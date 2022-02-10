 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Hazem Hisham
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum{
	DISABLED,RESERVED,EVEN,ODD
}UART_Parity;

typedef enum{
	ONE,TWO
}UART_StopBit;

typedef enum{
	FIVE,SIX,SEVEN,EIGHT,NINE=7
}UART_CharSize;

typedef struct {
	uint32 baud_rate;
	UART_Parity parity;
	UART_StopBit stop;
	UART_CharSize size;
}UART_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType *ConfigPtr );

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint16 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint16 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
