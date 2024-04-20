/*
 * ultraSonic.c
 *
 *  Created on: Oct 14, 2022
 *      Author: merna
 */

#include "ultraSonic.h"
#include "gpio.h"
#include "icu.h"
#include <avr/delay.h>

uint16 time;
uint16 distance;

void Ultrasonic_init(void)
{
	Icu_ConfigType config = {F_CPU_8,RISING};
	GPIO_setupPinDirection(TRIGGER_PORT, TRIGGER_PIN, PIN_OUTPUT);
	GPIO_writePin(TRIGGER_PORT, TRIGGER_PIN, LOGIC_LOW);
	GPIO_setupPinDirection(ECHO_PORT, ECHO_PIN, PIN_INPUT);
	Icu_init(&config);
	Icu_setCallBack(&Ultrasonic_edgeProcessing);
}
void Ultrasonic_Trigger(void)
{
	GPIO_writePin(TRIGGER_PORT, TRIGGER_PIN, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(TRIGGER_PORT, TRIGGER_PIN, LOGIC_LOW);
}

uint16 Ultrasonic_readDistance(void)
{
	Ultrasonic_Trigger();
	Icu_setEdgeDetectionType(RISING);
	/*(34400*timer)/2
	   17200*timer
	   17200*(ticks)*10^-6
	   distance=time*0.0172
	 */
	distance=time*0.0172;
	return (distance+1);

}
void Ultrasonic_edgeProcessing(void)
{
	time = Icu_getInputCaptureValue();
	Icu_clearTimerValue();
	Icu_setEdgeDetectionType(FALLING);
}
