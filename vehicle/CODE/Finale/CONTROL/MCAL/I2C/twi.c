/*
 * twi.c
 *
 *  Created on: Sep 12, 2023
 *      Author: merna
 */


#include "twi.h"

#include "../../LIB/common_macros.h"
#include <avr/io.h>

void TWI_init(uint8 Copy_uint8MasterAddress)
{
	/* Bit Rate: 400.000 kbps using zero pre-scaler TWPS=00 and F_CPU=8Mhz
	 * ((8000000/400.000)-16)/2
	 * 2
	 * */
	TWBR = 0x02;
	TWSR = 0x00;

	/* Two Wire Bus address my address if any master device want to call me: 0x1 (used in case this MC is a slave device)
       General Call Recognition: Off */
	if(Copy_uint8MasterAddress!=0)
	{
		TWAR=Copy_uint8MasterAddress<<1;
	} // my address = 0x01 :)

	TWCR = (1<<TWEN); /* enable TWI */
	//Enable Ack
	SET_BIT(TWCR,6);
}

void TWI_voidSlaveInit(uint8 Copy_uint8SlaveAddress)
{
	/*Initialization the node address*/
	TWAR=Copy_uint8SlaveAddress<<1;
	/*Enable TWI*/
	SET_BIT(TWCR,TWEN);
}
void TWI_start(void)
{
	/*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

void TWI_stop(void)
{
	/*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

I2C_ErrorState I2C_SendSlaveAddressWithWrite(uint8 Copy_u8SlaveAddress)
{

	I2C_ErrorState Local_ErrStatus=NoError;
	/*clear the start condition bit */
	CLEAR_BIT(TWCR,TWSTA);
	/*set slave address in the 7 MSB in the data register */
	TWDR=Copy_u8SlaveAddress<<1;
	/*write request*/
	CLEAR_BIT(TWDR,0);
	/*clear the interrupt flag to start the previous operation*/
	SET_BIT(TWCR,TWINT);
	/*wait until the interrupt flag is raised at the previous operation completed*/
	while(BIT_IS_CLEAR(TWCR,TWINT));
	if((TWSR & 0xF8)!= SLAVE_ADD_AND_WR_ACK)
	{
		Local_ErrStatus=SlaveAddressWithWriteErr;
	}
	return Local_ErrStatus;
}
I2C_ErrorState I2C_SendSlaveAddressWithRead(uint8 Copy_u8SlaveAddress)
{

	I2C_ErrorState Local_ErrStatus=NoError;
	/*clear the start condition bit */
	CLEAR_BIT(TWCR,TWSTA);
	/*set slave address in the 7 MSB in the data register */
	TWDR=Copy_u8SlaveAddress<<1;
	/*read request*/
	SET_BIT(TWDR,0);
	/*clear the interrupt flag to start the previous operation*/
	SET_BIT(TWCR,TWINT);
	/*wait until the interrupt flag is raised at the previous operation completed*/
	while((GET_BIT(TWCR,TWINT))==0);
	if((TWSR & 0xF8)!= SLAVE_ADD_AND_RD_ACK )
	{
		Local_ErrStatus=SlaveAddressWithReadErr;
	}
	return Local_ErrStatus;
}

void TWI_writeByte(uint8 data)
{
	/* Put data On TWI data Register */
	TWDR = data;
	/*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);
	/* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 TWI_readByteWithACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
	/* Read Data */
	return TWDR;
}

uint8 TWI_readByteWithNACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
	/* Read Data */
	return TWDR;
}

uint8 TWI_getStatus(void)
{
	uint8 status;
	/* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
	status = TWSR & 0xF8;
	return status;
}
