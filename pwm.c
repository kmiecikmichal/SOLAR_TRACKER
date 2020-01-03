#include "pwm.h"

void pwmInitialize(){

	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;		// Clock on PORTB 
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;	

	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(3); 		// TPM Clock source, 1 = 48MHz, 3 = 4MHz
	
	PORTB->PCR[10] |= PORT_PCR_MUX(2); 		// PORTB 10 to TPM
	
	TPM0->SC &= ~TPM_SC_CPWMS_MASK;				// Up counting mode
	TPM0->SC &= ~TPM_SC_CMOD_MASK;				// CMOD 0, LPTPM counter is disabled
	TPM0->SC |= TPM_SC_PS(2); 						// Clock divider, 2 = clk/4

	TPM0->MOD = 1629; 										// 8149 for 1 sec. Period = modulo + 1, for servo period = 20ms 

	TPM0->CONTROLS[1].CnSC |= (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK); // Center-aligned PWM High-pulse

	TPM0->SC |= TPM_SC_CMOD(1);
}

void TPM0_IRQHandler(){
	
	NVIC_ClearPendingIRQ(TPM0_IRQn);
	TPM0->SC |= TPM_SC_TOF_MASK;
}

void pwmServo1(uint16_t pulseWidth){

	while( !(TPM0->STATUS & TPM_STATUS_TOF_MASK )) {}
	
	TPM0->SC |= TPM_SC_CMOD(0); 											// 0 = LPTPM counter is disabled
	TPM0->CONTROLS[1].CnV = TPM_CnV_VAL(pulseWidth); 	// Pulse width
	TPM0->SC |= TPM_SC_CMOD(1); 											// 1 = LPTPM counter increments on every LPTPM counter clock
}
