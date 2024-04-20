/*
 * ac_dc_motor.c
 *
 *  Created on: Sep 12, 2023
 *      Author: merna
 */
#include "../../LIB/common_macros.h"
#include "../../MCAL/GPIO/gpio.h"
#include "ac_dc_Motor.h"


void AC_DcMotor_Init(void)
{
	GPIO_setupPinDirection (AC_DC_PORT_ID,AC_DC_ANTI_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection (AC_DC_PORT_ID,AC_DC_CLOCK_PIN_ID,PIN_OUTPUT);
	GPIO_writePin (AC_DC_PORT_ID,AC_DC_ANTI_PIN_ID,LOGIC_LOW);
	GPIO_writePin (AC_DC_PORT_ID,AC_DC_CLOCK_PIN_ID,LOGIC_LOW);

}

void AC_DcMotor_Rotate(AC_DcMotor_State state,uint8 speed)
{
	PWM_Timer0_Start (speed);
	if (state == STOP1)
	{
		/*Stop the motor*/
		GPIO_writePin (AC_DC_PORT_ID,AC_DC_ANTI_PIN_ID,LOGIC_LOW);
		GPIO_writePin (AC_DC_PORT_ID,AC_DC_CLOCK_PIN_ID,LOGIC_LOW);
	}

	else if (state == CLOCKWISE1)
	{
		/*Rotate Clockwise*/
		GPIO_writePin (AC_DC_PORT_ID,AC_DC_ANTI_PIN_ID,LOGIC_LOW);
		GPIO_writePin (AC_DC_PORT_ID,AC_DC_CLOCK_PIN_ID,LOGIC_HIGH);

	}

	else if (state == ANTICLOCKWISE1)
	{
		/*Rotate AntiClockwise*/
		GPIO_writePin (AC_DC_PORT_ID,AC_DC_ANTI_PIN_ID,LOGIC_HIGH);
		GPIO_writePin (AC_DC_PORT_ID,AC_DC_CLOCK_PIN_ID,LOGIC_LOW);
	}
}
