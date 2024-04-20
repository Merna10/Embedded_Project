/*
 * pwm.h
 *
 *  Created on: Oct 9, 2022
 *      Author: merna
 */

#ifndef PWM_H_
#define PWM_H_
#define TIMER0_PORT_ID                 PORTB_ID
#define TIMER0_PIN_ID                  PIN3_ID
#include "std_types.h"



/*prototype*/

void PWM_Timer0_Start(uint8 duty_cycle);


#endif /* PWM_H_ */
