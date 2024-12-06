/*
 * File Name: Seven_Segment.h
 * Layer	: HAL
 * Module	: SEVEN_SEG
 * Version  : V 0.0
 * Created	: 12/18/2023 4:16:02 PM
 * Author	: Anas Khamees
 * Brief	: This header file defines structures, Enumerators and functions for a 7-segment display driver.
 */ 

#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_

#include "../../MCAL_LAYER/DIO_MODULE/DIO_Driver/DIO.h"
#include "../../MCAL_LAYER/DIO_MODULE/PORT_Driver/PORT.h"


 /* 
 
* Common Cathode Seven Segment Table: 
* Note: I does not use the Decimal Point(DP) Led.
* DP led used in Decimal Numbers Display. 
+---+---+---+---+----+----+----+---+---+
|Digit | DP| G | F | E | D | C | B | A |
+----+----+----+---+---+---+---+---+---+
|  0   | 0 | 0 | 1 | 1 | 1 | 1 | 1 | 1 |
----------------------------------------
|  1   | 0 | 0 | 0 | 0 | 0 | 1 | 1 | 0 |
----------------------------------------
|  2   | 0 | 1 | 0 | 1 | 1 | 0 | 1 | 1 |
----------------------------------------
|  3   | 0 | 1 | 0 | 0 | 1 | 1 | 1 | 1 |
----------------------------------------
|  4   | 0 | 1 | 1 | 0 | 0 | 1 | 1 | 0 |
----------------------------------------
|  5   | 0 | 1 | 1 | 0 | 1 | 1 | 0 | 1 |
----------------------------------------
|  6   | 0 | 1 | 1 | 1 | 1 | 1 | 0 | 1 |
----------------------------------------
|  7   | 0 | 0 | 0 | 0 | 1 | 1 | 1 | 1 |
----------------------------------------
|  8   | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
----------------------------------------
|  9   | 0 | 1 | 1 | 0 | 1 | 1 | 1 | 1 |
----------------------------------------
|  A   | 0 | 1 | 1 | 1 | 0 | 1 | 1 | 1 |
----------------------------------------
|  b   | 0 | 1 | 1 | 1 | 1 | 1 | 0 | 0 |
----------------------------------------
|  C   | 0 | 0 | 1 | 1 | 1 | 0 | 0 | 1 |
----------------------------------------
|  d   | 0 | 1 | 0 | 1 | 1 | 1 | 1 | 0 |
----------------------------------------
|  E   | 0 | 1 | 1 | 1 | 1 | 0 | 0 | 1 |
----------------------------------------
|  F   | 0 | 1 | 1 | 1 | 0 | 0 | 0 | 1 |
+---+---+---+---+---+----+---+----+----+
*/


#define _7SEG_PIN0		0x00	/*The 7_Segment Pin associated with a */
#define _7SEG_PIN1		0x01	/*The 7_Segment Pin associated with b */
#define _7SEG_PIN2		0x02	/*The 7_Segment Pin associated with c */
#define _7SEG_PIN3		0x03	/*The 7_Segment Pin associated with d */
#define _7SEG_PIN4		0x04	/*The 7_Segment Pin associated with e */
#define _7SEG_PIN5		0x05	/*The 7_Segment Pin associated with f */
#define _7SEG_PIN6		0x06	/*The 7_Segment Pin associated with g */
#define _7SEG_PIN7		0x07	/*The 7_Segment Pin associated with dp*/
/**
 * @enum : _7SEG_enumType_t
 * @brief: Enumeration representing the type of 7-segment display (common anode or common cathode).
 */
typedef enum
{
    COMMON_ANODE=0,		/**< Common anode 7-segment display.  */
    COMMON_CATHODE		/**< Common cathode 7-segment display.*/
} _7SEG_enumType_t;

/**
 * @enum : _7SEG_enumError_t
 * @brief: Enumeration representing possible error codes for the 7-segment display driver.
 */
typedef enum
{
    _7SEG_enumOk = 0,           /**< Everything is okay; the function performed correctly. */
    _7SEG_enumNullPointer,      /**< NULL pointer is passed as a function parameter.	   */
    _7SEG_enumWrongType,        /**< Selected _7SEG type not found.						   */
	_7SEG_enumWrongNumber       /**< Selected Number to display out of (0 -> 9).		   */
} _7SEG_enumError_t;

/**
 * @enum : _7SEG_enumNumber_t
 * @brief: Enumeration representing the digits 1 through 9 for 7-segment display.

 */
typedef enum
{
    NUMBER_ZERO=0,
	NUMBER_ONE,
    NUMBER_TWO,
    NUMBER_THREE,
    NUMBER_FOUR,
    NUMBER_FIVE,
    NUMBER_SIX,
    NUMBER_SEVEN,
    NUMBER_EIGHT,
    NUMBER_NINE
} _7SEG_enumNumber_t;


/**
 * @struct: _7SEG_strConfig_t
 * @brief : Structure representing the configuration of a 7-segment display.
 */
typedef struct
{
    DIO_strPinConfig_t  _7SegPins[8]		;	/**< Pin configuration for the 7-segment display.					*/
    _7SEG_enumType_t	_7SegType			;	/**< Type of the 7-segment display (common anode or common cathode).*/
} _7SEG_strConfig_t;

/**
 * @brief	 : Initialize the 7-segment display.
 * This function initializes the 7-segment display based on the provided configuration.
 * @param[in]: Add_str7SEG_Config Pointer to the 7-segment display configuration structure.
 * @return   : _7SEG_enumError_t Error status indicating the success or failure of the operation.
 */
_7SEG_enumError_t _7SEG_enumInit(_7SEG_strConfig_t *Add_str7SEG_Config);

/**
 * @brief    : Display a number on the 7-segment display.
 * This function displays a specific number on the 7-segment display based on the provided configuration.
 * @param[in]: Add_str7SEG_Config Pointer to the 7-segment display configuration structure.
 * @return   : _7SEG_enumError_t Error status indicating the success or failure of the operation.
 */
_7SEG_enumError_t _7SEG_enumDisplay(_7SEG_strConfig_t *Add_str7SEG_Config,_7SEG_enumNumber_t Copy_enumNumber);

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
_7SEG_enumError_t _7SEG_enumDisplayAll(_7SEG_strConfig_t Add_str7SEG_Config[], _7SEG_enumNumber_t Copy_enumNumber);




#endif /* SEVEN_SEGMENT_H_ */