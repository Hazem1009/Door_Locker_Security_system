/******************************************************************************
 *
 * Module: HMI_ECU
 *
 * File Name: hmi.h
 *
 * Description: Header file HMI ECU
 *
 * Author: Hazem Hisham
 *
 *******************************************************************************/

#ifndef HMI_H_
#define HMI_H_
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#include "timer.h"
#include "uart.h"
#include "keypad.h"
#include "lcd.h"
#define NUMBER_OF_OVERFLOWS_PER_THREE_SECOND 92
#define NUMBER_OF_OVERFLOWS_PER_ONE_MINUTE 1832
#define NUMBER_OF_OVERFLOWS_PER_15_SECOND 458
#define DISPLAY_PERIOD 		1500
#define PASSWORD_LENGTH 	5
#define MAX_CHANCES 	3
#include "avr/interrupt.h"
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


/*States of Program*/
#define INITIAL					1
#define MAIN_MENU				2
#define PW_CHANGE				3

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*Function responsible for:
 * 1-Function used to prompt user for password on LCD
 * 2-Accepts Input from user on keypad and store it in Global array
 *
 * */
void passwordPrompt();
/*Function Responsible For:
 * 1-Getting Password in The right Format For UART Send string function.
 * 2-Send Password as a String.
 * */
void sendPassword(uint8*Pass);
/*Function Responsible for
 * 1-Interfacing Program for setting up password and confirming it
 * 2-sends Passwords to Control ECU to make sure they are matching
 *	3-Wait For A reply From control ECU for Validity of Password Matching
 * */
void firstEntry();
/*function Responsible for displaying Main menu options*/
void mainMenuDisplay(void);
/*Function responsible For displaying Wrong password msg when entering wrong one*/
void DisplayError();
/*Call back Function for timer0*/
void callBack();
/*Function Responsible For:
 * 1-Opening ,closing and holding door messages display on LCD
 * 2-Manipulating g_tick variable according to Number of interrupts in TImer0
 * */
void doorStateDisplay();
#endif
