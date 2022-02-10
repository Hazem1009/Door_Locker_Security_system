 /******************************************************************************
 *
 * Module: Motor
 *
 * File Name: motor.c
 *
 * Description: Source file for the DC motor
 *
 * Author: Hazem Hisham
 *
 *******************************************************************************/
#include "motor.h"
#include "gpio.h"
#include "common_macros.h"

/*
 * Description
 The Function responsible for setup the direction for the two
motor pins through the GPIO driver.
 Stop at the DC-Motor at the beginning through the GPIO driver.

 */
void DcMotor_init(void){
	GPIO_setupPinDirection(DCMOTOR_PORT_ID, DCMOTOR_INPUT1_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(DCMOTOR_PORT_ID, DCMOTOR_INPUT2_PIN, PIN_OUTPUT);
	GPIO_writePin(DCMOTOR_PORT_ID,DCMOTOR_INPUT1_PIN,LOGIC_LOW);
	GPIO_writePin(DCMOTOR_PORT_ID,DCMOTOR_INPUT2_PIN,LOGIC_LOW);

}

/*
 * Description:
 *The function responsible for rotate the DC Motor CW/ or A-CW or
 *stop the motor based on the state input state value.
 *Send the required duty cycle to the PWM driver based on the
 *required speed value.
 */
void DcMotor_Rotate(DcMotor_State state){
	switch(state){
	case STOP:
		GPIO_writePin(DCMOTOR_PORT_ID,DCMOTOR_INPUT1_PIN,LOGIC_LOW);
		GPIO_writePin(DCMOTOR_PORT_ID,DCMOTOR_INPUT2_PIN,LOGIC_LOW);
		break;
	case CW:
		GPIO_writePin(DCMOTOR_PORT_ID,DCMOTOR_INPUT1_PIN,LOGIC_HIGH);
		GPIO_writePin(DCMOTOR_PORT_ID,DCMOTOR_INPUT2_PIN,LOGIC_LOW);
		break;
	case ACW:
		GPIO_writePin(DCMOTOR_PORT_ID,DCMOTOR_INPUT1_PIN,LOGIC_LOW);
		GPIO_writePin(DCMOTOR_PORT_ID,DCMOTOR_INPUT2_PIN,LOGIC_HIGH);
		break;
	}
}
