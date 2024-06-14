/*
 * dc_motor.h
 *
 *  Created on: Oct 7, 2022
 *      Author: Mahmoud Reda
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include"std_types.h"
#define MOTOR_IN1_PORT_ID PORTB_ID
#define MOTOR_IN1_PIN_ID PIN6_ID
#define MOTOR_IN2_PORT_ID PORTB_ID
#define MOTOR_IN2_PIN_ID PIN7_ID

//enum contain all the states of the motor
typedef enum{
	stop,clockwise,anticlockwise
}DC_MOTOR_direction;

DC_MOTOR_direction state;

uint8 speed;

/*DcMotor_Init
 * description: the fun is responsible for initialize the values of the dc motors*/
void DcMotor_Init(void);

/*DcMotor_Rotate
 * description: the fun is responsible for determining the state of the motor and its speed*/
void DcMotor_Rotate(DC_MOTOR_direction state);

#endif /* DC_MOTOR_H_ */
