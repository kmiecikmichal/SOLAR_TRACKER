#include "i2c.h"

void i2cInitialize(void){

	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
  SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
    
	PORTB->PCR[3] |= PORT_PCR_MUX(2); // I2C0 SCL
	PORTB->PCR[4] |= PORT_PCR_MUX(2); // I2C0 SDA

	I2C0->F |= I2C_F_MULT(2);					// mul
	I2C0->F |= I2C_F_ICR(7);					// baud rate = fbus(24MHz) / 2^mul * ICR
	
	I2C0->C1 |= I2C_C1_IICEN_MASK;		//enable I2C
}

void i2cSendSingleByte(uint8_t dev, uint8_t address, uint8_t data){
	
	I2C_TRAN; 					//set to transmit mode 
	I2C_M_START; 				//send start 
	I2C0->D = dev; 			//send dev address 
	I2C_WAIT; 					//wait for ack
	I2C0->D = address; 	//send write address 
	I2C_WAIT;
	I2C0->D = data;			//send data 
	I2C_WAIT;
	I2C_M_STOP;					//send stop 
}

uint8_t i2cReadSingleByte(uint8_t dev, uint8_t address){

	uint8_t data;
	
	I2C_TRAN; 						//set to transmit mode 
	I2C_M_START; 					//send start
	I2C0->D = dev; 				//send dev address 
	I2C_WAIT; 						//wait for completion
	I2C0->D = address; 		//send read address 
	I2C_WAIT; 						//wait for completion 
	I2C_M_RSTART;					//repeated start 
	I2C0->D = (dev|0x1);	//send dev address (read)
	I2C_WAIT; 						//wait for completion 
	I2C_REC; 							//set to recieve mode 
	NACK; 								//set NACK after read 
	data = I2C0->D; 			//dummy read 
	I2C_WAIT; 						//wait for completion 
	I2C_M_STOP; 					//send stop 
	data = I2C0->D; 			//read data
	
	return data;

}
