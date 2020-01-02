#include "uart.h"

void uartInitialize(void){
	
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	
	PORTB->PCR[1] |= PORT_PCR_MUX(2);			// 2 because it's 2nd alternative function of this pin
	PORTB->PCR[2] |= PORT_PCR_MUX(2);
	
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);	// 1 = 48 MHz
	
	UART0->C2 &= !UART0_C2_TE_MASK;				// Tx disabled
	UART0->C2 &= !UART0_C2_RE_MASK;				// Rx disabled
	UART0->C4 |= UART0_C4_OSR(31);				// Over Sampling Ratio 31

	UART0->BDH |= UART0_BDH_SBR(0);
	UART0->BDL |= UART0_BDL_SBR(78);			// Baud rate = 19200, clk = 48 MHz
	
	UART0->BDH &= !UART0_BDH_SBNS_MASK;		// One stop bit

	UART0->C1 &= !UART0_C1_M_MASK;				// 8 bit long data
	UART0->C1 &= !UART0_C1_PE_MASK;				// No hardware parity checking or generating
	
	UART0->C2 |= UART0_C2_TE_MASK;				// Enable Tx
	UART0->C2 |= UART0_C2_RE_MASK;				// Enable Rx 
}

void uartSendChar(uint8_t c){
	
    while(!(UART0->S1 & UART0_S1_TDRE_MASK)); // wait until transmit data register is empty
		UART0->D = c;
}

void uartSendString(uint8_t *data){
	
    while(*data){
        uartSendChar(*data++);
    }
}
