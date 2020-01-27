#ifndef mode1_h
#define mode1_h

#include "MKL05Z4.h"
#include "pwm.h"
#include "adc.h"
#include "extra.h"
#include "mma8451.h"

uint8_t adcPhotoresistorsHandler(void);
void servoMode1SmoothOperator(uint8_t servo1PositionValue,uint8_t servo2PositionValue, uint32_t delayTime);
void servoMode1Handler(uint8_t result);
void mode1(void);

#endif
