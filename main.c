#include "MKL05Z4.h"
#include "uart.h"
#include "i2c.h"
#include "pwm.h"
#include "adc.h"
#include "extra.h"
#include "mma8451.h"
#include "mode1.h"
#include "mode2.h"

uint8_t mode = 1;

int main(){

	// UART
	uartInitialize();

	// PWM
	pwmInitialize();
	//servoDegreeTest();

	// ADC
	adcInitialize();
	
	// ACCELEROMETER
	accelInitialize();
	
	// SERVOS
	servoStartPosition();

	
	while(1){
		
		mode2(1,1,0,5000);
		//mode1();
		
	}
}
