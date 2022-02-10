/******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timer.c
 *
 * Description: Source file for the timer Driver
 *
 * Author: Hazem Hisham
 *
 *******************************************************************************/
#include "timer.h"
#include "common_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "std_types.h"
static volatile void(*g_callBackPtr)(void)=NULL_PTR;
static volatile uint8 g_initialTimerValue;

/*Timer overflow ISR*/
ISR(TIMER0_OVF_vect){
	TCNT0=g_initialTimerValue;
	if(g_callBackPtr!=NULL_PTR){
		(*g_callBackPtr)();
	}
}

/*Timer Compare Mode ISR*/
ISR(TIMER0_COMP_vect){
	TCNT0=g_initialTimerValue;
	if(g_callBackPtr!=NULL_PTR){
		(*g_callBackPtr)();
	}
}

/*Function Responsible for Initializing timer module according to Required mode and Passed structure*/
void Timer0_init(const Timer0_ConfigType *ConfigPtr ){
	/*Set initial Value of  Counter*/
	TCNT0=ConfigPtr->initialValue;
	g_initialTimerValue=ConfigPtr->initialValue;
	/*Set prescaler for Timer and Applying Non PWM mode*/
	TCCR0|=(1<<FOC0)|(ConfigPtr->preScaler);
	CLEAR_BIT(TCCR0,WGM00);
	/*Case of Normal mode(Overflow)*/
	if(ConfigPtr->mode==NORMAL){
		CLEAR_BIT(TCCR0,WGM01);
		/*Enabling Overflow Interrupt enable*/
		SET_BIT(TIMSK,TOIE0);
	}
	/*In case of Compare mode*/
	else{
		/*Setting Compare Value to value in passed Structure*/
		OCR0=ConfigPtr->compareValue;
		SET_BIT(TCCR0,WGM01);
		/*Enabling Output compare match Interrupt Enable*/
		SET_BIT(TIMSK,OCIE0);
	}
}
/*Function Responsible To disable Timer after each Mode*/
void Timer0_Deinit(){
	TCCR0=0;
	CLEAR_BIT(TIMSK,OCIE0);
	CLEAR_BIT(TIMSK,TOIE0);
}
/*Function used to Set Call Back Function according to passed function*/
void Timer0_setCallBack(void(*a_ptr)(void)){
	g_callBackPtr=a_ptr;
}
