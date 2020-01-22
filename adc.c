#include "adc.h"

void adcInitialize(void){
	
	// Initialize input pins on board
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;		// Clock on PORTA
	PORTA->PCR[8] |= PORT_PCR_MUX(0); 		// ADC0_SE3
	PORTA->PCR[9] |= PORT_PCR_MUX(0); 		// ADC0_SE2
	PORTA->PCR[7] |= PORT_PCR_MUX(0); 		// ADC0_SE7
	PORTA->PCR[12] |= PORT_PCR_MUX(0); 		// ADC0_SE0
	
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

float adcMeasureLight1(void){

	// red stand PORTA 8
	uint16_t light;
	ADC0->SC1[0] = ADC_SC1_ADCH(3); // 3 = PORTA8 INPUT 

	while(!(ADC0->SC1[0] & ADC_SC1_COCO_MASK)){}; // Wait until conversion complete

	light = ADC0 -> R[0];

	return light; // result from 0(brightness 100%) to 255(brightness 0%)
}

float adcMeasureLight2(void){

	// next, clockwise PORTA 9
	uint16_t light;
	ADC0->SC1[0] = ADC_SC1_ADCH(2); // 2 = PORTA9 INPUT 

	while(!(ADC0->SC1[0] & ADC_SC1_COCO_MASK)){}; // Wait until conversion complete

	light = ADC0 -> R[0];

	return light;
}

float adcMeasureLight3(void){

	// PORTA 7
	uint16_t light;
	ADC0->SC1[0] = ADC_SC1_ADCH(7); // 7 = PORTA7 INPUT 

	while(!(ADC0->SC1[0] & ADC_SC1_COCO_MASK)){}; // Wait until conversion complete

	light = ADC0 -> R[0];

	return light;
}

float adcMeasureLight4(void){

	// PORTA 12
	uint16_t light;
	ADC0->SC1[0] = ADC_SC1_ADCH(0); // 0 = PORTA12 INPUT 

	while(!(ADC0->SC1[0] & ADC_SC1_COCO_MASK)){}; // Wait until conversion complete

	light = ADC0 -> R[0];

	return light;
}

void adcTest(void){
	
	uint8_t result1, result2, result3 ,result4;
	
	uartSendString(" adc1: ");
	result1 = adcMeasureLight1();
	decToStringAndSendUart(result1);
	
	uartSendString(" adc2: ");
	result2 = adcMeasureLight2();
	decToStringAndSendUart(result2);
	
	uartSendString(" adc3: ");
	result3 = adcMeasureLight3();
	decToStringAndSendUart(result3);
	
	uartSendString(" adc4: ");
	result4 = adcMeasureLight4();
	decToStringAndSendUart(result4);
}

uint8_t adcPhotoresistorsHandler(void){
	
	uint8_t i;
	uint16_t average1 = 0;
	uint16_t average2 = 0;
	uint16_t average3 = 0;
	uint16_t average4 = 0;
	uint8_t position = 0;
	uint8_t diff = 30; 
	
	// AVERAGING 
	
	for(i = 0; i < 10; i++){
		average1 += adcMeasureLight1();
		average2 += adcMeasureLight2();
		average3 += adcMeasureLight3();
		average4 += adcMeasureLight4();
		
		delay(1000);
	}
	
	average1 /= 10;
	average2 /= 10;
	average3 /= 10;
	average4 /= 10;
	
	// COMPARING
	
	// adc1
	if(average1 < average2 - diff && average1 < average3 - diff && average1 < average4 - diff){
		position = 1;
	}
	// adc2
	else if(average2 < average1 - diff && average2 < average3 - diff && average2 < average4 - diff){
		position = 2;
	}
	// adc3
	else if(average3 < average1 - diff && average3 < average2 - diff && average3 < average4 - diff){
		position = 3;
	}
	// adc4
	else if(average4 < average1 - diff && average4 < average2 - diff && average4 < average3 - diff){
		position = 4;
	}
	// adc1 + adc2
	else if(average1 < average3 - diff && average1 < average4 - diff && average2 < average3 - diff && average2 < average4 - diff){
		position = 12;
	}
	// adc2 + adc3
	else if(average2 < average1 - diff && average2 < average4 - diff && average3 < average1 - diff && average3 < average4 - diff){
		position = 23;
	}
	// adc3 + adc4
	else if(average3 < average1 - diff && average3 < average2 - diff && average4 < average1 - diff && average4 < average2 - diff){
		position = 34;
	}
	// adc4 + adc1
	else if(average4 < average2 - diff && average4 < average3 - diff && average1 < average2 - diff && average1 < average3 - diff){
		position = 41;
	}
	// neutral
	else{
		position = 0;
	}

	return position;
}

