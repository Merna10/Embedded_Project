/*
 * himi.c
 *
 *  Created on: Seb 11, 2022
 *      Author: merna
 */

#include "himi.h"

uint8 Pass[SIZE],PassConfirm[SIZE],PassPrev[SIZE],check = 0,Buzzer_Flag=0;

void init(void) {

	LCD_init();
	UART_Config config = { DISABLED, ONE, EIGHT, 9600 };
	UART_init(&config);
	TIMER_ConfigType TIMERconfg = { TIMER_OVF,TIMER0,PRESCALAR_CLK64,0,0};
	Timer_init(&TIMERconfg);
}
void Enter_Pass(void) {
	uint8 i;
	while (1) {

		LCD_displayStringRowColumn(0, 0, "Enter Password");
		LCD_moveCursor(1, 0);
		for (i = 0; i < SIZE; i++) {
			Pass[i] = KEYPAD_getPressedKey();
			LCD_DisplayChar('*');
			_delay_ms(400);
		}
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "ReEnter Password");
		LCD_moveCursor(1, 0);
		for (i = 0; i < SIZE; i++) {
			//confirm password
			PassConfirm[i] = KEYPAD_getPressedKey();
			LCD_DisplayChar('*');
			_delay_ms(400);
		}
		for (i = 0; i < SIZE; i++) {
			if (Pass[i] == PassConfirm[i]) {
				check++;
			}
		}
		LCD_clearScreen();
		if (check == 5) {
			UART_sendByte(RECEIVEPASS);
			check = 0;
			for (i = 0; i < SIZE; i++) {
				UART_sendByte(Pass[i]);
				_delay_ms(10);
			}
			break; }

		check = 0;
		LCD_clearScreen();
		LCD_DisplayString("Invalid");
		_delay_ms(1000);
		LCD_clearScreen();

	}
}

void buzzer_handling(void) {
	Buzzer_Flag++;
	LCD_clearScreen();
	if (Buzzer_Flag == 3) {
		UART_sendByte(BUZZERON);
		Buzzer_Flag = 0;
	}
}
uint8 check_pass(void) {
	uint8 key;
	uint8 i;
	LCD_clearScreen();
	LCD_DisplayString("Enter Password");
	LCD_moveCursor(1, 0);
	for (i = 0; i < SIZE; i++) {
		PassPrev[i] = KEYPAD_getPressedKey();
		LCD_DisplayChar('*');
		_delay_ms(400);
	}
	UART_sendByte(CHECK_PASS);
	for (i = 0; i < SIZE; i++) {
		UART_sendByte(PassPrev[i]);
		_delay_ms(10);
	}
	key = UART_recieveByte();
	return (key);
}
void change_pass(void) {
	uint8 flag=0;
	uint8 key;
	for (uint8 i=0;i<3;i++){
		key=check_pass();
		_delay_ms(100);
		switch (key) {
		case CORRECT:
			Buzzer_Flag=0;
			flag=1;
			LCD_clearScreen();
			Enter_Pass();
			options();
			break;
		case WRONG:
			LCD_clearScreen();
			LCD_DisplayString("Try again");
			_delay_ms(1000);
			buzzer_handling();
			break;
		}
		if (flag==1){
			flag=0;
			break;
		}

	}
}

void handle_enigne(void) {
	uint8 flag = 0;
	uint8 checker=0;
	for (uint8 i = 0; i < 3; i++) {

		checker= check_pass();

		switch (checker) {
		case CORRECT:
			Buzzer_Flag = 0;
			flag = 1;
			UART_sendByte(OPENENGINE);
			LCD_clearScreen();
			LCD_DisplayString("Engine is ON");

			break;
		case WRONG:
			LCD_clearScreen();
			LCD_DisplayString("Try again");
			_delay_ms(1000);
			_delay_ms(500);
			buzzer_handling();

			break;
		}

		if (flag == 1) {
			flag = 0;
			break;
		}
	}
}
void options(void) {
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "+:Turn on Engine");
	LCD_displayStringRowColumn(1, 0, "-:Change Pass");

	switch (KEYPAD_getPressedKey()) {

	case '-': //change password
		_delay_ms(500);
		change_pass();
		break;
	case '+':
		_delay_ms(500);
		handle_enigne();
		break;
	default:
		options();
		break;
	}

}
