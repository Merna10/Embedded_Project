/*
 * pwm.c
 *
 *  Created on: Oct 9, 2022
 *      Author: merna
 */

#include "common_macros.h"
#include "gpio.h"
#include "pwm.h"
#include <avr/io.h>


void PWM_Timer0_Start(uint8 duty_cycle)
{
	TCNT0 =0;
	/*Compare Value*/
	OCR0= ((float)duty_cycle / 100) * 255;
	/*TIMER0_PIN_ID as output*/
	GPIO_setupPinDirection (TIMER0_PORT_ID,TIMER0_PIN_ID,PIN_OUTPUT);
	TCCR0 |= (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}
