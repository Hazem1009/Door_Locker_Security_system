/******************************************************************************
 *
 * Module: CONTROL_ECU
 *
 * File Name: control.c
 *
 * Description: Source file CONTROL ECU
 *
 * Author: Hazem Hisham
 *
 *******************************************************************************/
#include "control.h"
uint8 g_receivedPassword[PASSWORD_LENGTH];
uint8 g_confirmationPassword[PASSWORD_LENGTH];
uint8 g_eeprom_password[PASSWORD_LENGTH];
uint8 g_chances=0;
uint16 g_tick;
int main(){
	SREG|=(1<<7);
	UART_ConfigType uartconfig_Ptr={9600,DISABLED,ONE,EIGHT};
	UART_init(&uartconfig_Ptr);
	Timer0_ConfigType timerconfig_ptr={NORMAL,F_CPU_1024,0,0};
	Timer0_init(&timerconfig_ptr);
	Timer0_setCallBack(callBack);
	TWI_TypeConfig twiconfig_ptr={MC_SLAVE_ADDRESS,Fast};
	TWI_init(&twiconfig_ptr);
	Buzzer_init();
	DcMotor_init();
	uint8 stateReceived;/*According to command sent via UART we are going to alter flow*/
	firstEntry();
	while(1){
		if(UART_recieveByte()==MC_READY_TO_SEND){
			UART_receiveString(g_receivedPassword);
			stateReceived=UART_recieveByte();
			if(stateReceived==UNLOCK_DOOR_REQUEST){
				if(comparePasswords(g_eeprom_password, g_receivedPassword)==PASSWORD_MATCH){
					UART_sendByte(UNLOCK_DOOR);
					doorOpen();
				}
				else{
					UART_sendByte(WRONG_MATCH);
					g_chances++;
					if(g_chances==MAX_CHANCES){
						Buzzer_ON();
						g_tick=0;
						while(g_tick<NUMBER_OF_OVERFLOWS_PER_ONE_MINUTE);
						Buzzer_OFF();
						g_chances=0;
					}
				}
			}
			else if(stateReceived==CHANGE_PASSWORD_REQUEST){
				if(comparePasswords(g_eeprom_password, g_receivedPassword)==PASSWORD_MATCH){
					UART_sendByte(CHANGE_PASSWORD);
					firstEntry();
				}
				else{
					UART_sendByte(WRONG_MATCH);
					g_chances++;
					if(g_chances==MAX_CHANCES){
						Buzzer_ON();
					    g_tick=0;
					    while(g_tick<NUMBER_OF_OVERFLOWS_PER_ONE_MINUTE);
					    Buzzer_OFF();
					    g_chances=0;
				}
			}
		}

	}
}
}
/*Description:
 * 1-Function Receives Password to be set and password to be received by UART
 * 2-Compare Passwords and send Confirmation or Wrong Entry to MC1
 * 3-IF passwords matched ,it stores password in EEPROM
 * 4-If not Sends UNMATCHING to repormpt user in MC1 to re-enter Password
 * */
void firstEntry(){
	uint8 match=PASSWORD_MISMATCH;
	while(match==PASSWORD_MISMATCH){
		/*For Receiving Password TO be set*/
		while(UART_recieveByte()!=MC_READY_TO_SEND);
		UART_sendByte(MC_READY_TO_RECEIVE);
		UART_receiveString(g_receivedPassword);

		/*For Receiving Confirmation password for password to be set*/
		while(UART_recieveByte()!=MC_READY_TO_SEND);
		UART_sendByte(MC_READY_TO_RECEIVE);
		UART_receiveString(g_confirmationPassword);
		/*Now We need to compare two passwords to Alter FLow in MC1*/
		if(comparePasswords(g_receivedPassword,g_confirmationPassword)==PASSWORD_MATCH){
			UART_sendByte(MC_READY_TO_SEND);
			UART_sendByte(PASSWORD_MATCH);
			/*Now we need to store Password in eeprom*/
			match=PASSWORD_MATCH;
			storePassword();
		}
		else{
			UART_sendByte(MC_READY_TO_SEND);
			UART_sendByte(PASSWORD_MISMATCH);
		}
	}
}
/*Description:
 * Function used to Compare Confirmation password and Set password
 * Also used In case comparing in main menu,The first step is to update global array
 * containg EEPROM password with the one stored in EEPROM
 * */
uint8 comparePasswords(uint8*a_pass1,uint8*a_pass2){
/*Important Step is updating global array password with the one stored in eeprom*/
	readPassword();
	uint8 ctr=0;
	for(ctr=0;ctr<PASSWORD_LENGTH;ctr++){
		if(a_pass1[ctr]!=a_pass2[ctr]){
			return PASSWORD_MISMATCH;
		}
	}
	return PASSWORD_MATCH;
}
/*Description:
 *Function responsible for storing Password in eeprom in case of matching
 * */
void storePassword(){
	uint8 ctr=0;
	for(ctr=0;ctr<PASSWORD_LENGTH;ctr++){
		EEPROM_writeByte(ctr, g_receivedPassword[ctr]);
		_delay_ms(100);
	}
}
/*Function responsible for reading password from EEPROM and storing it global array*/
void readPassword(){
	uint8 ctr=0;
		for(ctr=0;ctr<PASSWORD_LENGTH;ctr++){
			EEPROM_readByte(ctr, g_eeprom_password+ctr);
		}
}
/*Call back Function*/
void callBack(){
	g_tick++;
}
/*Function responsible for:
 * 1-Open door for 15 secs
 * 2-Hold door for 3 secs
 * 3-Close door for 15 secs
 *	4-Uses Timer ticks for Calculating the time
 * */
void doorOpen(){
	g_tick=0;
	DcMotor_Rotate(CW);
	while(g_tick<NUMBER_OF_OVERFLOWS_PER_15_SECOND);
	g_tick=0;
	DcMotor_Rotate(STOP);
	while(g_tick<NUMBER_OF_OVERFLOWS_PER_THREE_SECOND);
	g_tick=0;
	DcMotor_Rotate(ACW);
	while(g_tick<NUMBER_OF_OVERFLOWS_PER_15_SECOND);
	DcMotor_Rotate(STOP);
	g_tick=0;
}

