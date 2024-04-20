/*
 * adc.h
 *
 *  Created on: Aug 25, 2023
 *      Author: merna
 */

#ifndef MCAL_ADC_ADC_H_
#define MCAL_ADC_ADC_H_
#include "../../LIB/std_types.h"

#define ADC_REF_SELECT_BITS				6
#define ADC_LEFT_ADJ_BIT				5
#define ADC_MUX_BITS					0
#define ADC_ENABLE_BIT					7
#define ADC_START_CONVERSION_BIT		6
#define ADC_AUTO_TRIGER_ENABLE_BIT		5
#define ADC_INT_FLAG_BIT				4
#define ADC_INT_ENABLE_BIT				3
#define ADC_PRESCALER_BITS				0
#define ADC_AUTO_TRIGER_SOURCE_BITS		5
#define ADC_MAXIMUM_VALUE           1023
#define ADC_REF_VOLT_VALUE          2.56

typedef enum
{
	AREF = 0x00,
	AVCC = 0x40,
	INTERNAL = 0xC0
} ADC_Reference;

typedef enum{
	F_CPU1=0x03,
	F_CPU8=0x06,
	F_CPU16=0x07
}ADC_Prescaler;

typedef enum{
	ADC0 = 0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7,
	/*
	 * ADC_0_0_10,
	ADC_1_0_10,
	ADC_0_0_200,
	ADC_1_0_200,
	ADC_2_2_10,
	ADC_3_2_10,
	ADC_2_2_200,
	ADC_3_2_200,
	ADC_0_1_1,
	ADC_1_1_1,
	ADC_2_1_1,
	ADC_3_1_1,
	ADC_4_1_1,
	ADC_5_1_1,
	ADC_6_1_1,
	ADC_7_1_1,
	ADC_0_2_1,
	ADC_1_2_1,
	ADC_2_2_1,
	ADC_3_2_1,
	ADC_4_2_1,
	ADC_5_2_1,
	VBG,
	GND*/
}ADC_CHANNELS;
typedef struct
{
	ADC_Prescaler prescaler;
	ADC_Reference ref;
} ADC_ConfigType;
void ADC_init(ADC_ConfigType  *type);
uint16 ADC_readChannel(uint8 channel_num);

#endif /* MCAL_ADC_ADC_H_ */
