 /******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.h
 *
 * Description: header file for the BUZZER
 *
 * Author: Hazem Hisham
 *
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_
#include "gpio.h"
#define BUZZER_PORT		PORTC_ID
#define BUZZER_PIN		PIN3_ID

/*Function Responsible for Initializing Buzzer */
void Buzzer_init();

/*Function Responsible for turning The Buzzer ON*/
void Buzzer_ON();

/*Function Responsible for turning The Buzzer OFF*/
void Buzzer_OFF();



#endif /* BUZZER_H_ */
