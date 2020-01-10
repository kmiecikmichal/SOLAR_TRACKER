#include "pwm.h"

void pwmInitialize(){

	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;		// Clock on PORTB 
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;	

	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(3); 		// TPM Clock source, 1 = 48MHz, 3 = 4MHz
	
	PORTB->PCR[7] |= PORT_PCR_MUX(2); 		// PORTB 7 to TPM -> Servo 1 TPM0 CH2
	PORTB->PCR[6] |= PORT_PCR_MUX(2); 		// PORTB 6 to TPM -> Servo 2 TPM0 CH3
	
	TPM0->SC &= ~TPM_SC_CPWMS_MASK;				// Up counting mode
	TPM0->SC &= ~TPM_SC_CMOD_MASK;				// CMOD 0, LPTPM counter is disabled
	TPM0->SC |= TPM_SC_PS(2); 						// Clock divider, 2 = clk/4

	TPM0->MOD = 162; 											// 8149 for 1 sec. Period = modulo + 1, for servo period = 20ms 
	
	TPM0->CONTROLS[2].CnSC |= (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK); // Center-aligned PWM High-pulse CH1
	TPM0->CONTROLS[3].CnSC |= (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK); // Center-aligned PWM High-pulse CH2


	TPM0->SC |= TPM_SC_CMOD(1);
}

void TPM0_IRQHandler(){
	
	NVIC_ClearPendingIRQ(TPM0_IRQn);
	TPM0->SC |= TPM_SC_TOF_MASK;
}

void pwmServo1(uint16_t pulseWidth){

	while( !(TPM0->STATUS & TPM_STATUS_TOF_MASK )) {}
	
	TPM0->SC |= TPM_SC_CMOD(0); 											// 0 = LPTPM counter is disabled
	TPM0->CONTROLS[2].CnV = TPM_CnV_VAL(pulseWidth); 	// Pulse width CH2 PB7
	TPM0->SC |= TPM_SC_CMOD(1); 											// 1 = LPTPM counter increments on every LPTPM counter clock
}

void pwmServo2(uint16_t pulseWidth){

	while( !(TPM0->STATUS & TPM_STATUS_TOF_MASK )) {}
	
	TPM0->SC |= TPM_SC_CMOD(0); 											// 0 = LPTPM counter is disabled
	TPM0->CONTROLS[3].CnV = TPM_CnV_VAL(pulseWidth); 	// Pulse width CH3 PB6
	TPM0->SC |= TPM_SC_CMOD(1); 											// 1 = LPTPM counter increments on every LPTPM counter clock
}

void servoWorkTest (void){
	delay_mc(1000);
	pwmServo1(3.95);	// Servo position -90deg
	pwmServo2(3.95);
	delay_mc(1000); 
	pwmServo1(19.95); // Servo position 90deg
	pwmServo2(19.95);
	delay_mc(1000);
	pwmServo1(3.95);	// Servo position -90deg
	pwmServo2(3.95);
	delay_mc(1000); 
	pwmServo1(19.95); // Servo position 90deg
	pwmServo2(19.95);
}

void servoDegreeTest (void){
	uint32_t x = 3.95; // Start position, -90 deg
	
	while(x <= 19.95){
		delay_mc(1000);
		pwmServo1(x);
		pwmServo2(x);
		x += 1;
	}
}
