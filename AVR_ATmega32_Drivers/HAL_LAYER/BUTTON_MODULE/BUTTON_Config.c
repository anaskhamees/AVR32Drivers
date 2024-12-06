/*
 * File Name: BUTTON_Config.c
 * Layer	: HAL
 * Module	: BUTTON
 * Version  : V 0.0
 * Created	: 12/17/2023 11:51:38 PM
 * Author	: Anas Khamees
 */ 

#include "BUTTON_Config.h"

/*BUTTON_strButton_t Increment_Button=
{
	.Button.portNumber=DIO_enumPortB,
	.Button.pinNumber =DIO_enumPin0,
	.Button.pinDirection=DIO_enumInputInternalPU,
	.Button.pinLogic=DIO_enumLogicHigh,
	.ButtonState=BUTTON_RELEASED,
};

BUTTON_strButton_t Decrement_Button=
{
	.Button.portNumber=DIO_enumPortB,
	.Button.pinNumber =DIO_enumPin1,
	.Button.pinDirection=DIO_enumInputInternalPU,
	.Button.pinLogic=DIO_enumLogicHigh,
	.ButtonState=BUTTON_RELEASED,
};

BUTTON_strButton_t Down_Button=
{
	.Button.portNumber=DIO_enumPortB,
	.Button.pinNumber =DIO_enumPin2,
	.Button.pinDirection=DIO_enumInputInternalPU,
	.Button.pinLogic=DIO_enumLogicHigh,
	.ButtonState=BUTTON_RELEASED,
};*/

/* Interrupt App*/
BUTTON_strButton_t INT0_Button=
{
	.Button.portNumber=DIO_enumPortD,
	.Button.pinNumber =DIO_enumPin2,
	.Button.pinDirection=DIO_enumInputInternalPU,
	.Button.pinLogic=DIO_enumLogicHigh,
	.ButtonState=BUTTON_RELEASED,
};

BUTTON_strButton_t INT1_Button=
{
	.Button.portNumber=DIO_enumPortD,
	.Button.pinNumber =DIO_enumPin3,
	.Button.pinDirection=DIO_enumInputInternalPU,
	.Button.pinLogic=DIO_enumLogicHigh,
	.ButtonState=BUTTON_RELEASED,
};

BUTTON_strButton_t INT2_Button=
{
	.Button.portNumber=DIO_enumPortB,
	.Button.pinNumber =DIO_enumPin2,
	.Button.pinDirection=DIO_enumInputInternalPU,
	.Button.pinLogic=DIO_enumLogicHigh,
	.ButtonState=BUTTON_RELEASED,
};