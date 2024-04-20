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

typedef enum
{
	TIMER0_NORMAL_MODE=0,
	TIMER0_PWM_PHASE_COTROL=1,
	TIMER0_COMPARE_MODE=2,
	TIMER0_FAST_PWM_MODE=3
}Timer0_Modes;

typedef enum
{
	timer0_NO_CLK_SRC,
	timer0_NO_PRESCALAR,
	timer0_PRESCALAR_CLK8,
	timer0_PRESCALAR_CLK64,
	timer0_PRESCALAR_CLK256,
	timer0_PRESCALAR_CLK1024,
	timer0_EXT_CLK_FALLING,
	timer0_EXT_CLK_RISING

}Timer0_PRESCALAR;

typedef struct
{
	uint16 initial_value;
	uint16 compare_value; // it will be used in compare mode only.
	Timer0_Modes mode;
	Timer0_PRESCALAR prescaler;
}Timer0_ConfigType;


/***               PROTOTYPE             ***/
void Timer0_init(const Timer0_ConfigType *Config_Ptr  );
void Timer0_deInit(void);
void Delay_Timer(uint32 seconds);
void Timer0_setCallBack(void(*a_ptr)(void));
void timer0_tick(void);
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* TIMER_H_ */
