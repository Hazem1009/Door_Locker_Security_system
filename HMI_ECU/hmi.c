/******************************************************************************
 *
 * Module: HMI_ECU
 *
 * File Name: hmi.c
 *
 * Description: Source file HMI ECU
 *
 * Author: Hazem Hisham
 *
 *******************************************************************************/
#include "hmi.h"
#include "util/delay.h"
uint8 g_password[PASSWORD_LENGTH];
uint8 g_check=PASSWORD_MISMATCH;
uint16 g_tick=0;
uint8 g_chances=0;
int main(){
	SREG|=(1<<7);
	UART_ConfigType uartconfig_Ptr={9600,DISABLED,ONE,EIGHT};
	UART_init(&uartconfig_Ptr);
	Timer0_ConfigType timerconfig_ptr={NORMAL,F_CPU_1024,0,0};
	Timer0_init(&timerconfig_ptr);
	Timer0_setCallBack(callBack);
	LCD_init();
	LCD_displayString("WELCOME TO SYSTEM");
	_delay_ms(DISPLAY_PERIOD);
	firstEntry();
	uint8 key;
	uint8 stateReceived;
	while(1){
		mainMenuDisplay();
		key=KEYPAD_getPressedKey();
		if(key=='+'){
			LCD_clearScreen();
			LCD_displayString("Enter Password");
			passwordPrompt();
			UART_sendByte(MC_READY_TO_SEND);
#if 0
	UART_sendByte(MC_READY_TO_RECEIVE);
#endif
			sendPassword(g_password);
			UART_sendByte(UNLOCK_DOOR_REQUEST);
			stateReceived=UART_recieveByte();
			if(stateReceived==UNLOCK_DOOR){
				doorStateDisplay();
			}
			else if(stateReceived==WRONG_MATCH){ //wrong password
				LCD_clearScreen();
				g_chances++;
				LCD_displayString("Wrong Password,Retry");
				if(g_chances==MAX_CHANCES){
					g_tick=0;
					LCD_clearScreen();
					LCD_displayString("Hostile!!");
					while(g_tick<NUMBER_OF_OVERFLOWS_PER_ONE_MINUTE);
					g_chances=0;
					g_tick=0;
				}
				else{
				_delay_ms(DISPLAY_PERIOD);
				}
			}
			mainMenuDisplay();
		}
		else if(key=='-'){
			LCD_clearScreen();
			LCD_displayString("Enter Your Password");
			passwordPrompt();
			UART_sendByte(MC_READY_TO_SEND);
#if 0
	UART_sendByte(MC_READY_TO_RECEIVE);
#endif
			sendPassword(g_password);
			UART_sendByte(CHANGE_PASSWORD_REQUEST);
			stateReceived=UART_recieveByte();
			if(stateReceived==CHANGE_PASSWORD){
				firstEntry();
			}
			else if(stateReceived==WRONG_MATCH){
				LCD_clearScreen();
				g_chances++;
				LCD_displayString("Wrong Password,Retry");
				if(g_chances==MAX_CHANCES){
					g_tick=0;
					LCD_clearScreen();
					LCD_displayString("Hostile!!");
					while(g_tick<NUMBER_OF_OVERFLOWS_PER_ONE_MINUTE);
					g_chances=0;
					g_tick=0;
				}
				else{
					_delay_ms(DISPLAY_PERIOD);
					}
			}
			mainMenuDisplay();
		}
	}
}
/*Function responsible for:
 * 1-Function used to prompt user for password on LCD
 * 2-Accepts Input from user on keypad and store it in Global array
 *
 * */
void passwordPrompt(){
	LCD_moveCursor(1, 0);
	uint8 ctr=0,key=0;
	for(ctr=0;ctr<PASSWORD_LENGTH;ctr++){

		key=KEYPAD_getPressedKey();

		if(key>=1&&key<=9){
			g_password[ctr]=key;
			LCD_moveCursor(1, ctr);
			LCD_displayCharacter('*');
		}
		else{
			ctr--;
			continue;
		}
		_delay_ms(500);
	}
	/*Waiting for user to press Enter*/
	while(KEYPAD_getPressedKey()!=13);
}
/*Function Responsible For:
 * 1-Getting Password in The right Format For UART Send string function.
 * 2-Send Password as a String.
 * */
void sendPassword(uint8*Pass){
	uint8 temp_pass[PASSWORD_LENGTH+2];
	uint8 i=0;
	for(i=0;i<PASSWORD_LENGTH;i++){
		temp_pass[i]=Pass[i];
	}
	temp_pass[5]='#';
	temp_pass[6]='\0';
	UART_sendString(temp_pass);
}
/*Function Responsible for
 * 1-Interfacing Program for setting up password and confirming it
 * 2-sends Passwords to Control ECU to make sure they are matching
 *	3-Wait For A reply From control ECU for Validity of Password Matching
 * */
void firstEntry(){
	while(g_check==PASSWORD_MISMATCH){
		LCD_clearScreen();
		LCD_displayString("Enter Password:");
		LCD_moveCursor(0, 1);
		passwordPrompt();
		UART_sendByte(MC_READY_TO_SEND);
		while(UART_recieveByte()!=MC_READY_TO_RECEIVE);
		sendPassword(g_password);
		/*PROMPT FOR RE-ENTERING "confirmation For password"*/
		LCD_clearScreen();
		LCD_displayString("Re-Enter Password:");
		LCD_moveCursor(1, 0);
		passwordPrompt();
		UART_sendByte(MC_READY_TO_SEND);
		while(UART_recieveByte()!=MC_READY_TO_RECEIVE);
		sendPassword(g_password);
		while(UART_recieveByte()!=MC_READY_TO_SEND);
#if 0
	UART_sendByte(MC_READY_TO_RECEIVE);
#endif
		g_check=UART_recieveByte();
		if(g_check==PASSWORD_MISMATCH){
			LCD_clearScreen();
			LCD_displayString("Not Matching");
			_delay_ms(DISPLAY_PERIOD);
		}
	}
	/*After Matching We should set check to Mismatch for Main Menu*/
	g_check=PASSWORD_MISMATCH;
}
/*function Responsible for displaying Main menu options*/
void mainMenuDisplay(void){
	LCD_clearScreen();
	LCD_displayString("+:Open Door");
	LCD_displayStringRowColumn(1, 0, "-:Reset Password");
}
/*Function responsible For displaying Wrong password msg when entering wrong one*/
void DisplayError(){
	LCD_clearScreen();
	LCD_displayString("Wrong Password,Retry");
	_delay_ms(DISPLAY_PERIOD);
}
/*Call back Function for timer0*/
void callBack(){
	g_tick++;
}
/*Function Responsible For:
 * 1-Opening ,closing and holding door messages display on LCD
 * 2-Manipulating g_tick variable according to Number of interrupts in TImer0
 * */
void doorStateDisplay(){
	LCD_clearScreen();
	g_tick=0;
	LCD_displayString("Door is Opening");
	while(g_tick<NUMBER_OF_OVERFLOWS_PER_15_SECOND);
	LCD_clearScreen();
	g_tick=0;
	LCD_displayString("door unlocked");
	while(g_tick<NUMBER_OF_OVERFLOWS_PER_THREE_SECOND);
	LCD_clearScreen();
	g_tick=0;
	LCD_displayString("Door is closing");
	while(g_tick<NUMBER_OF_OVERFLOWS_PER_15_SECOND);
	g_tick=0;
	LCD_clearScreen();
}
