/*
 * LCD_APP.c
 *
 * Created: 1/1/2024 5:00:55 AM
 *  Author: Anas
 */ 
#include "../APP.h"
#ifdef APP
#if (APP==LCD_LAB)  //Select the Lab Application from APP.h
#include "../../HAL_LAYER/LCD_MODULE/LCD_Config.h"
#include <util/delay.h>

int main(void)
{
	LCD_enumError_t Loc_LCDRetErr=LCD_enumInit(&LCD1);
	Loc_LCDRetErr=LCD_enumSendCommand(&LCD1,LCD_DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
	//Loc_LCDRetErr=LCD_enumSendString(&LCD1,(u8*)"Anas Khamees");
	/*Loc_LCDRetErr =LCD_enumSendSpecialChar(&LCD1,LCD_ROW1,15,CharArrPattern1,0);
	Loc_LCDRetErr =LCD_enumSendSpecialChar(&LCD1,LCD_ROW1,14,CharArrPattern2,1);
	Loc_LCDRetErr =LCD_enumSendSpecialChar(&LCD1,LCD_ROW1,13,CharArrPattern3,2);
	Loc_LCDRetErr =LCD_enumSendSpecialChar(&LCD1,LCD_ROW1,12,CharArrPattern4,3);
	Loc_LCDRetErr =LCD_enumSendSpecialChar(&LCD1,LCD_ROW1,11,CharArrPattern5,4);
	Loc_LCDRetErr =LCD_enumSendSpecialChar(&LCD1,LCD_ROW1,10,CharArrPattern5,3);
*/
	 Loc_LCDRetErr=LCD_enumSendString(&LCD1,(u8*)"Anas Khamees");
	 _delay_ms(200);
	while (1)
	{
		
		for(u8 i=0;i<16;i++)
		{
			Loc_LCDRetErr=LCD_enumSendCommand(&LCD1,LCD_DISPLAY_SHIFT_RIGHT);	
			_delay_ms(200);
		}
		
		
		for(u8 i=0;i<16+11;i++)
		{
			Loc_LCDRetErr=LCD_enumSendCommand(&LCD1,LCD_DISPLAY_SHIFT_LEFT);
			_delay_ms(200);
		}
		
		for(u8 i=0;i<11;i++)
		{
			Loc_LCDRetErr=LCD_enumSendCommand(&LCD1,LCD_DISPLAY_SHIFT_RIGHT);
			_delay_ms(200);
		}
	
}
}
#endif // (APP == LCD_LAB)
#endif // ifdef APP