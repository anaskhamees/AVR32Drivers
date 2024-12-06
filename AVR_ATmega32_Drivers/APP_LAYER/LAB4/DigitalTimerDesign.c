/*
 * File Name: DigitalTimerDesign.c (main)
 * Layer	: APP
 * Version  : V 0.0
 * Created	: 12/19/2023 5:04:38 PM
 * Author	: Anas Khamees
 */ 

#include "../APP.h"
#ifdef APP
#if (APP==DIG_TIMER)  //Select the Lab Application from APP.h
#include "../../HAL_LAYER/SEVEN_SEG_MODULE/Seven_Segment_config.h"
#include "../../HAL_LAYER/BUTTON_MODULE/BUTTON_Config.h"
#include "../../HAL_LAYER/LED_MODULE/LED_Config.h"
#include <util/delay.h>

int main(void)
{	
	/*Initialize button states and counter which will be display on SSD*/
	BUTTON_enumState_t BUTTON_LocIncState=BUTTON_RELEASED;
	BUTTON_enumState_t BUTTON_LocDowncState=BUTTON_RELEASED;
	BUTTON_enumState_t BUTTON_LocDecState=BUTTON_RELEASED;
	u8 Loc_Counter=0;
	/* Initialize the LED*/
	LED_enumError_t LED_LocRetErr=LED_enumInit(&Led1);

	 /*Initialize 7-segment display*/
	_7SEG_enumError_t _7SEG_LocRetErr;
	for(u8 SSD_Index=0;SSD_Index<MAX_7SEGMENTS_USED;SSD_Index++)
	{
		_7SEG_LocRetErr=_7SEG_enumInit(&(_7Segment[SSD_Index]));
	}
	/* Initialize 3-buttons*/
	BUTTON_enumError_t BUTTON_RetErr=BUTTON_enumInit(&Increment_Button);
	BUTTON_RetErr=BUTTON_enumInit(&Decrement_Button);
	BUTTON_RetErr=BUTTON_enumInit(&Down_Button);
	
    while (1) 
    {
	    /*Display the current counter value on 7-segment display*/
		_7SEG_LocRetErr=_7SEG_enumDisplay(&(_7Segment[_7SEGMENT_1]),Loc_Counter);
		/*Waiting until any button is pressed*/
		while((BUTTON_LocIncState==BUTTON_RELEASED)&&(BUTTON_LocDowncState==BUTTON_RELEASED)&&(BUTTON_LocDecState==BUTTON_RELEASED))
		{
			BUTTON_RetErr=BUTTON_enumReadStatus(&Increment_Button,&BUTTON_LocIncState);
			BUTTON_RetErr=BUTTON_enumReadStatus(&Decrement_Button,&BUTTON_LocDecState);
			BUTTON_RetErr=BUTTON_enumReadStatus(&Down_Button,&BUTTON_LocDowncState);
		}
		/*Respond to button press events*/		
		if(BUTTON_LocIncState==BUTTON_PRESSED)
		{
			/*Turn off LED and increment the counter*/
			LED_LocRetErr=LED_enumTurnOff(&Led1);
			if(Loc_Counter<9)
			{
				Loc_Counter++;
			}			
		}
		else if(BUTTON_LocDecState==BUTTON_PRESSED)
		{
			if(Loc_Counter>0)
			{
				Loc_Counter--;
			}
			
		}
		else if(BUTTON_LocDowncState==BUTTON_PRESSED)
		{
		/*Display the counter in reverse order and reset the counter*/
			for(int i=Loc_Counter;i>=0;i--)
			{
				_7SEG_LocRetErr=_7SEG_enumDisplay(&(_7Segment[_7SEGMENT_1]),i);
				_delay_ms(500);
			}
			Loc_Counter=0;
			/*Turn on LED after displaying the countdown*/
			LED_LocRetErr=LED_enumTurnOn(&Led1);

		}
		/* Waiting until all buttons are released*/
		while ((BUTTON_LocIncState==BUTTON_PRESSED)||(BUTTON_LocDecState==BUTTON_PRESSED)||(BUTTON_LocDowncState==BUTTON_PRESSED))
		{
			BUTTON_RetErr=BUTTON_enumReadStatus(&Increment_Button,&BUTTON_LocIncState);
			BUTTON_RetErr=BUTTON_enumReadStatus(&Decrement_Button,&BUTTON_LocDowncState);
			BUTTON_RetErr=BUTTON_enumReadStatus(&Down_Button,&BUTTON_LocDecState);
		}
	}
}
#endif // (APP == DIG_TIMER)
#endif // ifdef APP