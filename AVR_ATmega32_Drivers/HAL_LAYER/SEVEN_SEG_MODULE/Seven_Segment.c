/*
 * File Name: Seven_Segment.c
 * Layer	: HAL
 * Module	: SEVEN_SEG
 * Version  : V 0.0
 * Created	: 12/18/2023 4:16:02 PM
 * Author	: Anas Khamees
 */ 
#include "Seven_Segment_config.h"
 
static u8 _7SEG_u8Cathod_Numbers[10] = {0b00111111,  // 0
										0b00000110,  // 1
										0b01011011,  // 2
										0b01001111,  // 3
										0b01100110,  // 4
										0b01101101,  // 5
										0b01111101,  // 6
										0b00000111,  // 7
										0b01111111,  // 8
										0b01101111}; // 9
												
/*static u8 _7SEG_u8Anode_Numbers[10] = { 0b11000000,  //0
										0b11111001,	 //1
										0b10100100,	 //2
										0b10110000,	 //3
										0b10011001,	 //4
										0b10010010,	 //5
										0b10000010,	 //6
										0b11111000,	 //7
										0b10000000,	 //8
										0b10010000}; //9
*/

/**
 * @brief	 : Initialize the 7-segment display.
 * This function initializes the 7-segment display based on the provided configuration.
 * @param[in]: Add_str7SEG_Config Pointer to the 7-segment display configuration structure.
 * @return   : _7SEG_enumError_t Error status indicating the success or failure of the operation.
 */
_7SEG_enumError_t _7SEG_enumInit(_7SEG_strConfig_t *Add_str7SEG_Config)
{
	_7SEG_enumError_t _7SEG_LocRetErr = _7SEG_enumOk;

	/* Validation Statement - Ensure that the user does not pass a NULL pointer.*/
	if (NULL == Add_str7SEG_Config)
	{
		_7SEG_LocRetErr = _7SEG_enumNullPointer;
	}
	/* Validation Statement - Ensure that the 7-segment type is within the valid enumerators.*/
	else if (((Add_str7SEG_Config->_7SegType) > COMMON_CATHODE) || ((Add_str7SEG_Config->_7SegType) < COMMON_ANODE))
	{
		_7SEG_LocRetErr = _7SEG_enumWrongType;
	}
	/* Validation Statement - Ensure that the displayed number is within the valid range.*/
	/*else if (((Add_str7SEG_Config->_7SegDisplayedNum) > NUMBER_NINE) || ((Add_str7SEG_Config->_7SegDisplayedNum) < NUMBER_ZERO))
	{
		_7SEG_LocRetErr = _7SEG_enumWrongNumber;
	}*/
	else
	{
		DIO_enumError_t DIO_LocRetErr = DIO_enumOk;

		/* Loop to initialize the configuration for each pin of the 7-segment display.*/
		for (int PinIterator = 0; PinIterator < 7; PinIterator++)
		{
			/* Initialize the port configuration for the current pin.*/
			DIO_LocRetErr = PORT_enumInitConfig(&(Add_str7SEG_Config->_7SegPins[PinIterator]));
		}
	}
	
	return _7SEG_LocRetErr;
}

/**
 * @brief    : Display a number on the 7-segment display.
 * This function displays a specific number on the 7-segment display based on the provided configuration.
 * @param[in]: Add_str7SEG_Config Pointer to the 7-segment display configuration structure.
 * @return   : _7SEG_enumError_t Error status indicating the success or failure of the operation.
 */
_7SEG_enumError_t _7SEG_enumDisplay(_7SEG_strConfig_t *Add_str7SEG_Config,_7SEG_enumNumber_t Copy_enumNumber)
{
	_7SEG_enumError_t _7SEG_LocRetErr=_7SEG_enumOk;
	if(NULL==Add_str7SEG_Config)
	{
		_7SEG_LocRetErr=_7SEG_enumNullPointer;
	}
	else if(((Add_str7SEG_Config->_7SegType)>COMMON_CATHODE) || ((Add_str7SEG_Config->_7SegType)<COMMON_ANODE))
	{
		_7SEG_LocRetErr=_7SEG_enumWrongType;
	}
	else if((Copy_enumNumber>NUMBER_NINE) || (Copy_enumNumber<NUMBER_ZERO))
	{
		_7SEG_LocRetErr=_7SEG_enumWrongNumber;
	}
	else
	{
		DIO_enumError_t DIO_LocRetErr=DIO_enumOk;										
		switch(Add_str7SEG_Config->_7SegType)
		{
			case COMMON_CATHODE:
			{
			    /* If using the decimal point Led in SSD replace 7 by 8 in the loop condition*/
				for(int SSD_Pin=0;SSD_Pin<7;SSD_Pin++)
				{
					DIO_LocRetErr=DIO_enumSetPin(&(Add_str7SEG_Config->_7SegPins[SSD_Pin]),(u8)((_7SEG_u8Cathod_Numbers[Copy_enumNumber]>>SSD_Pin)&BIT_MASK));
				}
			}
			break;
			
			case COMMON_ANODE:
			{
				/* If using the decimal point Led in SSD replace 7 by 8 in the loop condition*/
				for(int SSD_Pin=0;SSD_Pin<7;SSD_Pin++)
				{
					DIO_LocRetErr=DIO_enumSetPin(&(Add_str7SEG_Config->_7SegPins[SSD_Pin]),(u8)((~_7SEG_u8Cathod_Numbers[Copy_enumNumber]>>SSD_Pin)&BIT_MASK));
				}
			}
			break;
			
			default: {/*Nothing To Do but For MISRA*/}
		}
		
	}
	
	return _7SEG_LocRetErr;
}

/**
 * @brief	 : Displays a specific number on all connected 7-segment displays.
 *
 * This function takes an array of _7SEG_strConfig_t structures and a target number as parameters.
 * It iterates through each 7-segment display and calls the _7SEG_enumDisplay function to display
 * the specified number on that display.
 *
 * @param[in]: Add_str7SEG_Config An array of _7SEG_strConfig_t structures representing the configurations of 7-segment displays.
 * @param[in]: Copy_enumNumber The target number to be displayed on all 7-segment displays.
 * @return	 : _7SEG_enumError_t Error status indicating the success or failure of the operation.
 */

_7SEG_enumError_t  _7SEG_enumDisplayAll(_7SEG_strConfig_t Add_str7SEG_Config[], _7SEG_enumNumber_t Copy_enumNumber)
{
	_7SEG_enumError_t _7SEG_LocRetErr=_7SEG_enumOk;
	for(u8 SSD=0;SSD<MAX_7SEGMENTS_USED;SSD++)
	{
		_7SEG_enumError_t _7SEG_LocRetErr=_7SEG_enumDisplay(&Add_str7SEG_Config[SSD],Copy_enumNumber);
	}
	return _7SEG_LocRetErr;
}