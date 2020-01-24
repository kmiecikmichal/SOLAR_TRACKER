#include "MKL05Z4.h"
#include "uart.h"
#include "i2c.h"
#include "pwm.h"
#include "adc.h"
#include "extra.h"
#include "mma8451.h"
#include "mode1.h"

int main(){
	
	uint8_t result;

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
	
	// SERVOS
	servoStartPosition();

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
		mode1();
		
	}
}
