/*
 * control.h
 *
 *  Created on: Seb 11, 2022
 *      Author: merna
 */

#ifndef CONTROL_H_
#define CONTROL_H_
#define F_CPU 8000000UL
#include "../HAL/BUZZER/buzzer.h"
#include "util/delay.h"
#include "../MCAL/UARY/uart.h"
#include "../MCAL/GPIO/gpio.h"
#include "../MCAL/ADC/adc.h"
#include "../MCAL/I2C/twi.h"
#include "../HAL/EEPROM/external_eeprom.h"
#include "../HAL/LM35/lm35_sensor.h"
#include "../HAL/MOTOR/dc_motor.h"
#include "../HAL/ULTRASONIC/ultraSonic.h"
#include "../HAL/MOTOR/ac_dc_motor.h"
#include "../HAL/LCD/lcd.h"
#include "../MCAL/TIMER/Timer.h"
typedef enum
{
	OFF,ON
} AC_STATE;

#define SIZE 5
#define RECEIVEPASS 0x01
#define CHECK_PASS 2
#define OPENENGINE 3
#define CORRECT 4
#define WRONG 6
#define BUZZERON 7

void TIMER1_CallBack(void);
void start(void);
void receive_pass(void);
void check_pass(void);
void rotate(void);
void tempERA(void);
void Distance(void);

#endif /* CONTROL_H_ */
