#ifndef pwm_h
#define pwm_h

#include "MKL05Z4.h"
#include "extra.h"

void pwmInitialize(void);
void pwmServo1(uint16_t pulseWidth);
void pwmServo2(uint16_t pulseWidth);
void servoWorkTest(void);
void servoDegreeTest(void);
void servoStartPosition(void);
void servoSmoothOperator(uint8_t servo1PositionValue,uint8_t servo2PositionValue, uint32_t delayTime);
void servoMode1Handler(uint8_t result);
	
#endif
