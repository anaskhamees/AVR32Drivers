/*
 * File Name: LED_Config.c
 * Layer	: HAL
 * Module	: LED
 * Version  : V 0.0
 * Created	: 12/12/2023 11:48:00 PM
 * Author	: Anas Khamees
 */ 
#include "LED_Config.h"

LED_strConfig_t Led1=
{
	.Led.pinDirection=DIO_enumOutputHigh,
	.Led.portNumber=DIO_enumPortD,
	.Led.pinNumber=DIO_enumPin0,
	.LedConfig=ACTIVE_HIGH,
};

LED_strConfig_t INT0_Led=
{
	.Led.pinDirection=DIO_enumOutputHigh,
	.Led.portNumber=DIO_enumPortC,
	.Led.pinNumber=DIO_enumPin0,
	.LedConfig=ACTIVE_HIGH,
};

LED_strConfig_t INT1_Led=
{
	.Led.pinDirection=DIO_enumOutputHigh,
	.Led.portNumber=DIO_enumPortC,
	.Led.pinNumber=DIO_enumPin1,
	.LedConfig=ACTIVE_HIGH,
};

LED_strConfig_t INT2_Led=
{
	.Led.pinDirection=DIO_enumOutputHigh,
	.Led.portNumber=DIO_enumPortC,
	.Led.pinNumber=DIO_enumPin2,
	.LedConfig=ACTIVE_HIGH,
};