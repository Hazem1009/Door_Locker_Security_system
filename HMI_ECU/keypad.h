 /******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.h
 *
 * Description: header file for the Keypad driver
 *
 * Author: Hazem Hisham
 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"

//STATIC CONFIGURATION FOR NUMBER OF ROWS AND COLS
#define KEYPAD_NUM_COLS 4
#define KEYPAD_NUM_ROWS 4
//Static configuration for PORT and PINS
#define KEYPAD_PORT_ID   PORTB_ID
#define KEYPAD_FIRST_COLUMN_PIN_ID PIN4_ID
#define KEYPAD_FIRST_ROW_PIN_ID PIN0_ID
//Static configuration for pull up/down
#define KEYPAD_BUTTON_PRESSED  LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED LOGIC_HIGH // high for internal pull up
uint8 KEYPAD_getPressedKey(void);
#endif /* KEYPAD_H_ */
