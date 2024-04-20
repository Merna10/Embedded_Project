/*
 * main.c
 *
 *  Created on: Seb 12, 2022
 *      Author: merna
 */

#include "APP/control.h"



int main(void){
	start();
	_delay_ms(50);
	while(1){
		switch (UART_recieveByte()){

		case RECEIVEPASS:
			receive_pass();
			break;

		case CHECK_PASS:
			check_pass();
			break;

		case OPENENGINE:
			DcMotor_Rotate(CLOCKWISE);
			tempERA();
			break;

		case BUZZERON:
			Buzzer_on();
			for (int var = 0; var < 15; var++) {
				_delay_ms(1000);
			}
			Buzzer_off();
		}

	}

}


