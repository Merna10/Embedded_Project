/*
 * Timer.c
 *
 *  Created on: Oct 22, 2022
 *      Author: merna
 */

#include "Timer.h"
#include "../LIB/common_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>

static void (*g_callBackPtr)(void) = NULL_PTR;

ISR(TIMER1_OVF_vect) {
	if (g_callBackPtr != NULL_PTR) {
		(*g_callBackPtr)();
	}
}

ISR(TIMER1_COMPA_vect) {
	if (g_callBackPtr != NULL_PTR) {
		(*g_callBackPtr)();
	}
}

void Timer1_init(const Timer_config *Config_Ptr) {

	SET_BIT(TCCR1A, FOC1A);
	SET_BIT(TCCR1A,FOC1B);
	TCCR1A |= Config_Ptr->prescaler;
	TCCR1B = Config_Ptr->prescaler;
	TCNT1 = Config_Ptr->Initial_value;
	if (Config_Ptr->mode == NORMAL) {
		SET_BIT(TIMSK, TOIE1);
		SET_BIT(TIFR,TOV1);
	} else if (Config_Ptr->mode == CTC) {
		SET_BIT(TCCR1B,WGM12);
		OCR1A=Config_Ptr->Compare_value;
		SET_BIT(TIMSK,OCIE1A);
		SET_BIT(TIFR,OCF1A);

	}
}

void Timer1_DeInit(void) {
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 =  0;
	CLEAR_BIT(TIMSK,TOIE1);
	CLEAR_BIT(TIFR,TOV1);
	OCR1A = 0;
	CLEAR_BIT(TIMSK,OCIE1A);
	CLEAR_BIT(TIFR,OCF1A);

}

/*void Delay(uint32 seconds) {
	uint8 count;
	TCNT1 = 0;
	OCR1A = 65000;
	for (int i = 0; i < seconds; i++) {
		for (count = 0; count < 485; count++) {
			while (!(TIFR & (1 << OCF1A)));
			TIFR |= (1 << OCF1A);
		}
	}
}*/

void Timer1_setCallBack(void (*a_ptr)(void)) {
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}




