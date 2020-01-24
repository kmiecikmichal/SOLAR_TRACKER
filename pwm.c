#include "pwm.h"

uint8_t actualServo1Position = 45; // Type pulsewidth there from 
uint8_t actualServo2Position = 45;

void pwmInitialize(){

	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;		// Clock on PORTB 
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;	

	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(3); 		// TPM Clock source, 1 = 48MHz, 3 = 4MHz
	
	PORTB->PCR[7] |= PORT_PCR_MUX(2); 		// PORTB 7 to TPM -> Servo 1 TPM0 CH2
	PORTB->PCR[6] |= PORT_PCR_MUX(2); 		// PORTB 6 to TPM -> Servo 2 TPM0 CH3
	
	TPM0->SC &= ~TPM_SC_CPWMS_MASK;				// Up counting mode
	TPM0->SC &= ~TPM_SC_CMOD_MASK;				// CMOD 0, LPTPM counter is disabled
	TPM0->SC |= TPM_SC_PS(0); 						// Clock divider, 0 = clk

	TPM0->MOD = 651;											// 651 for 20ms. Period = modulo + 1, for servo period = 20ms 
	
	TPM0->CONTROLS[2].CnSC |= (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK); // Center-aligned PWM High-pulse CH1
	TPM0->CONTROLS[3].CnSC |= (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK); // Center-aligned PWM High-pulse CH2

	TPM0->SC |= TPM_SC_CMOD(1);
}

void TPM0_IRQHandler(){
	
	NVIC_ClearPendingIRQ(TPM0_IRQn);
	TPM0->SC |= TPM_SC_TOF_MASK;
}

void pwmServo1(uint16_t pulseWidth){ // TOP

	while( !(TPM0->STATUS & TPM_STATUS_TOF_MASK )) {}
	
	TPM0->SC |= TPM_SC_CMOD(0); 											// 0 = LPTPM counter is disabled
	TPM0->CONTROLS[2].CnV = TPM_CnV_VAL(pulseWidth); 	// Pulse width CH2 PB7
	TPM0->SC |= TPM_SC_CMOD(1); 											// 1 = LPTPM counter increments on every LPTPM counter clock
}

void pwmServo2(uint16_t pulseWidth){ // BOTTOM

	while( !(TPM0->STATUS & TPM_STATUS_TOF_MASK )) {}
	
	TPM0->SC |= TPM_SC_CMOD(0); 											// 0 = LPTPM counter is disabled
	TPM0->CONTROLS[3].CnV = TPM_CnV_VAL(pulseWidth); 	// Pulse width CH3 PB6
	TPM0->SC |= TPM_SC_CMOD(1); 											// 1 = LPTPM counter increments on every LPTPM counter clock
}

void servoWorkTest (void){
	delay(1000);
	pwmServo1(14);	// Servo position -90deg
	pwmServo2(14);
	delay(1000); 
	pwmServo1(45); // Servo position 0deg
	pwmServo2(45);
	delay(1000); 
	pwmServo1(76); // Servo position 90deg
	pwmServo2(76);
}

void servoDegreeTest (void){
	uint32_t x = 14; // Start position, -90 deg
	
	while(x <= 76){
		delay(1000);
		pwmServo1(x);
		delay(100);
		pwmServo2(x);
		x += 1;
	}
}
void servoStartPosition(void){
	pwmServo1(45);
	pwmServo2(47);
}

void servoSmoothOperator(uint8_t servo1PositionValue,uint8_t servo2PositionValue, uint32_t delayTime){
	uint8_t servo1Flag = 0;
	uint8_t servo2Flag = 0;
	
	while (servo1Flag != 1 || servo2Flag != 1) {
	uartSendString(" 1 ");
	decToStringAndSendUart(actualServo1Position);
	uartSendString(" 2 ");
	decToStringAndSendUart(actualServo2Position);
	
		if (actualServo1Position == servo1PositionValue & actualServo2Position == servo2PositionValue){
			servo1Flag = 1;
			servo2Flag = 1;
		}
		else if (actualServo1Position == servo1PositionValue && actualServo2Position != servo2PositionValue){
			servo1Flag = 1;
			
			if (actualServo2Position < servo2PositionValue){
				delay(delayTime);
				actualServo2Position += 1;
				pwmServo2(actualServo2Position);
			}
			else{
				delay(delayTime);
				actualServo2Position -= 1;
				pwmServo2(actualServo2Position);
			}
		}
		else if (actualServo1Position != servo1PositionValue && actualServo2Position == servo2PositionValue){
			servo2Flag = 1;

			if (actualServo1Position < servo1PositionValue){
				delay(delayTime);
				actualServo1Position += 1;
				pwmServo1(actualServo1Position);
			}
			else{
				delay(delayTime);
				actualServo1Position -= 1;
				pwmServo1(actualServo1Position);
			}
		}
		else if (actualServo1Position != servo1PositionValue && actualServo2Position != servo2PositionValue){
			if (actualServo1Position < servo1PositionValue && actualServo2Position < servo2PositionValue){
				delay(delayTime);
				actualServo1Position += 1;
				actualServo2Position += 1;
				pwmServo1(actualServo1Position);
				pwmServo2(actualServo2Position);
			}
			else if (actualServo1Position > servo1PositionValue && actualServo2Position < servo2PositionValue){
				delay(delayTime);
				actualServo1Position -= 1;
				actualServo2Position += 1;
				pwmServo1(actualServo1Position);
				pwmServo2(actualServo2Position);
			}
			else if (actualServo1Position < servo1PositionValue && actualServo2Position > servo2PositionValue){
				delay(delayTime);
				actualServo1Position += 1;
				actualServo2Position -= 1;
				pwmServo1(actualServo1Position);
				pwmServo2(actualServo2Position);
			}
			else if (actualServo1Position > servo1PositionValue && actualServo2Position > servo2PositionValue){
				delay(delayTime);
				actualServo1Position -= 1;
				actualServo2Position -= 1;
				pwmServo1(actualServo1Position);
				pwmServo2(actualServo2Position);
			}
		}
	}
}

void servoMode1Handler(uint8_t result){
	
	if (result == 0){
		servoSmoothOperator(45,45,1000);
	}
	else if (result == 1){
		servoSmoothOperator(30,30,1000);
	}
	else if (result == 2){
		servoSmoothOperator(60,60,1000);
	}
	else if (result == 3){
		servoSmoothOperator(60,30,1000);
	}
	else if (result == 4){
		servoSmoothOperator(30,60,1000);
	}
	else if (result == 12){
		servoSmoothOperator(30,14,1000);
	}
	else if (result == 23){
		servoSmoothOperator(60,45,1000);
	}
	else if (result == 34){
		servoSmoothOperator(30,76,1000);
	}
	else if (result == 41){
		servoSmoothOperator(30,45,1000);
	}
}
