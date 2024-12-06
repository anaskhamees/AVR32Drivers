/*
 * adc_app.c
 *
 * Created: 3/22/2024 5:29:36 AM
 *  Author: anask
 */ 

#include "../APP.h"
#ifdef APP
#if (APP==ADC_TEST)  //Select the Lab Application from APP.h
#include "../../MCAL_LAYER/ADC/ADC_CFG.h"
#include "../../HAL_LAYER/LED_MODULE/LED_Config.h"
ADC_Chain_t ADC_Chain;
void ChainNotification(void)
{
	/* ADC Resultion 10 Bit, so the max Value is 1024*/
	f32 StepSize=(f32)5/(f32)1024;
	/* This Analog value from 0 volt to 5 Volt*/
	f32 AnalogVolt=(ADC_Chain.ChainResults[0])*StepSize;
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
int main(void)
{
	LED_enumError_t retErr=LED_enumInit(&Led1);
	ADC_enumErrorState_t ReturnError;
	ReturnError=ADC_Init();
	
	u8  ADC_Channel[2]={ADC_SINGLE_CHANNEL0,ADC_SINGLE_CHANNEL1};
	u16 ADC_Results[2]={0};
	
	ADC_Chain.ChainLength=2;
	ADC_Chain.ChainChannels=ADC_Channel;
	ADC_Chain.ChainResults=ADC_Results;
	ADC_Chain.APP_Notification=ChainNotification;

	ReturnError=ADC_StartConversionAsync(&ADC_Chain);

	while (1)
	{

	}
}
#endif
#endif