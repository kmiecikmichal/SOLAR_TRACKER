#ifndef adc_h
#define adc_h

#include "MKL05Z4.h"
#include "uart.h"
#include "extra.h"

void adcInitialize(void);
void adcCalibration(void);
float adcMeasureLight1(void);
float adcMeasureLight2(void);
float adcMeasureLight3(void);
float adcMeasureLight4(void);
void adcTest(void);

#endif
