


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "../../LIB/std_types.h"
#include "../../MCAL/TIMER/Timer.h"
#define DC_PORT_ID               PORTC_ID
#define DC_ANTI_PIN_ID           PIN5_ID
#define DC_CLOCK_PIN_ID          PIN4_ID



typedef enum{
	STOP, CLOCKWISE,ANTICLOCKWISE
}DcMotor_State;


/*    FUNCTION PROTOTYPES  */
void DcMotor_Init(void);

void DcMotor_Rotate(DcMotor_State);




#endif /* DC_MOTOR_H_ */
