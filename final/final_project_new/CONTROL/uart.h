/*
 * uart.h
 *
 *  Created on: Oct 14, 2022
 *      Author: Mahmoud Reda
 */

#ifndef UART_H_
#define UART_H_

#include"std_types.h"
#define USartAycnNormal_MODE 0
#define USARTASYNCDOUBLE_SPEED_MODE 1
#define USARTSYNC_MODE 0
#define USART_interrupt_RECEIVER 0
#define USART_interrupt_SENDER 0
#define USART_EMPTY_INTERRUPT 0

typedef enum{
	bit_5,bit_6,bit_7,bit_8
}UART_character_size;
typedef enum{
	Disabled,Reserved,Even,Odd
}UART_parity_mode;
typedef enum{
	one_bit,two_bit
}UART_stop_bit;

//typedef enum{
//	rising_falling,falling_rising
//}USART_clock_polarity;
typedef struct{

#if(USARTSYNC_MODE)
	//USART_clock_polarity clock;
#endif
#if(USARTASYNCDOUBLE_SPEED_MODE)
	UART_parity_mode parity;
	UART_stop_bit stopbit;
	UART_character_size size;
	uint32 baud_rate;
#endif
}UART_ConfigType;

//void UART_init(uint32 baud_rate,const USART_ConfigType * Config_Ptr);
void UART_init(const UART_ConfigType * Config_Ptr);
void UART_sendByte(uint8 data);
uint8 UART_receiveByte(void);
void UART_sendString(const uint8 *Str);
void UART_receiveString(uint8 *Str);


#endif /* UART_H_ */
