/*
 * File Name: Keypad_Config.c
 * Layer	: HAL
 * Module	: KEYPAD
 * Version  : V 0.0
 * Created	: 1/7/2024 12:44:57 AM
 * Author	: Anas Khamees
 */ 
#include "Keypad.h"

#define COLUMN0		0
#define COLUMN1		1
#define COLUMN2		2
#define COLUMN3		3

#define ROW0		0
#define ROW1		1
#define ROW2		2
#define ROW3		3

KEYPAD_strConfig_t CalculatorKeyPad=
{
	/* Columns Pins Configurations which associated with MCU DIO*/
	.KeypadColomns[COLUMN0].pinDirection=DIO_enumOutputHigh,
	.KeypadColomns[COLUMN0].portNumber  =DIO_enumPortC,
	.KeypadColomns[COLUMN0].pinNumber   =DIO_enumPin0,
	
	.KeypadColomns[COLUMN1].pinDirection=DIO_enumOutputHigh,
	.KeypadColomns[COLUMN1].portNumber  =DIO_enumPortC,
	.KeypadColomns[COLUMN1].pinNumber   =DIO_enumPin1,
	
	.KeypadColomns[COLUMN2].pinDirection=DIO_enumOutputHigh,
	.KeypadColomns[COLUMN2].portNumber  =DIO_enumPortC,
	.KeypadColomns[COLUMN2].pinNumber   =DIO_enumPin2,
	
	.KeypadColomns[COLUMN3].pinDirection=DIO_enumOutputHigh,
	.KeypadColomns[COLUMN3].portNumber  =DIO_enumPortC,
	.KeypadColomns[COLUMN3].pinNumber   =DIO_enumPin3,
	
	/* Rows Pins Configurations which associated with MCU DIO*/
	.KeypadRows[ROW0].pinDirection=DIO_enumInputInternalPU,
	.KeypadRows[ROW0].portNumber  =DIO_enumPortC,
	.KeypadRows[ROW0].pinNumber   =DIO_enumPin4,
	
	.KeypadRows[ROW1].pinDirection=DIO_enumInputInternalPU,
	.KeypadRows[ROW1].portNumber  =DIO_enumPortC,
	.KeypadRows[ROW1].pinNumber   =DIO_enumPin5,
	
	.KeypadRows[ROW2].pinDirection=DIO_enumInputInternalPU,
	.KeypadRows[ROW2].portNumber  =DIO_enumPortC,
	.KeypadRows[ROW2].pinNumber   =DIO_enumPin6,
	
	.KeypadRows[ROW3].pinDirection=DIO_enumInputInternalPU,
	.KeypadRows[ROW3].portNumber  =DIO_enumPortC,
	.KeypadRows[ROW3].pinNumber   =DIO_enumPin7
};