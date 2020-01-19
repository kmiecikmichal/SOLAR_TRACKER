#ifndef pwm_h
#define pwm_h

#include "MKL05Z4.h"
#include "extra.h"

void pwmInitialize(void);
void pwmServo1(uint16_t pulseWidth);
void pwmServo2(uint16_t pulseWidth);
void servoWorkTest(void);
void servoDegreeTest(void);
	
#endif
