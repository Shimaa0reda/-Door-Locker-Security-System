
/*
 * main.c
 *
 *  Created on: Nov 9, 2022
 *      Author: Mahmoud Reda
 */
#include"std_types.h"
#include<util\delay.h>
#include"lcd.h"
#include"keypad.h"
#include"gpio.h"
#include<avr\interrupt.h>
#include"uart.h"
#include"timer.h"
#define unmatched 0
#define matched 1
uint8 array[5];
uint8 re_enter[5];
uint8 check[5];
uint8 i=0,check_bit1=0,false_attempts=0,option=0,check_bit2=0;
uint8 tick=0;
Timer1_ConfigType Config_Ptr_time1 = {0,0,prescaler_1024,Normal};
Timer1_ConfigType Config_Ptr_time2 = {13884,0,prescaler_1024,Normal};
Timer1_ConfigType Config_Ptr_time3 = {42099,0,prescaler_1024,Normal};
Timer1_ConfigType Config_Ptr_time4 = {55538,0,prescaler_1024,Normal};
void time()
{tick++;
	}
int main()
{
	LCD_init();
	SREG|=(1<<7);
	UART_ConfigType Config_Ptr_2 ={Disabled,one_bit,bit_8,9600};
	UART_init(&Config_Ptr_2);
	uint8 i=0;

while(1){
//**************************************first system*******************************************************

	do{
		check_bit1=matched;
		/*Get the password from user and send it to the Control_ECU*/
		LCD_displayStringRowColumn(0, 0, "plz enter pass");
		_delay_ms(500);
		LCD_moveCursor(1, 0);

		for(i=0;i<5;i++)
		{array[i]=KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		_delay_ms(500);
		}

		while(KEYPAD_getPressedKey()!='+');

		if(KEYPAD_getPressedKey()=='+')//+ is enter key

			LCD_clearScreen();

		//re-enter the pass to check
		LCD_displayString("plz re-enter the");
		LCD_moveCursor(1, 0);
		LCD_displayString("same pass");
		_delay_ms(1000);

		for(i=0;i<5;i++)
		{
			LCD_moveCursor(2, i);
			re_enter[i]=KEYPAD_getPressedKey();
			LCD_displayCharacter('*');
			_delay_ms(500);
		}

		while(KEYPAD_getPressedKey()!='+');

		LCD_clearScreen();

		for(i=0;i<5;i++)
			UART_sendByte(array[i]);

		for(i=0;i<5;i++)
			UART_sendByte(re_enter[i]);

		/*Check if the entering password and the re-entering password are the same*/
		check_bit1 =UART_receiveByte();

		LCD_clearScreen();

	}

	while(check_bit1 == unmatched);

//**************************************second system**********************************************

while(1)
{
	check_bit2=matched;
false_attempts=0;
_delay_ms(500);
//display main options of the LCD
LCD_displayString("+:open door");
LCD_moveCursor(1, 0);
LCD_displayString("-:change pass");
while(!(KEYPAD_getPressedKey()=='+'||KEYPAD_getPressedKey()=='-'));

//get the option from the user
option=KEYPAD_getPressedKey();

switch(option)
{
//in case the user chose to open the door
case'+':

	do{
		//send option to the other mc
		UART_sendByte(option);
		LCD_clearScreen();
		_delay_ms(500);

		//ask the user to enter the password
		LCD_displayString("plz enter pass:");
		LCD_moveCursor(1, 0);

		for(i=0;i<5;i++)
		{check[i]=KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		_delay_ms(500);}
//wait until the user press on the enter key
		while(KEYPAD_getPressedKey()!='+');
		LCD_clearScreen();
		_delay_ms(500);

		//send the password to the other mc
		for(i=0;i<5;i++)
			UART_sendByte(check[i]);

		//check if the entered password is matched with the password of the system
		check_bit2=UART_receiveByte();

		if(check_bit2==matched)
			{false_attempts=0;

	//display a message on the screen "door is unlocking" for 15 seconds
		LCD_displayString("door is unlocking");

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

		LCD_clearScreen();

		//hold the motor for 3 seconds

		Timer1_init(&Config_Ptr_time3);
		TIMER1_setCallBack(time);
		while(tick < 1);
		tick = 0;
		Timer1_deInit();
		//display a message on the screen "door is locking" for 15 seconds
		LCD_displayString("door is locking");

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

		LCD_clearScreen();;
		break;}
else{
	false_attempts++;
	if (false_attempts<3)
		continue;

		else{
			//start timer1 to calculate 8.4 sec
			Timer1_init(&Config_Ptr_time1);
			TIMER1_setCallBack(time);
		//display error message on the screen
			LCD_displayString("error");
			//now we calculated 7*8.4=58.8sec
			while(tick<7);
			tick=0;
			Timer1_deInit();
			//add 1.2 sec so total time calculated = 1 minute
			Timer1_init(&Config_Ptr_time4);
			TIMER1_setCallBack(time);
			while(tick<1);
			tick=0;
			Timer1_deInit();
			false_attempts=0;
			LCD_clearScreen();
			break;
		}
}}
while(false_attempts<3);
	break;
	//in case user choose to change the password
case'-':
	do{
		//send option to the other mc
		UART_sendByte(option);
		LCD_clearScreen();
		_delay_ms(500);

		//ask the user to enter the password
		LCD_displayString("plz enter pass:");
		LCD_moveCursor(1, 0);

		for(i=0;i<5;i++)
		{check[i]=KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		_delay_ms(500);}
		//wait until the user press on the enter key
		while(KEYPAD_getPressedKey()!='+');
		LCD_clearScreen();
		_delay_ms(500);

		//send the password to the other mc
		for(i=0;i<5;i++)
			UART_sendByte(check[i]);

		//check if the entered password is matched with the password of the system
		check_bit2=UART_receiveByte();
if(check_bit2==matched)
{
	false_attempts=0;
	do{
		LCD_displayStringRowColumn(0, 0, "plz enter pass");
				_delay_ms(500);
				LCD_moveCursor(1, 0);

				for(i=0;i<5;i++)
				{array[i]=KEYPAD_getPressedKey();
				LCD_displayCharacter('*');
				_delay_ms(500);
				}

				while(KEYPAD_getPressedKey()!='+');

				if(KEYPAD_getPressedKey()=='+')//+ is enter key

					LCD_clearScreen();

				//re-enter the pass to check
				LCD_displayString("plz re-enter the");
				LCD_moveCursor(1, 0);
				LCD_displayString("same pass");
				_delay_ms(1000);

				for(i=0;i<5;i++)
				{
					LCD_moveCursor(2, i);
					re_enter[i]=KEYPAD_getPressedKey();
					LCD_displayCharacter('*');
					_delay_ms(500);
				}

				while(KEYPAD_getPressedKey()!='+');

				LCD_clearScreen();

				for(i=0;i<5;i++)
					UART_sendByte(array[i]);

				for(i=0;i<5;i++)
					UART_sendByte(re_enter[i]);

				/*Check if the entering password and the re-entering password are the same*/
				check_bit2 =UART_receiveByte();

				LCD_clearScreen();

			}

			while(check_bit2 == unmatched);
break;
}
else
{
false_attempts++;
if(false_attempts<3)
	continue;
else{
	//start timer1 to calculate 8.4 sec
	Timer1_init(&Config_Ptr_time1);
	TIMER1_setCallBack(time);
	//display error message on the screen
	LCD_displayString("error");
	//now we calculated 7*8.4=58.8sec
	while(tick<7);
	tick=0;
	Timer1_deInit();
	//add 1.2 sec so total time calculated = 1 minute
	Timer1_init(&Config_Ptr_time4);
	TIMER1_setCallBack(time);
	while(tick<1);
	tick=0;
	Timer1_deInit();
	false_attempts=0;
	LCD_clearScreen();
	break;

}
}

	}
	while(false_attempts<3);
	break;




}

}

}}
