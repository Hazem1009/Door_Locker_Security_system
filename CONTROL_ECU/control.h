/******************************************************************************
 *
 * Module: CONTROL_ECU
 *
 * File Name: control.h
 *
 * Description: Header file CONTROL ECU
 *
 * Author: Hazem Hisham
 *
 *******************************************************************************/

#ifndef CONTROL_H_
#define CONTROL_H_
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define NUMBER_OF_OVERFLOWS_PER_THREE_SECOND 92
#define NUMBER_OF_OVERFLOWS_PER_ONE_MINUTE 1832
#define NUMBER_OF_OVERFLOWS_PER_15_SECOND 458
#define DISPLAY_PERIOD 		1500
#define PASSWORD_LENGTH 	5
#define MAX_CHANCES 	3
#include "avr/interrupt.h"
#include "timer.h"
#include "twi.h"
#include "buzzer.h"
#include "motor.h"
#include "uart.h"
#include "external_eeprom.h"
#include <util/delay.h>
/*UART MESSAGES*/
#define MC_READY_TO_SEND		0x10
#define MC_READY_TO_RECEIVE		0x11
#define PASSWORD_MATCH 			0x01
#define PASSWORD_MISMATCH		0x00 /*For matching between 2 Sent passwords*/
#define CHANGE_PASSWORD_REQUEST	0x03
#define UNLOCK_DOOR_REQUEST		0x04
#define CHANGE_PASSWORD			0x05
#define UNLOCK_DOOR				0x06
#define WRONG_MATCH				0x07 /*For matching with eeprom*/
#define SYSTEM_LOCK				0x08


#define MC_SLAVE_ADDRESS		0x01
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*Description:
 * 1-Function Receives Password to be set and password to be received by UART
 * 2-Compare Passwords and send Confirmation or Wrong Entry to MC1
 * 3-IF passwords matched ,it stores password in EEPROM
 * 4-If not Sends UNMATCHING to repormpt user in MC1 to re-enter Password
 * */
void firstEntry();
/*Description:
 * Function used to Compare Confirmation password and Set password
 * Also used In case comparing in main menu,The first step is to update global array
 * containg EEPROM password with the one stored in EEPROM
 * */
uint8 comparePasswords(uint8*a_pass1,uint8*a_pass2);
/*Description:
 *Function responsible for storing Password in eeprom in case of matching
 * */
void storePassword();
/*Function responsible for reading password from EEPROM and storing it global array*/
void readPassword();
/*Call back Function*/
void callBack();
/*Function responsible for:
 * 1-Open door for 15 secs
 * 2-Hold door for 3 secs
 * 3-Close door for 15 secs
 *	4-Uses Timer ticks for Calculating the time
 * */
void doorOpen();
#endif /* CONTROL_H_ */
