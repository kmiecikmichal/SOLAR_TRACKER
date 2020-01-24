#include "mode1.h"

void mode1(void){
	uint8_t result;

	result = adcPhotoresistorsHandler();
	decToStringAndSendUart(result);
	servoMode1Handler(result);
}