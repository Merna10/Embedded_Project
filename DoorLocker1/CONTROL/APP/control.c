/*
 * control.c
 *
 *  Created on: Nov 6, 2022
 *      Author: merna
 */
#include "control.h"

uint8 Pass_Save[SIZE],Pass_Recieved[SIZE],Pass_EEPROM[SIZE];

void start(void) {
	UART_Config UARTconfig= { DISABLED, ONE, EIGHT, 9600 };
	UART_init(&UARTconfig);
	I2C_Config configr = { 400000, 0x01 };
	TWI_init(&configr);
	DcMotor_Init();
	Timer_config TIMERconfg = { CTC,PRESCALAR_CLK1024,0,7813};
	Timer1_init(&TIMERconfg);
	Buzzer_init();
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


void rotate(void){

	DcMotor_Rotate(CLOCKWISE);
	for (int var = 0; var < 15; var++) {
		_delay_ms(1000);
	}
	DcMotor_Rotate(STOP);
	for (int var = 0; var < 3; var++) {
		_delay_ms(1000);
	}
	DcMotor_Rotate(ANTICLOCKWISE);
	for (int var = 0; var < 15; var++) {
		_delay_ms(1000);
	}
	DcMotor_Rotate(STOP);


}

