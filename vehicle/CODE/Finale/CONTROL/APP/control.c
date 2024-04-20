/*
 * control.c
 *
 *  Created on: Seb 11, 2022
 *      Author: merna
 */
#include "control.h"
#include <avr/interrupt.h>
#include <avr/io.h>

uint8 Pass_Save[SIZE],Pass_Recieved[SIZE],Pass_EEPROM[SIZE];
uint8 temp=0,distance=101;

void start(void) {
	UART_Config UARTconfig= { DISABLED, ONE, EIGHT, 9600 };
	UART_init(&UARTconfig);
	DcMotor_Init();
	LCD_init();
	AC_DcMotor_Init();
	ADC_ConfigType config = {F_CPU8,INTERNAL  };
	ADC_init (&config);
	Buzzer_init();
	Ultrasonic_init();
}

void receive_pass(void) {
	uint8 i;
	for (i = 0; i < SIZE; i++) {
		Pass_Save[i] = UART_recieveByte();
		_delay_ms(10);
	}
	for (i = 0; i < SIZE; i++) {
		EEPROM_writeByte(i, Pass_Save[i]);
		_delay_ms(10);
	}
}

void check_pass(void) {
	uint8 i;
	uint8 check=0;

	for (i = 0; i < SIZE; i++) {
		Pass_Recieved[i] = UART_recieveByte();
		_delay_ms(10);
	}
	for (i = 0; i < SIZE; i++) {
		EEPROM_readByte(i, &Pass_EEPROM[i]);
		_delay_ms(10);
	}
	for (i = 0; i < SIZE; i++){
		if (Pass_Recieved[i]==Pass_EEPROM[i]){
			check++;
		}

	}
	if (check==5) {
		UART_sendByte(CORRECT);

	}
	else {
		UART_sendByte(WRONG);
	}
	check=0;
}

void tempERA(void){
	_delay_ms(100);
/*
	Timer0_ConfigType config0={0,0,TIMER0_NORMAL_MODE,timer0_PRESCALAR_CLK8};
	Timer0_init(&config0);
*/
	SREG |= (1<<7);
	LCD_displayStringRowColumn (0,3, "TEMP is  ");

	AC_STATE acstate;
	Buzzer_off();
	while(1){
		distance = Ultrasonic_readDistance();

		temp = LM35_getTemperature();
		_delay_ms(100);

		if (temp <= 25 && temp>=10 )
		{
			acstate = OFF;
			AC_DcMotor_Rotate(STOP1,0);
		}
		else if (temp < 10 )
		{
			acstate = ON;
			AC_DcMotor_Rotate(ANTICLOCKWISE1,100);
		}

		else if (temp >25)
		{
			acstate = ON;
			LCD_DisplayChar(' ');
			AC_DcMotor_Rotate(CLOCKWISE1,100);
		}

		if((distance < 100 )&& (distance > 70 ))
		{

			Buzzer_on();
			_delay_ms(400);
			Buzzer_off();
			_delay_ms(500);
		}
		else if((distance < 70 )&& (distance > 40 ))
		{

			Buzzer_on();
			_delay_ms(300);
			Buzzer_off();
			_delay_ms(400);
		}
		else if((distance <= 40 )&& (distance > 10 ))
		{

			Buzzer_on();
			_delay_ms(100);
			Buzzer_off();
			_delay_ms(100);
		}
		else if((distance <= 10 )&& (distance >=0 ))
		{

			Buzzer_on();
		}


		LCD_moveCursor(0, 11);
		LCD_intgerToString(temp);
		LCD_DisplayChar(' ');
	}
}


