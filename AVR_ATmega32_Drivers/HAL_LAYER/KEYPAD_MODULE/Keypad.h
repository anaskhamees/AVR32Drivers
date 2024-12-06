/*
 * File Name: Keypad.h
 * Layer	: HAL
 * Module	: KEYPAD
 * Version  : V 0.0
 * Created	: 1/7/2024 12:34:48 AM
 * Author	: Anas Khamees
 */ 
#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "../../MCAL_LAYER/DIO_MODULE/DIO_Driver/DIO.h"
#include "../../MCAL_LAYER/DIO_MODULE/PORT_Driver/PORT.h"
#include <util/delay.h>

#define KEYPAD_ROWS_NUMBER		(4U)
#define KEYPAD_COLOMNS_NUMBER	(4U)

/**
 * @enum :KEYPAD_enumError_t
 * @brief: Enumeration representing possible errors for the Keypad module.
 */
typedef enum
{
    KEYPAD_enumOk = 0,           /**< Everything is okay; the function performed correctly. */
    KEYPAD_enumNullPointer,      /**< NULL pointer is passed as a function parameter.		*/
} KEYPAD_enumError_t;

/**
 * @brief Configuration structure for the Keypad module.
 * 
 * This structure holds the configuration for the Keypad module, specifying the pins associated with keypad rows and columns.
 * Each keypad row and column is represented by a DIO_strPinConfig_t structure.
 */
typedef struct
{
	 /**
     * @brief Array of configurations for Keypad Rows.
     * 
     * This array holds the configurations for individual keypad rows, where each element is a DIO_strPinConfig_t structure
     * specifying the DIO pin configurations associated with a keypad row.
     */
	DIO_strPinConfig_t	KeypadRows   [KEYPAD_ROWS_NUMBER]   ;
	 /**
     * @brief Array of configurations for Keypad Columns.
     * 
     * This array holds the configurations for individual keypad columns, where each element is a DIO_strPinConfig_t structure
     * specifying the DIO pin configurations associated with a keypad column.
     */
	DIO_strPinConfig_t	KeypadColomns[KEYPAD_COLOMNS_NUMBER];
	
}KEYPAD_strConfig_t;

/**
 * @brief :  Initialize the Keypad Pins.
 * @param :  Add_strKeypadConfig, Pointer to the keypad configuration structure.
 * @return:  KEYPAD_enumError_t  Error status indicating the success or failure of the initialization.
 */
KEYPAD_enumError_t	KEYPAD_enumInit(KEYPAD_strConfig_t* Add_strKeypadConfig);
/**
 * @brief	  :	Get the pressed value from the Calculator Keypad.
 * @param[in] : Add_strKeypadConfig Pointer to the keypad configuration structure.
 * @param[out]: Add_u8KeyValue Pointer to store the pressed key value.
 * @return	  : KEYPAD_enumError_t Error status indicating the success or failure of getting the pressed value.
 */
KEYPAD_enumError_t	KEYPAD_enumGetPressedValue(KEYPAD_strConfig_t* Add_strKeypadConfig, u8* Add_u8KeyValue);

#endif /* KEYPAD_H_ */