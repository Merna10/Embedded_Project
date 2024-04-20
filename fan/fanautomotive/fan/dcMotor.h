 /*
 * dcMotor.h
 *
 *  Created on: Oct 9, 2022
 *      Author: merna
 */
#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "std_types.h"

#define DC_PORT_ID                 PORTB_ID
#define DC_ANTI_PIN_ID             PIN1_ID
#define DC_CLOCK_PIN_ID            PIN0_ID


typedef enum
{
	STOP , CLOCKWISE , ANTICLOCKWISE
}DcMotor_State;

/*Prototypes*/

void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DCMOTOR_H_ */
