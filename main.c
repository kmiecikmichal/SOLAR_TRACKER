#include "MKL05Z4.h"
#include "uart.h"
#include "i2c.h"
#include "mma8451.h"

int main(){
	uint16_t result;

	uartInitialize();
	accelInitialize();
	
	result = accelRead();
	
	// int to string
	char str[8];
  sprintf(str, "%u", result);
	uartSendString(str);
	
	while(1){
	}
}
