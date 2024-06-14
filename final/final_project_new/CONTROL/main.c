/*
 * main.c
 *
 *  Created on: Nov 9, 2022
 *      Author: Mahmoud Reda
 */
#include"uart.h"
#include"util\delay.h"
#include"gpio.h"
#include"common_macros.h"
#include"std_types.h"
#include"external_eeprom.h"
#include"dc_motor.h"
#include"BUZZER.h"
#include"timer.h"
#include<avr/io.h>
#define unmatched 0
#define matched 1
//#define i_am_ready 7
extern uint8 array_2[5];
extern uint8 check_2[5];
uint8 array_2[5];
 uint8 check_2[5];
 uint8 re_enter_2[5];
uint8 j=0,check_bit=0,false_attempts=0,option=0,check_bit2=0;
uint8 tick=0;
Timer1_ConfigType Config_Ptr_time1 = {0,0,prescaler_1024,Normal};
Timer1_ConfigType Config_Ptr_time2 = {13884,0,prescaler_1024,Normal};
Timer1_ConfigType Config_Ptr_time3 = {42099,0,prescaler_1024,Normal};
Timer1_ConfigType Config_Ptr_time4 = {55538,0,prescaler_1024,Normal};
void time()
{
	tick++;
	}
int main()
{
	Buzzer_init();
	DcMotor_Init();
	UART_ConfigType Config_Ptr_2 ={Disabled,one_bit,bit_8,9600};
	UART_init(&Config_Ptr_2);
	SREG|=(1<<7);
while(1){
//**************************************first system*******************************************************
do{
	check_bit=matched;
	for(j=0;j<5;j++)
		array_2[j]=UART_receiveByte();

	for(j=0;j<5;j++)
		re_enter_2[j]=UART_receiveByte();

	for(j=0;j<5;j++)
	{
		if(array_2[j]!=re_enter_2[j])

		{
			check_bit=unmatched;
			UART_sendByte(check_bit);
		}
		break;
	}
	if(check_bit==matched)
	{UART_sendByte(check_bit);
		for(j=0;j<5;j++)
			EEPROM_writeByte(0x0311+j,array_2[j]);
	}
}

	while(check_bit ==unmatched);
//**************************************second system**********************************************
while(1)
{check_bit2=matched;
	//receive the option from the other mc
	option=UART_receiveByte();
	//get the saved password from eeprom
 for(j=0;j<5;j++)
	 EEPROM_readByte(0x0311+j,array_2+j);

 //receive the password from the other mc
 for(j=0;j<5;j++)
	check_2[j]=UART_receiveByte();
//check if the entered password is matched with the password of the system
	for(j = 0 ;j < 5 ; j++){
		if(array_2[j]!= check_2[j]){
			{check_bit2=unmatched;
			UART_sendByte(check_bit2);
			}
			break;
		}}
		if(check_bit2!=unmatched)
		{
			UART_sendByte(check_bit2);
			false_attempts=0;

	switch(option)
	{
	case'+':
		//rotate the motor cw for 15 sec
		DcMotor_Rotate(clockwise);
		//calculate 8.4 sec
		Timer1_init(&Config_Ptr_time1);
		TIMER1_setCallBack(time);
		while(tick < 1);
		tick = 0;
		Timer1_deInit();

		//calculate 6.6 sec so the total seconds calculated = 6.6+8.4=15sec
		Timer1_init(&Config_Ptr_time2);
		TIMER1_setCallBack(time);
		while(tick < 1);
		tick = 0;
		Timer1_deInit();

		//hold the motor for 3 seconds
		DcMotor_Rotate(stop);
		Timer1_init(&Config_Ptr_time3);
		TIMER1_setCallBack(time);
		while(tick < 1);
		tick = 0;
		Timer1_deInit();

		//rotate the motor anti-cw for 15 sec
		DcMotor_Rotate(anticlockwise);
		//calculate 8.4 sec
		Timer1_init(&Config_Ptr_time1);
		TIMER1_setCallBack(time);
		while(tick < 1);
		tick = 0;
		Timer1_deInit();

		//calculate 6.6 sec so the total seconds calculated = 6.6+8.4=15sec
		Timer1_init(&Config_Ptr_time2);
		TIMER1_setCallBack(time);
		while(tick < 1);
		tick = 0;
		Timer1_deInit();
		DcMotor_Rotate(stop);
		_delay_ms(500);
		break;
	case'-':
		do{
			check_bit2=matched;
			for(j=0;j<5;j++)
				array_2[j]=UART_receiveByte();

			for(j=0;j<5;j++)
				re_enter_2[j]=UART_receiveByte();

			for(j=0;j<5;j++)
			{
				if(array_2[j]!=re_enter_2[j])

				{
					check_bit2=unmatched;
					UART_sendByte(check_bit2);
				}
				break;
			}

			if(check_bit==matched)
			{UART_sendByte(check_bit2);
			for(j=0;j<5;j++)
				EEPROM_writeByte(0x0311+j,array_2[j]);
			}


		}
		while(check_bit2==unmatched);

		break;



	}

		}
		else{
			UART_sendByte(check_bit2);
			false_attempts++;

			if(false_attempts==3)
			{
				//activate buzzer for 1 minute
				Buzzer_on();
				//start timer1 to count 7*8.4sec=58.8 sec
				Timer1_init(&Config_Ptr_time1);
				TIMER1_setCallBack(time);
				while(tick < 7);
				tick = 0;
				Timer1_deInit();
				//start timer1 to count 1.2sec so total time counted = 1 min
				Timer1_init(&Config_Ptr_time4);
				TIMER1_setCallBack(time);
				while(tick < 1);
				tick = 0;
				Timer1_deInit();
				//turn off the buzzer
				Buzzer_off();

			}



		}
}}}
