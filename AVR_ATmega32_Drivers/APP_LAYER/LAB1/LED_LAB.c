/*
 * File Name: LED_LAB.c (main)
 * Layer	: APP
 * Version  : V 0.0
 * Created	: 12/10/2023 10:52:44 PM
 * Author	: Anas Khamees
 */ 

#include "../APP.h"
#ifdef APP
#if (APP==LED_LAB)  //Select the Lab Application from APP.h
#include "../../HAL_LAYER/LED_MODULE/LED_Config.h"
#include <util/delay.h>

int main(void)
{
	LED_enumError_t retErr=LED_enumInit(&Led1);
	retErr=LED_enumInit(&Led2);
	retErr=LED_enumInit(&Led3);
	
    /* Replace with your application code */
    while (1) 
    {
		retErr=LED_enumTurnOn(&Led1);
     	retErr=LED_enumTurnOn(&Led2);
		retErr=LED_enumTurnOn(&Led3);
		_delay_ms(500);
		retErr=LED_enumTurnOff(&Led1);
		retErr=LED_enumTurnOff(&Led2);
		retErr=LED_enumTurnOff(&Led3);	
		_delay_ms(500);	
    }
}
#endif // (APP == LED_LAB)
#endif // ifdef APP