#include "MKL05Z4.h"
#include "uart.h"
#include "i2c.h"
#include "pwm.h"
#include "adc.h"
#include "extra.h"
#include "mma8451.h"
#include "mode1.h"

int main(){
	
	//uint8_t result;

	// UART
	uartInitialize();

	// PWM
	pwmInitialize();
	//servoDegreeTest();

	// ADC
	adcInitialize();
	//result = adcMeasureLight2();
	
	// ACCELEROMETER
	accelInitialize();

	int table1[2][2] = {{1,2},{5,6}};
	int table2[2] = {3,4};
	int *table3[2] = {table1, table2};
	uartSendString("as");
	decToStringAndSendUart(table3[0][2]);
	
	
	while(1){
		/*
		result = adcMeasureLight2();
		if( result < 1000){
			pwmServo1(3.95);
			delay(1000);
		}
		else{
			pwmServo1(19.95);
			delay(1000);
		}
		*/
		
		//accelReadXYZ();
		//adcTest();
		//mode1();
		
		
		
	}
}
