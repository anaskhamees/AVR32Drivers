/*
 * File Name: Keypad_LAB.c
 * Layer	: MCAL
 * Module	: EXTI
 * Version  : V 0.0
 * Target	: AVR-Atmega32
 * Created	: 1/7/2024 4:51:40 AM
 * Author	: Anas Khamees
 * Brief	: This Source file is the main application.
 */ 

#include "../APP.h"
#ifdef APP
#if (APP==KEYPAD_LAB)  //Select the Lab Application from APP.h
#include "../../HAL_LAYER/KEYPAD_MODULE/Keypad_Config.h"
#include "../../HAL_LAYER/LED_MODULE/LED_Config.h"
#include "../../HAL_LAYER/LCD_MODULE/LCD_Config.h"

u8 KEYPAD_PressedKeyValue;
int main(void)
{
	LCD_enumError_t Loc_LCDRetErr=LCD_enumInit(&LCD1);
	LED_enumError_t LED_LocRetErr=LED_enumInit(&Led1);
	KEYPAD_enumError_t KEYPAD_LocRetErr=KEYPAD_enumInit(&CalculatorKeyPad);
	while (1)
	{
		KEYPAD_LocRetErr=KEYPAD_enumGetPressedValue(&CalculatorKeyPad,&KEYPAD_PressedKeyValue);	
		if(KEYPAD_PressedKeyValue !='\0')
		{
			LED_LocRetErr=LED_enumTurnOn(&Led1);
			Loc_LCDRetErr=LCD_enumSendChar(&LCD1,KEYPAD_PressedKeyValue);
			KEYPAD_PressedKeyValue ='\0';
			_delay_ms(100);
			Loc_LCDRetErr=LCD_enumSendCommand(&LCD1,LCD_CLEAR_DISPLAY);
			LED_LocRetErr=LED_enumTurnOff(&Led1);
		}	
	}
}
#endif // (APP == KEYPAD_LAB)
#endif // ifdef APP