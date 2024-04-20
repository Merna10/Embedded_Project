/*
 * adc.c
 *
 *  Created on: Oct 4, 2022
 *      Author: merna
 */


#include "common_macros.h"
#include "adc.h"
#include <avr/io.h>


void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	ADMUX |= Config_Ptr->ref;
	ADCSRA |=(1<<ADEN )| Config_Ptr->prescaler;
}

uint16 ADC_readChannel(uint8 channel_num)
{
	channel_num &= 0x07;
	ADMUX &= 0XE0;
	ADMUX |= channel_num;
	SET_BIT(ADCSRA,ADSC);
	while(BIT_IS_CLEAR(ADCSRA,ADIF));
	SET_BIT(ADCSRA,ADIF);
	return ADC;
}


