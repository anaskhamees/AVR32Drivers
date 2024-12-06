/*
 * ADC_Synch.c
 *
 * Created: 3/22/2024 6:11:41 PM
 *  Author: anask
 */ 

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
#if (APP==ADC_SYNCH_TEST)  //Select the Lab Application from APP.h
#include "../../MCAL_LAYER/ADC/ADC_CFG.h"
#include "../../HAL_LAYER/LED_MODULE/LED_Config.h"
u16 Result=0;
int main(void)
{
	LED_enumError_t retErr=LED_enumInit(&Led1);
	ADC_enumErrorState_t ReturnError;
	ReturnError=ADC_Init();
	while (1)
	{
		ReturnError= ADC_StartConversionSync(ADC_SINGLE_CHANNEL0,&Result);
		/* ADC Resultion 10 Bit, so the max Value is 1024*/
		f32 StepSize=(f32)5/(f32)1024;
		/* This Analog value from 0 volt to 5 Volt*/
		f32 AnalogVolt=(Result*StepSize);
		LED_enumError_t LedReturnError;
		if(AnalogVolt>2)
		{
			LedReturnError=LED_enumTurnOn(&Led1);
		}
		else
		{
			LedReturnError=LED_enumTurnOff(&Led1);
		}
	}
}
#endif // (APP == ADC_SYNCH_TEST)
#endif // ifdef APP