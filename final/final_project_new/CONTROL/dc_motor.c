/*
 * dc_motor.c
 *
 *  Created on: Oct 7, 2022
 *      Author: Mahmoud Reda
 */
#include"gpio.h"// to initialize the pins of h bridge
#include"common_macros.h"//to use macros
#include<avr\io.h>//to access the registers
#include"dc_motor.h"



/*DcMotor_Init
 * description: the fun is responsible for initialize the values of the dc motors
 *input: void
 * return void
 */
void DcMotor_Init(void)
{
	//initialize the direction of the pins which connected to H bridge to be output
	GPIO_setupPinDirection(MOTOR_IN1_PORT_ID,MOTOR_IN1_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_IN2_PORT_ID,MOTOR_IN2_PIN_ID,PIN_OUTPUT);
	//initially stop the dc-motor
	GPIO_writePin(MOTOR_IN1_PORT_ID,MOTOR_IN1_PIN_ID,LOGIC_LOW);
	GPIO_writePin(MOTOR_IN2_PORT_ID,MOTOR_IN2_PIN_ID,LOGIC_LOW);
}




/*DcMotor_Rotate
 * description: the fun is responsible for determining the state of the motor and its speed
 *input: The function is responsible for moving the motor according to the input speed and condition
 * return void
 */
void DcMotor_Rotate(DC_MOTOR_direction state)
{
	switch(state)
	{
	//access the pins according to the state
	case stop:
		GPIO_writePin(MOTOR_IN1_PORT_ID,MOTOR_IN1_PIN_ID,LOGIC_LOW);
		GPIO_writePin(MOTOR_IN2_PORT_ID,MOTOR_IN2_PIN_ID,LOGIC_LOW);
		break;
	case clockwise:
		GPIO_writePin(MOTOR_IN1_PORT_ID,MOTOR_IN1_PIN_ID,LOGIC_HIGH);
		GPIO_writePin(MOTOR_IN2_PORT_ID,MOTOR_IN2_PIN_ID,LOGIC_LOW);
		break;
	case anticlockwise:
		GPIO_writePin(MOTOR_IN1_PORT_ID,MOTOR_IN1_PIN_ID,LOGIC_LOW);
		GPIO_writePin(MOTOR_IN2_PORT_ID,MOTOR_IN2_PIN_ID,LOGIC_HIGH);
		break;
	}

	//the fun move the motor according to the speed which was entered By producing a specific PWM signal with specific duty cycle

}
