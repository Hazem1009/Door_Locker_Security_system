/******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timer.h
 *
 * Description: header file for the timer Driver
 *
 * Author: Hazem Hisham
 *
 *******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_
#include "std_types.h"
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Timer0_PreScaler;

typedef enum{
	NORMAL,COMPARE
}Timer0_Mode;
typedef struct{
	/*A member for defining Mode of Timer*/
	Timer0_Mode mode;
	/*A member for defining Prescaler of Timer*/
	Timer0_PreScaler preScaler;
	/*A member for defining initial value of timer in TCNT0*/
	uint8 initialValue;
	/*A member for Compare Value*/
	uint8 compareValue;
}Timer0_ConfigType;


void Timer0_init(const Timer0_ConfigType *ConfigPtr );

void Timer0_setCallBack(void(*a_ptr)(void));

void Timer0_Deinit();

#endif /* TIMER_H_ */
