/*
 * ac_dc_motor.h
 *
 *  Created on: Sep 12, 2023
 *      Author: user
 */

#ifndef HAL_AC_DC_MOTOR_H_
#define HAL_AC_DC_MOTOR_H_

#include "../../LIB/std_types.h"
#include "../../MCAL/TIMER/Timer.h"
#define AC_DC_PORT_ID               PORTA_ID
#define AC_DC_ANTI_PIN_ID           PIN1_ID
#define AC_DC_CLOCK_PIN_ID          PIN0_ID



typedef enum{
	STOP1, CLOCKWISE1,ANTICLOCKWISE1
}AC_DcMotor_State;


/*    FUNCTION PROTOTYPES  */
void AC_DcMotor_Init(void);

void AC_DcMotor_Rotate(AC_DcMotor_State,uint8 speed);

#endif /* HAL_AC_DC_MOTOR_H_ */
