/*
 * himi.h
 *
 *  Created on: Seb 11, 2022
 *      Author: merna
 */

#ifndef HIMI_H_
#define HIMI_H_
#define F_CPU 8000000UL
#include "../MCAL/UARY/uart.h"
#include "../HAL/KEYPAD/keypad.h"
#include "../HAL/LCD/lcd.h"
#include "../MCAL/TIMER/Timer.h"
#include <util/delay.h>
#include "../MCAL/GPIO/gpio.h"

#define SIZE 5
#define RECEIVEPASS 0x01
#define CHECK_PASS 2
#define OPENENGINE 3
#define CORRECT 4
#define WRONG 6
#define BUZZERON 7

void init(void);
void Enter_Pass(void);
void buzzer_handling(void);
uint8 check_pass(void);
void change_pass(void) ;
void handle_enigne(void);
void options(void);

#endif /* HIMI_H_ */
