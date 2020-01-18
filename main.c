#include "MKL05Z4.h"
#include "uart.h"
#include "i2c.h"
#include "pwm.h"
#include "adc.h"
#include "extra.h"
#include "mma8451.h"

int main(){
	uint8_t result_x, result_y, result_z;

	// UART
	uartInitialize();

	// PWM
	//pwmInitialize();
	//servoDegreeTest();

	// ADC
	//adcInitialize();
	//result = adcMeasureLight2();
	
	
	
	// ACCELEROMETER
	accelInitialize();
	// actually not working 
	//result = accelRead();
	
	
	// int to string
	//char str[8];
  //sprintf(str, "%u", result);
	//uartSendString(str);
	
	while(1){
		/*
		result = adcMeasureLight2();
		if( result < 1000){
			pwmServo1(3.95);
			delay_mc(1000);
		}
		else{
			pwmServo1(19.95);
			delay_mc(1000);
		}
		*/
		uartSendString("accelerometer: ");
		result_x = accelReadX();
		char strx[8];
  sprintf(strx, "%u", result_x);
	uartSendString(" x:");
	uartSendString(strx);
		
	result_y = accelReadY();
		char stry[8];
  sprintf(stry, "%u", result_y);
	uartSendString(" y:");
	uartSendString(stry);
	
	result_z = accelReadZ();
		char strz[8];
  sprintf(strz, "%u", result_z);
	uartSendString(" z:");
	uartSendString(strz);
	
	delay_mc(1000);
	}
}
