/*
 * twi.h
 *
 *  Created on: Sep 12, 2023
 *      Author: user
 */

#ifndef LIB_TWI_H_
#define LIB_TWI_H_

#include "../../LIB/std_types.h"



/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
///* I2C Status Bits in the TWSR Register */
#define  START_ACK               0X08  /*Start has been sent*/
#define  REP_START_ACK           0X10  /*repeated start*/
#define  SLAVE_ADD_AND_WR_ACK    0X18  /*Master Transmit (slave address + Write request ) ACK*/
#define  SLAVE_ADD_AND_RD_ACK    0X40  /*Master Transmit (slave address + Read request ) ACK*/
#define  MSTR_WR_BYTE_WITH_ACK   0X28  /*Master Transmit Data Ack*/
#define  MSTR_RD_BYTE_WITH_ACK   0X50  /*Master Recieve Data with Ack*/
#define  MSTR_RD_BYTE_WITH_NACK  0X58  /*Master Recieve Data with no Ack*/
#define  SLAVE_ADD_RCVD_RD       0XA8  /*means that slave address is recieved with read request */
#define  SLAVE_ADD_RCVD_RW       0X60  /*means that slave address is recieved with Write request */
#define  SLAVE_DATA_RECIEVED     0X80  /*means that a byte is recieved */
#define  SLAVE_BYTE_TRANSMITTED  0XB8  /*means that the written byte is transmitted */

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */


typedef enum
{
	NoError,
	StartConditionError,
	RepeatedStartError,
	SlaveAddressWithWriteErr,
	SlaveAddressWithReadErr,
	MasterWriteByteErr,
}I2C_ErrorState;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void TWI_init(uint8 Copy_uint8MasterAddress);
void TWI_voidSlaveInit(uint8 Copy_uint8SlaveAddress);
void TWI_start(void);
void TWI_stop(void);
I2C_ErrorState I2C_SendSlaveAddressWithWrite(uint8 Copy_u8SlaveAddress);
I2C_ErrorState I2C_SendSlaveAddressWithRead(uint8 Copy_u8SlaveAddress);
void TWI_writeByte(uint8 data);
uint8 TWI_readByteWithACK(void);
uint8 TWI_readByteWithNACK(void);
uint8 TWI_getStatus(void);

#endif /* LIB_TWI_H_ */
