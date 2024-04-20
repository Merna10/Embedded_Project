/*
 * adc.h
 *
 *  Created on: Oct 4, 2022
 *      Author: merna
 */

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/* DEFINATION */
#define ADC_MAXIMUM_VALUE           1023
#define ADC_REF_VOLT_VALUE          2.56

/*declare*/
typedef enum
{
	AREF = 0x00 , AVCC = 0x40 , INTERNAL = 0xC0
} ADC_Reference_Selection_Bits;

typedef enum
{
	F_CPU2 = 0x00 , F_CPU4 = 0x02 , F_CPU8 = 0x03 , F_CPU16 = 0x04 , F_CPU32 = 0x05 , F_CPU64 = 0x06 , F_CPU128 = 0x07
}  ADC_Prescaler_SelectBits;


typedef struct
{
	ADC_Reference_Selection_Bits ref;
	ADC_Prescaler_SelectBits prescaler;
} ADC_ConfigType;

/*prototypes*/
void ADC_init(const ADC_ConfigType * Config_Ptr);
uint16 ADC_readChannel(uint8 ch_num);

#endif /* ADC_H_ */
