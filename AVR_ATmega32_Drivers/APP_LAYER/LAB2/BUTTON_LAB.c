/*
 * File Name: BUTTON_LAB.c (main)
 * Layer	: APP
 * Version  : V 0.0
 * Created	: 12/10/2023 10:52:44 PM
 * Author	: Anas Khamees
 */ 

#include "../APP.h"
#ifdef APP
#if (APP==BTN_LAB)  //Select the Lab Application from APP.h
#include "../../HAL_LAYER/BUTTON_MODULE/BUTTON_Config.h"
#include "../../HAL_LAYER/LED_MODULE/LED_Config.h"
#include <util/delay.h>

int main(void)
{	
	BUTTON_enumError_t BUTTON_RetErr=BUTTON_enumInit(&Button1);
	LED_enumError_t retErr=LED_enumInit(&Led1);
	BUTTON_enumState_t BUTTON_LocState;
    /* Replace with your application code */
    while (1) 
    {
		BUTTON_RetErr=BUTTON_enumReadStatus(&Button1,&BUTTON_LocState);
		_delay_ms(10);
		if(BUTTON_LocState==BUTTON_PRESSED)
		{
			retErr=LED_enumTurnOn(&Led1);
			_delay_ms(500);	
		}
		else
		{
			retErr=LED_enumTurnOff(&Led1);
			_delay_ms(500);
		}
    }
}
#endif // (APP == LED_LAB)
#endif // ifdef APP