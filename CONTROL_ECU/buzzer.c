/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.c
 *
 * Description: source file for the BUZZER
 *
 * Author: Hazem Hisham
 *
 *******************************************************************************/

#include "buzzer.h"

/*Function Responsible for Initializing Buzzer */
void Buzzer_init(){
	GPIO_setupPinDirection(BUZZER_PORT, BUZZER_PIN, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_LOW);
}

/*Function Responsible for turning The Buzzer ON*/
void Buzzer_ON(){
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_HIGH);
}

/*Function Responsible for turning The Buzzer OFF*/
void Buzzer_OFF(){
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,0);
}
