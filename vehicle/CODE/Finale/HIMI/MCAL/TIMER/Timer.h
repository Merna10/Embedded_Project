/*
 * Timer.h
 *
 *  Created on: Oct 22, 2022
 *      Author: merna
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "../../LIB/std_types.h"

#define TIMER0_PORT_ID                 PORTB_ID
#define TIMER0_PIN_ID                  PIN3_ID

typedef enum{
	NOCLK=0x00,
	CLK_NOPRS=0x01,
	CLK_8=0x02,
	CLK_64=0x03,
	CLK_256=0x4,
	CLK_1024=0x05,
	EX_CLK_FALLING=0x06,
	EX_CLK_RISING=0x07
}TIMER_Prescaler;
typedef enum
{
	TIMER0,TIMER1,TIMER2
}TIMER_NUMBER;
typedef enum
{
	TIMER_OVF=0x00,
	TIMER_CTC=0x08,
	TIMER_PWM=0x40,
	TIMER_FAST_PWM=0x48
}TIMER_MODE;



typedef enum {
	NO_CLK_SRC,
	NO_PRESCALAR,
	PRESCALAR_CLK8,
	PRESCALAR_CLK64,
	PRESCALAR_CLK256,
	PRESCALAR_CLK1024,
	EXT_CLK_FALLING,
	EXT_CLK_RISING
} Timer_Prescaler;


typedef struct
{
	TIMER_MODE mode;
	TIMER_NUMBER number;
	TIMER_Prescaler prescaler;
	uint16 compareValue;
	uint16 initialCounter;
} TIMER_ConfigType;


/***               PROTOTYPE             ***/
void Timer_init(const TIMER_ConfigType *Config_Ptr  );
void Timer0_DeInit(void);
void Delay_Timer(uint32 seconds);
void Timer0_setCallBack(void(*a_ptr)(void));
void timer0_tick(void);
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* TIMER_H_ */
