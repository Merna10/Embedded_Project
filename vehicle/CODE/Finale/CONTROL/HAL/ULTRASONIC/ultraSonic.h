/*
 * ultraSonic.h
 *
 *  Created on: Seb 10, 2022
 *      Author: merna
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#include "../../LIB/std_types.h"
/*defintion*/

#define TRIGGER_PORT 	PORTD_ID
#define TRIGGER_PIN 	PIN5_ID

#define ECHO_PORT		PORTD_ID
#define ECHO_PIN		PIN6_ID

/*prototype*/
 void Ultrasonic_init(void);
 void Ultrasonic_Trigger(void);
 uint16 Ultrasonic_readDistance(void);
 void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_H_ */
