#ifndef pwm_h
#define pwm_h

#include "MKL05Z4.h"

void pwmInitialize(void);
void pwmServo1(uint16_t pulseWidth);
void delay_mc(uint32_t value);
	
#endif
