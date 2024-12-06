/*
 * File Name: Seven_Segment_config.c
 * Layer	: HAL
 * Module	: SEVEN_SEG
 * Version  : V 0.0
 * Created	: 12/18/2023 9:41:36 PM
 * Author	: Anas Khamees
 */ 

#include "Seven_Segment_config.h"

_7SEG_strConfig_t	_7Segment[MAX_7SEGMENTS_USED]=
	
	{
		/*[_7SEGMENT_1]=
		{
			._7SegPins[0].portNumber=DIO_enumPortC,
			._7SegPins[0].pinNumber=DIO_enumPin0,
			._7SegPins[0].pinDirection=DIO_enumLogicLow,
			._7SegPins[1].portNumber=DIO_enumPortC,
			._7SegPins[1].pinNumber=DIO_enumPin1,
			._7SegPins[1].pinDirection=DIO_enumLogicLow,
			._7SegPins[2].portNumber=DIO_enumPortC,
			._7SegPins[2].pinNumber=DIO_enumPin2,
			._7SegPins[2].pinDirection=DIO_enumLogicLow,
			._7SegPins[3].portNumber=DIO_enumPortC,
			._7SegPins[3].pinNumber=DIO_enumPin3,
			._7SegPins[3].pinDirection=DIO_enumLogicLow,
			._7SegPins[4].portNumber=DIO_enumPortC,
			._7SegPins[4].pinNumber=DIO_enumPin4,
			._7SegPins[4].pinDirection=DIO_enumLogicLow,
			._7SegPins[5].portNumber=DIO_enumPortC,
			._7SegPins[5].pinNumber=DIO_enumPin5,
			._7SegPins[5].pinDirection=DIO_enumLogicLow,
			._7SegPins[6].portNumber=DIO_enumPortC,
			._7SegPins[6].pinNumber=DIO_enumPin6,
			._7SegPins[6].pinDirection=DIO_enumLogicLow,
			._7SegPins[7].portNumber=DIO_enumPortC,
			._7SegPins[7].pinNumber=DIO_enumPin7,
			._7SegPins[7].pinDirection=DIO_enumLogicLow,
			._7SegType=COMMON_CATHODE,
		},*/
		
		[_7SEGMENT_1]=
		{
			._7SegPins[0].portNumber=DIO_enumPortA,
			._7SegPins[0].pinNumber=DIO_enumPin0,
			._7SegPins[0].pinDirection=DIO_enumLogicLow,
			._7SegPins[1].portNumber=DIO_enumPortA,
			._7SegPins[1].pinNumber=DIO_enumPin1,
			._7SegPins[1].pinDirection=DIO_enumLogicLow,
			._7SegPins[2].portNumber=DIO_enumPortA,
			._7SegPins[2].pinNumber=DIO_enumPin2,
			._7SegPins[2].pinDirection=DIO_enumLogicLow,
			._7SegPins[3].portNumber=DIO_enumPortA,
			._7SegPins[3].pinNumber=DIO_enumPin3,
			._7SegPins[3].pinDirection=DIO_enumLogicLow,
			._7SegPins[4].portNumber=DIO_enumPortA,
			._7SegPins[4].pinNumber=DIO_enumPin4,
			._7SegPins[4].pinDirection=DIO_enumLogicLow,
			._7SegPins[5].portNumber=DIO_enumPortA,
			._7SegPins[5].pinNumber=DIO_enumPin5,
			._7SegPins[5].pinDirection=DIO_enumLogicLow,
			._7SegPins[6].portNumber=DIO_enumPortA,
			._7SegPins[6].pinNumber=DIO_enumPin6,
			._7SegPins[6].pinDirection=DIO_enumLogicLow,
			._7SegPins[7].portNumber=DIO_enumPortA,
			._7SegPins[7].pinNumber=DIO_enumPin7,
			._7SegPins[7].pinDirection=DIO_enumLogicLow,
			._7SegType=COMMON_CATHODE,
		}
	};

