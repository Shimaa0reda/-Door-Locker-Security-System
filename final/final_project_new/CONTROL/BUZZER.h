/*
 * BUZZER.h
 *
 *  Created on: Nov 4, 2022
 *      Author: Mahmoud Reda
 */

#ifndef BUZZER_H_
#define BUZZER_H_
#define BUZZER_PORT_ID PORTD_ID
#define BUZZER_PIN_ID  PIN2_ID
void Buzzer_init();
void Buzzer_on(void);
void Buzzer_off(void);


#endif /* BUZZER_H_ */
