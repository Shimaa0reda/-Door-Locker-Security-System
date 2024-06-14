/*
 * timer.c
 *
 *  Created on: Nov 4, 2022
 *      Author: Mahmoud Reda
 */
#include"timer.h"
#include"std_types.h"
#include"avr\io.h"
#include"avr\interrupt.h"
static volatile void (*g_callBackPtr)(void) = NULL_PTR;
ISR(TIMER1_OVF_vect)/*handler overflow interrupt of timer0 */
{
	if(g_callBackPtr != NULL_PTR)
			(*g_callBackPtr)();
}
ISR (TIMER1_COMPA_vect)/*handler output compare  interrupt of timer0 */
{
	if(g_callBackPtr != NULL_PTR)
			(*g_callBackPtr)();
}
ISR(TIMER1_COMPB_vect)/*handler overflow interrupt of timer0 */
{
	if(g_callBackPtr != NULL_PTR)
			(*g_callBackPtr)();
}
/*
 * Description :
 * initialize timer1 compare and overflow mode.
 */

void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	TCCR1A |= (1<<FOC1A)|(1<<FOC1B);
	if((Config_Ptr->mode)==Compare)
	{
		TCNT1 =Config_Ptr->initial_value;
		TCCR1B = (1<<WGM12) ;
#if(CMP_UNITA)
		OCR1B =Config_Ptr->compare_value;
		TCCR1A|=(1<<COM1A1);
		TIMSK |= (1<<OCIE1A);
#elif(CMP_UNITB)
		OCR1B =Config_Ptr->compare_value;
		TCCR1A|=(1<<COM1B1);
		TIMSK |= (1<<OCIE1B);
#endif
		TCCR1B &=0xF8 ;
		TCCR1B |=Config_Ptr->prescaler;
	}

	else if((Config_Ptr->mode)==Normal)
	{
		TCNT1 =Config_Ptr->initial_value;
		TIMSK |= (1<<TOIE1);
		TCCR1B &=0xF8 ;
		TCCR1B |=(Config_Ptr->prescaler);
	}

		}
/*
 * Description :
 * de initialize timer1 compare and overflow mode.
 */
void Timer1_deInit(void)
	{
TCCR1B&=~(1<<CS10)&~(1<<CS11)&~(1<<CS12);
}

void TIMER1_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr  ;
}
