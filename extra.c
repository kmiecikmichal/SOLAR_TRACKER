#include "extra.h"

void delay(uint32_t value){
	
	uint32_t delay_val, x;
	
	for(x=0; x < value; x++){
		for(delay_val=0; delay_val < 10000; delay_val++){}; 
	}
}

void decToStringAndSendUart(uint8_t data){
	
	char strx[8];
	
  sprintf(strx, "%d", data);
	uartSendString(strx);
}
