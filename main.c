#include "MKL05Z4.h"
#include "uart.h"
#include "i2c.h"
#include "pwm.h"
#include "mma8451.h"

int main(){
	//uint16_t result;

	//UART
	uartInitialize();
	
	//PWM
	pwmInitialize();
	servoDegreeTest();

	//ACCELEROMETER
	accelInitialize();
	/* actually not working 
	result = accelRead();
	
	// int to string
	char str[8];
  sprintf(str, "%u", result);
	uartSendString(str);
	*/ 
	
	while(1){
	}
}
