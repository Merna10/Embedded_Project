/*
 * interupt.c
 *
 *  Created on: Oct 28, 2022
 *      Author: merna
 */

#include "interrupt.h"

/* External INT0 enable and configuration function */
void INT0_Init(void)
{
	// Configure INT0/PD2 as input pin
	MCUCR |= (1<<ISC00) | (1<<ISC01);   // Trigger INT0 with the raising edge
	GICR  |= (1<<INT0);                 // Enable external interrupt pin INT0
	SREG  |= (1<<7);                    // Enable interrupts by setting I-bit
}
