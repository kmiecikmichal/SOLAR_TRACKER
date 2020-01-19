#ifndef adc_h
#define adc_h

#include "MKL05Z4.h"

void adcInitialize(void);
void adcCalibration(void);
float adcMeasureLight2(void);

#endif
