#ifndef uart_h
#define uart_h

#include "MKL05Z4.h"

void uartInitialize(void);
void uartSendChar(uint8_t c);
void uartSendString(uint8_t *data);

#endif
