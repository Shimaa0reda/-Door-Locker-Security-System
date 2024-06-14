/*
 * timer.h
 *
 *  Created on: Nov 4, 2022
 *      Author: Mahmoud Reda
 */
#include"std_types.h"
#ifndef TIMER_H_
#define TIMER_H_
#define CMP_UNITA 1
#define CMP_UNITB 0
typedef uint16 TIMER1_initialvalue;
typedef uint32 TIMER1_comparevalue;
typedef enum{
	no_prescaler,prescaler_1,prescaler_8,prescaler_64,prescaler_256,prescaler_1024
}Timer1_Prescaler;

typedef enum{
	Normal,Compare
}Timer1_Mode;

typedef struct {
	TIMER1_initialvalue initial_value;
	 TIMER1_comparevalue compare_value; // it will be used in compare mode only.
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;

void Timer1_init(const Timer1_ConfigType * Config_Ptr);
void Timer1_deInit(void);
void TIMER1_setCallBack(void(*a_ptr)(void));
void TIMER1_count(uint8 time);
#endif /* TIMER_H_ */
