/*
 * buzzer.c
 *
 *  Created on: Nov 1, 2022
 *      Author: merna
 */
#include "buzzer.h"
#include "../MCAL/gpio.h"

/*
 * Setup the direction for the buzzer pin as output pin through the
 * GPIO driver.Turn off the buzzer through the GPIO.
 *
 */
void Buzzer_init()
{
	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}
/*
 * Function to enable the Buzzer through the GPIO.
 */
void Buzzer_on(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);

}
/*
 * Function to disable the Buzzer through the GPIO.
 */
void Buzzer_off(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);

}
