#include "adc.h"

void adcInitialize(void){
	
	// Initialize input pins on board
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;		// Clock on PORTA
	PORTA->PCR[8] |= PORT_PCR_MUX(0); 		// ADC0_SE3
	
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK; 		//Base freq = 24MHz
	ADC0->CFG1 |= ADC_CFG1_ADLSMP_MASK;		//Long Time Sample
	ADC0->CFG1 |= ADC_CFG1_ADICLK(1);			//Here freq = 12MHz, Input Clock Select
	ADC0->CFG1 |= ADC_CFG1_ADIV(0);	 			//Here freq = 3MHz Clock Divide Select
	
	ADC0->CFG2 |= ADC_CFG2_ADHSC_MASK; 		//For higher freqs
	ADC0->CFG2 |= ADC_CFG2_ADLSTS(0); 		//Long Sample Time Select, 0 = Default longest sample time; 20 extra ADCK cycles; 24 ADCK cycles total
	
	ADC0->SC2 |= ADC_SC2_REFSEL(0); 			//External reference source
	
	ADC0->SC3 |= ADC_SC3_AVGE_MASK;				//Averaging on 
	ADC0->SC3 |= ADC_SC3_AVGS(3); 				//Max 32 value
	
	adcCalibration();
}

// ADD ADC0_IRQHandler

void adcCalibration(void){
	
	uint16_t cal;
	
	cal = ADC0->CLP0 + ADC0->CLP1 + ADC0->CLP2 + ADC0->CLP3 + ADC0->CLP4 + ADC0->CLPD + ADC0->CLPS; //Sum up all ADC0->CLPx registers
	cal /= 2; 									//Divide by 2
	cal |= (1UL << 15); 				//Set 1 at MSB
	ADC0->PG = ADC_PG_PG(cal); 	//Send cal to ADC0->PG register
	
	ADC0->CFG1 |= ADC_CFG1_MODE(1); 		//BUS_CLOCK/2, divide by 1, Long Sample Time, 
	ADC0->SC1[0] |= ADC_SC1_AIEN_MASK; 	//Active Interupt
}

float adcMeasureLight2(void){

	uint16_t light;
	ADC0->SC1[0] = ADC_SC1_ADCH(3); // 3 = PORTA INPUT 

	while(!(ADC0->SC1[0] & ADC_SC1_COCO_MASK)){}; // Wait until conversion complete

	light = ADC0 -> R[0];

	return light;
}
