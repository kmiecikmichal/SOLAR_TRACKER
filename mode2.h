#ifndef mode2_h
#define mode2_h

#include <stdlib.h>
#include "MKL05Z4.h"
#include "pwm.h"
#include "adc.h"
#include "extra.h"
#include "mma8451.h"
#include "mode1.h"

void servoMode2SmoothOperator(uint8_t accelXPositionValue,uint8_t accelZPositionValue, uint32_t delayTime);
void mode2(uint8_t month, uint16_t day, uint8_t hour, uint16_t hourDelay);

#endif
