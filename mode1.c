#include "mode1.h"

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

void servoMode1SmoothOperator(uint8_t servo1PositionValue,uint8_t servo2PositionValue, uint32_t delayTime){
	uint8_t servo1Flag = 0;
	uint8_t servo2Flag = 0;
	
	while (servo1Flag != 1 || servo2Flag != 1) {
	
		if (actualServo1Position == servo1PositionValue && actualServo2Position == servo2PositionValue){
			servo1Flag = 1;
			servo2Flag = 1;
		}
		else if (actualServo1Position == servo1PositionValue && actualServo2Position != servo2PositionValue){
			servo1Flag = 1;
			
			if (actualServo2Position < servo2PositionValue){
				delay(delayTime);
				actualServo2Position += 1;
				pwmServo2(actualServo2Position);
			}
			else{
				delay(delayTime);
				actualServo2Position -= 1;
				pwmServo2(actualServo2Position);
			}
		}
		else if (actualServo1Position != servo1PositionValue && actualServo2Position == servo2PositionValue){
			servo2Flag = 1;

			if (actualServo1Position < servo1PositionValue){
				delay(delayTime);
				actualServo1Position += 1;
				pwmServo1(actualServo1Position);
			}
			else{
				delay(delayTime);
				actualServo1Position -= 1;
				pwmServo1(actualServo1Position);
			}
		}
		else if (actualServo1Position != servo1PositionValue && actualServo2Position != servo2PositionValue){
			if (actualServo1Position < servo1PositionValue && actualServo2Position < servo2PositionValue){
				delay(delayTime);
				actualServo1Position += 1;
				actualServo2Position += 1;
				pwmServo1(actualServo1Position);
				pwmServo2(actualServo2Position);
			}
			else if (actualServo1Position > servo1PositionValue && actualServo2Position < servo2PositionValue){
				delay(delayTime);
				actualServo1Position -= 1;
				actualServo2Position += 1;
				pwmServo1(actualServo1Position);
				pwmServo2(actualServo2Position);
			}
			else if (actualServo1Position < servo1PositionValue && actualServo2Position > servo2PositionValue){
				delay(delayTime);
				actualServo1Position += 1;
				actualServo2Position -= 1;
				pwmServo1(actualServo1Position);
				pwmServo2(actualServo2Position);
			}
			else if (actualServo1Position > servo1PositionValue && actualServo2Position > servo2PositionValue){
				delay(delayTime);
				actualServo1Position -= 1;
				actualServo2Position -= 1;
				pwmServo1(actualServo1Position);
				pwmServo2(actualServo2Position);
			}
		}
	}
}

void servoMode1Handler(uint8_t result){
	
	switch(result){
		case 0:
			servoMode1SmoothOperator(45,45,1000);
			break; 
		case 1:
			servoMode1SmoothOperator(30,30,1000);
			break; 
		case 2:
			servoMode1SmoothOperator(60,60,1000);
			break;
		case 3:
			servoMode1SmoothOperator(60,30,1000);
			break;
		case 4:
			servoMode1SmoothOperator(30,60,1000);
			break; 
		case 12:
			servoMode1SmoothOperator(60,60,1000);
			break;
		case 23:
			servoMode1SmoothOperator(60,45,1000);
			break;
		case 34:
			servoMode1SmoothOperator(30,76,1000);
			break;
		case 41:
			servoMode1SmoothOperator(30,45,1000);
			break; 	
	}
}

void mode1(void){
	uint8_t result;

	result = adcPhotoresistorsHandler();
	decToStringAndSendUart(result);
	servoMode1Handler(result);
}
