/*
 * uart.c
 *
 *  Created on: Oct 14, 2022
 *      Author: Mahmoud Reda
 */

#include"uart.h"
#include"std_types.h"
#include"common_macros.h"
#include<avr\io.h>
#include<avr\interrupt.h>
uint16 ubrr_value = 0;



void UART_sendByte(uint8 data)
{
#if(!(USART_interrupt_SENDER))
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}
	UDR = data;
#else

#endif
}

uint8 UART_receiveByte(void)
{
#if(!(USART_interrupt_RECEIVER))
	while(BIT_IS_CLEAR(UCSRA,RXC)){}
	return UDR;
#else
	return UDR;
#endif
}
void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;

	/* Send the whole string */
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
}
void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_receiveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_receiveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}
//void UART_init(uint32 baud_rate,const USART_ConfigType * Config_Ptr)
void UART_init(const UART_ConfigType * Config_Ptr)
{
#if(USARTASYNCDOUBLE_SPEED_MODE)
	SET_BIT(UCSRA,U2X);
#endif

#if(USART_interrupt_RECEIVER)
	SET_BIT(UCSRB,RXCIE);
	ISR(USART_RXC_vect)
	{
		data=UDR;
	}
#endif

#if(USART_interrupt_SENDER)
	SET_BIT(UCSRB,TXCIE);
#endif

#if(USART_EMPTY_INTERRUPT)
	SET_BIT(UCSRB,UDRIE);
	ISR(USART_UDRE_vect)
		{
		UDR = data;
		}
#endif
	SET_BIT(UCSRC,URSEL);
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN);
	CLEAR_BIT(UCSRB,UCSZ2);

#if(USARTSYNC_MODE)
	SET_BIT(UCSRC,UMSEL);
	UCSRC|=(Config_Ptr->clock<<UCPOL);
#endif
	UCSRC|=((Config_Ptr->parity)<<UPM0);
	UCSRC|=((Config_Ptr->stopbit)<<USBS);
	UCSRC|=((Config_Ptr->size)<<UCSZ0);
//UCSRC|=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
	//UCSRC|=(Config_Ptr->clock<<UCPOL);
#if(USartAycnNormal_MODE)
	ubrr_value = (uint16)(((F_CPU / ((Config_Ptr->baud_rate)* 16UL))) - 1);
#elif(USARTASYNCDOUBLE_SPEED_MODE)
	ubrr_value = (uint16)(((F_CPU / ((Config_Ptr->baud_rate) * 8UL))) - 1);
#elif(USARTSYNC_MODE)
	ubrr_value = (uint16)(((F_CPU / ((Config_Ptr->baud_rate) * 2UL))) - 1);
#endif
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;
}
