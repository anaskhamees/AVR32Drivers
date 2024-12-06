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
#if (APP==TIMER0_APP)  //Select the Lab Application from APP.h
#include "MCAL_LAYER/TIMER/TimerCFG.h"
#include "HAL_LAYER/LED_MODULE/LED_Config.h"

void AppHandler(void)
{
    LED_enumError_t RetError;
    RetError=LED_enumToggle(&Led1);
}
int main(void)
{
    TIMER_enumErrorState_t ReturnError;
    LED_enumError_t retErr=LED_enumInit(&Led1);
    ReturnError=TIMER0_enumInit();
    ReturnError=TIMER0_enumSetTickTimeMS(_TICK_TIME_500MS,TIMER_8BIT_OVF_INT_ON);
    ReturnError=Timer0_SetCallBack(AppHandler,TIMER_8BIT_OVF_INT_ON);
    ReturnError=Timer0_Start();

	while (1)
	{

	}
}
#endif // (APP == KEYPAD_LAB)
#endif // ifdef APP