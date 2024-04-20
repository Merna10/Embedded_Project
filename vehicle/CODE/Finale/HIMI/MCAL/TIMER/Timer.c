/*
 * Timer.c
 *
 *  Created on: Oct 22, 2022
 *      Author: merna
 */

#include "Timer.h"
#include "../../LIB/common_macros.h" /* To use the macros like SET_BIT */
#include <avr/io.h> /* To use ICU/Timer1 Registers */
#include <avr/interrupt.h> /* For ICU ISR */
#include "../../MCAL/GPIO/gpio.h"
#define NUMBER_OF_OVERFLOWS_PER_HALF_SECOND 2
void (*Timer0_CALLBACK_Fptr)(void)=NULL_PTR;
static volatile void (*g_callBackPtr)(void) = NULL_PTR;
/**********************GLOBAL VARIABLES*******************************/
#define NULL_PTR ((void*)0)

uint32 g_tick;

ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}



void Timer_init(const TIMER_ConfigType *timer){

	switch (timer->number) {
	case TIMER0:
		TCNT0 = timer->initialCounter;
		TCCR0 = (TCCR0 & 0xF8) | (timer->prescaler);
		SET_BIT(TCNT0,0);
		if(timer->mode==TIMER_OVF)
		{
			SET_BIT(TCCR0,FOC0);
			TIMSK |= (1<<TOIE0)|(1<<timer->mode);
		}
		else if(timer->mode==TIMER_CTC)
		{
			SET_BIT(TCCR0,FOC0);
			TIMSK |= (1<<OCIE0)|(1<<timer->mode);
			OCR0 = timer->compareValue;
		}
		break;
	case TIMER1:
		TCNT1 = timer->initialCounter;
		TCCR1B = (TCCR1B & 0xF8) | (timer->prescaler);
		if(timer->mode==TIMER_OVF)
		{
			SET_BIT(TCCR1A, FOC1A);
			SET_BIT(TCCR1A, FOC1B);
			TIMSK |= (1<<TOIE1)|(1<<timer->mode);
		}
		else if(timer->mode==TIMER_CTC)
		{
			SET_BIT(TCCR1A, FOC1A);
			SET_BIT(TCCR1A, FOC1B);
			TIMSK |= (1<<OCIE1A)|(1<<timer->mode);
			OCR1A = timer->compareValue;
		}
		break;
	case TIMER2:
		TCNT2 = timer->initialCounter;
		TCCR2 = (TCCR0 & 0xF8) | (timer->prescaler);
		SET_BIT(TCNT0,0);
		if(timer->mode==TIMER_OVF)
		{
			SET_BIT(TCCR2,FOC2);
			TIMSK |= (1<<TOIE2)|(1<<timer->mode);
		}
		else if(timer->mode==TIMER_CTC)
		{
			SET_BIT(TCCR2,FOC2);
			TIMSK |= (1<<OCIE2)|(1<<timer->mode);
			OCR2 = timer->compareValue;
		}
		break;
	default:
		break;
	}

}

void Timer0_DeInit(void){
	TCCR0 = 0;
	TCNT0 = 0;
	OCR0 = 0;
	TIMSK=0;
}

void Delay_Timer(uint32 seconds){
	g_tick = 0;
	uint32 tick = seconds;
	Timer0_setCallBack(&timer0_tick);
	while(g_tick  < tick);
	Timer0_DeInit();
}
void Timer0_setCallBack(void(*a_ptr)(void)){
	Timer0_CALLBACK_Fptr=a_ptr;

}

void timer0_tick(void)
{
	g_tick++;
}
void PWM_Timer0_Start(uint8 duty_cycle)
{
	TCNT0 =0;
	/*Compare Value*/
	OCR0= ((float)duty_cycle / 100) * 255;
	/*TIMER0_PIN_ID as output*/
	GPIO_setupPinDirection (TIMER0_PORT_ID,TIMER0_PIN_ID,PIN_OUTPUT);
	TCCR0 |= (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}


/*
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

void Delay(uint32 seconds) {
	uint8 count;
	TCNT1 = 0;
	OCR1A = 65000;
	for (int i = 0; i < seconds; i++) {
		for (count = 0; count < 485; count++) {
			while (!(TIFR & (1 << OCF1A)));
			TIFR |= (1 << OCF1A);
		}
	}
}

void Timer1_setCallBack(void (*a_ptr)(void)) {
	g_callBackPtr = a_ptr;
}
 */



