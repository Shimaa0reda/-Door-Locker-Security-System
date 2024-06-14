/*
 * BUZZER.c
 *
 *  Created on: Nov 4, 2022
 *      Author: Mahmoud Reda
 */
#include"BUZZER.h"
#include"gpio.h"
#include"std_types.h"
/*
 * Description :
 * function to initialize the buzzer
 */
void Buzzer_init()
{
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID,PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);

	}
/*
 * Description :
 * function to fire the buzzer
 */
void Buzzer_on(void)
{
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_HIGH);

}
/*
 * Description :
 * function to stop the buzzer
 */
void Buzzer_off(void)
{
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);
	}
