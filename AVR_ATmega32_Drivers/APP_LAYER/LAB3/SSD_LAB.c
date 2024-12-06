/*
 * File Name: SevenSeg.c (main)
 * Layer	: APP
 * Version  : V 0.0
 * Created	: 12/18/2023 9:56:30 PM
 * Author	: Anas Khamees
 */ 

#include "../APP.h"
#ifdef APP
#if (APP==_7SEG_LAB)  //Select the Lab Application from APP.h
#include "../../HAL_LAYER/SEVEN_SEG_MODULE/Seven_Segment_config.h"
#include <util/delay.h>

int main(void)
{	
	_7SEG_enumError_t _7SEG_LocRetErr;
	for(u8 SSD_Index=0;SSD_Index<MAX_7SEGMENTS_USED;SSD_Index++)
	{
		_7SEG_LocRetErr=_7SEG_enumInit(&(_7Segment[SSD_Index]));
	}

    /* Replace with your application code */
    while (1) 
    {
		
		for (u8 SSD_Num=0;SSD_Num<=NUMBER_NINE;SSD_Num++)
		{
			_7SEG_LocRetErr=_7SEG_enumDisplayAll(_7Segment,SSD_Num);
			_delay_ms(500);
		}
	}
}
#endif // (APP == _7SEG_LAB)
#endif // ifdef APP