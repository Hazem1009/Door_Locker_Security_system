 /******************************************************************************
 *
 * Module: Motor
 *
 * File Name: motor.h
 *
 * Description: header file for the DC motor
 *
 * Author: Hazem Hisham
 *
 *******************************************************************************/

#ifndef MOTOR_H_
#define MOTOR_H_
#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define DCMOTOR_INPUT1_PIN		PIN2_ID
#define DCMOTOR_INPUT2_PIN 		PIN3_ID
#define DCMOTOR_PORT_ID			PORTD_ID
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum{
	STOP=0,CW,ACW
}DcMotor_State;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description
 The Function responsible for setup the direction for the two
motor pins through the GPIO driver.
 Stop at the DC-Motor at the beginning through the GPIO driver.

 */
void DcMotor_init(void);

/*
 * Description:
 *The function responsible for rotate the DC Motor CW/ or A-CW or
 *stop the motor based on the state input state value.
 *Send the required duty cycle to the PWM driver based on the
 *required speed value.
 */
void DcMotor_Rotate(DcMotor_State state);


#endif /* MOTOR_H_ */
