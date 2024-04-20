/*
 * adc.c
 *
 *  Created on: Aug 25, 2023
 *      Author: merna
 */

#include "adc.h"
#include "../../LIB/common_macros.h"
#include <avr/io.h>
/*
 * REFS1:0 = 01 to choose to connect external reference voltage by input this voltage through AREF pin
 * ADEN = 1
 * ADSC = 1 START CONVERSION IN THE READ OPERATION BECAUS DELAY
 * ADATE = 0
 * ADIF = 1
 * 125Khz --> ADC must operate in range 50-200Khz
 * so if F_CPU = 8MHZ SO PRESCALER 64
 *
 */
void ADC_init(ADC_ConfigType * type){

	ADMUX |= type->ref;
	ADCSRA |= (1<<ADC_ENABLE_BIT) | type->prescaler ;


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
