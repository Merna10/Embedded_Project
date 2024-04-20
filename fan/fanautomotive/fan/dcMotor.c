 /*
 * dcMotor.c
 *
 *  Created on: Oct 9, 2022
 *      Author: merna
 */
#include "common_macros.h"
#include "gpio.h"
#include "pwm.h"
#include "dcMotor.h"


void DcMotor_Init(void)
{
	GPIO_setupPinDirection (DC_PORT_ID,DC_ANTI_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection (DC_PORT_ID,DC_CLOCK_PIN_ID,PIN_OUTPUT);
	GPIO_writePin (DC_PORT_ID,DC_ANTI_PIN_ID,LOGIC_LOW);
	GPIO_writePin (DC_PORT_ID,DC_CLOCK_PIN_ID,LOGIC_LOW);

}

void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	PWM_Timer0_Start (speed);
	if (state == STOP)
	{
		/*Stop the motor*/
		GPIO_writePin (DC_PORT_ID,DC_ANTI_PIN_ID,LOGIC_LOW);
		GPIO_writePin (DC_PORT_ID,DC_CLOCK_PIN_ID,LOGIC_LOW);
	}

	else if (state == CLOCKWISE)
	{
		/*Rotate Clockwise*/
		GPIO_writePin (DC_PORT_ID,DC_ANTI_PIN_ID,LOGIC_LOW);
		GPIO_writePin (DC_PORT_ID,DC_CLOCK_PIN_ID,LOGIC_HIGH);

	}

	else if (state == ANTICLOCKWISE)
	{
		/*Rotate AntiClockwise*/
		GPIO_writePin (DC_PORT_ID,DC_ANTI_PIN_ID,LOGIC_HIGH);
		GPIO_writePin (DC_PORT_ID,DC_CLOCK_PIN_ID,LOGIC_LOW);
	}
}
