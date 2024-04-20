/*
 * FanController.c
 *
 *  Created on: Oct 9, 2022
 *      Author: merna
 */

#include "adc.h"
#include "dcMotor.h"
#include "lcd.h"
#include "lm35_sensor.h"
#include "pwm.h"



/*FANSTATE*/

typedef enum
{
	OFF,ON
} FAN_STATE;


int main()
{
	uint8 temp = 0;
	FAN_STATE fanstate;
	ADC_ConfigType config = {INTERNAL , F_CPU8 };
	LCD_init();
	ADC_init (&config);
	DcMotor_Init();
	LCD_displayStringRowColumn (0,4, "FAN IS");
	LCD_displayStringRowColumn (1,4, "TEMP = ");
	while (1)
	{
		temp = LM35_getTemperature();
		if (fanstate == OFF)
		{
			LCD_displayStringRowColumn (0,11, "OFF");
		}
		else if (fanstate == ON)
		{
			LCD_displayStringRowColumn (0,11, "ON");
		}

		if (temp < 30)
		{
			fanstate = OFF;
			DcMotor_Rotate (STOP ,0);
		}

		else
		{
			fanstate = ON;
			LCD_DisplayChar(' ');
			if ((temp<60) && (temp >=30))
			{
				DcMotor_Rotate (CLOCKWISE ,25);
		    }

			else if ((temp<90) && (temp>=60))
			{
				DcMotor_Rotate (CLOCKWISE,50);
			}

			else if ((temp<120) && (temp>=90))
			{
				DcMotor_Rotate (CLOCKWISE ,75);
			}

			else if (temp>=120)
			{
				DcMotor_Rotate (CLOCKWISE ,100);
			}
		}

		LCD_moveCursor(1,11);
		if(temp>=100)
		{
			LCD_intgerToString(temp);
		}
		else
		{
			LCD_intgerToString(temp);
			LCD_DisplayChar(' ');
		}
	}



}
