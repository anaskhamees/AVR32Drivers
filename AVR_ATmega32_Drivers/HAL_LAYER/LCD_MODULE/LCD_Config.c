/*
 * File Name: LCD_Config.c
 * Layer	: HAL
 * Module	: LCD
 * Version  : V 0.0
 * Created	: 12/31/2023 9:49:35 PM
 * Author	: Anas Khamees
 * Brief	: This source file defines the user configuration for LCD driver.
 */ 
#include "LCD.h"

LCD_strConfig LCD1=
{
	.RegisterSelect.pinDirection=DIO_enumOutputLow,
	.RegisterSelect.pinLogic=DIO_enumLogicLow,
	.RegisterSelect.portNumber=DIO_enumPortB,
	.RegisterSelect.pinNumber=DIO_enumPin0,
	
	.EnableSignal.pinDirection=DIO_enumOutputLow,
	.EnableSignal.pinLogic=DIO_enumLogicLow,
	.EnableSignal.portNumber=DIO_enumPortB,
	.EnableSignal.pinNumber=DIO_enumPin1,
	
	 .LCD_Data[0].pinDirection=DIO_enumOutputLow,
	 .LCD_Data[0].pinLogic=DIO_enumLogicLow,
	 .LCD_Data[0].portNumber=DIO_enumPortA,
	 .LCD_Data[0].pinNumber=DIO_enumPin4,
	 
	 .LCD_Data[1].pinDirection=DIO_enumOutputLow,
	 .LCD_Data[1].pinLogic=DIO_enumLogicLow,
	 .LCD_Data[1].portNumber=DIO_enumPortA,
	 .LCD_Data[1].pinNumber=DIO_enumPin5,
	 
	 .LCD_Data[2].pinDirection=DIO_enumOutputLow,
	 .LCD_Data[2].pinLogic=DIO_enumLogicLow,
	 .LCD_Data[2].portNumber=DIO_enumPortA,
	 .LCD_Data[2].pinNumber=DIO_enumPin6,

	 .LCD_Data[3].pinDirection=DIO_enumOutputLow,
	 .LCD_Data[3].pinLogic=DIO_enumLogicLow,
	 .LCD_Data[3].portNumber=DIO_enumPortA,
	 .LCD_Data[3].pinNumber=DIO_enumPin7,
	
	/* .LCD_Data[4].pinDirection=DIO_enumOutputLow,
	 .LCD_Data[4].pinLogic=DIO_enumLogicLow,
	 .LCD_Data[4].portNumber=DIO_enumPortA,
	 .LCD_Data[4].pinNumber=DIO_enumPin4,
	
	 .LCD_Data[5].pinDirection=DIO_enumOutputLow,
	 .LCD_Data[5].pinLogic=DIO_enumLogicLow,
	 .LCD_Data[5].portNumber=DIO_enumPortA,
	 .LCD_Data[5].pinNumber=DIO_enumPin5,

	 .LCD_Data[6].pinDirection=DIO_enumOutputLow,
	 .LCD_Data[6].pinLogic=DIO_enumLogicLow,
	 .LCD_Data[6].portNumber=DIO_enumPortA,
	 .LCD_Data[6].pinNumber=DIO_enumPin6,
	 
	 .LCD_Data[7].pinDirection=DIO_enumOutputLow,
	 .LCD_Data[7].pinLogic=DIO_enumLogicLow,
	 .LCD_Data[7].portNumber=DIO_enumPortA,
	 .LCD_Data[7].pinNumber=DIO_enumPin7*/
	};
	
/********************************* Pattern Array of Special Characters ****************************************/
//?
u8 CharArrPattern1[8]={ 0x00,
						0x1F,
						0x1F,
						0x1F,
						0x0E,
						0x04,
						0x00,
						0x00};

//?
u8 CharArrPattern2[8]={ 0x00,
						0x02,
						0x00,
						0x07,
						0x05,
						0x07,
						0x1F,
						0x00};				
// ?						
u8 CharArrPattern3[8]={ 0x00,
						0x00,
						0x00,
						0x00,
						0x15,
						0x15,
						0x1F,
						0x00};
//?						
u8 CharArrPattern4[8]={	0x10,
						0x10,
						0x10,
						0x10,
						0x1E,
						0x12,
						0x1F,
						0x00};

//?
u8 CharArrPattern5[8]={ 0x00,
						0x00,
						0x00,
						0x12,
						0x12,
						0x1F,
						0x00,
						0x0C};
						

//?
u8 CharArrPattern6[8]={ 0x04,
						0x00,
						0x12,
						0x12,
						0x12,
						0x1F,
						0x00,
						0x00};
