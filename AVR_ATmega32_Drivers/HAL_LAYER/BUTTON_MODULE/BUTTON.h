/*
 * File Name: BUTTON.h
 * Layer	: HAL
 * Module	: BUTTON
 * Version  : V 0.0
 * Created	: 12/17/2023 12:03:24 PM
 * Author	: Anas Khamees
 */ 

#ifndef BUTTON_H_
#define BUTTON_H_
#include "../../MCAL_LAYER/DIO_MODULE/DIO_Driver/DIO.h"
#include "../../MCAL_LAYER/DIO_MODULE/PORT_Driver/PORT.h"


/**
 * @enum BUTTON_enumState_t
 * @brief: Enumeration representing the possible states of a button.
 */
typedef enum
{
    BUTTON_RELEASED = 0, /**< Button is in the released state. */
    BUTTON_PRESSED       /**< Button is in the pressed state.  */
} BUTTON_enumState_t;

/**
 * @enum BUTTON_enumConfig_t
 * @brief: Enumeration representing the possible configurations of a button.
 * If it connected As PullUp Resistor Connection   > (Active LOW).
 * If it connected As PullDown Resistor Connection > (Active HIGH).
 */

/*typedef enum
{
    BUTTON_ACTIVE_LOW = 0,  //<  The Pin which assigned with Button is configured as active low. 
    BUTTON_ACTIVE_HIGH      //<  The Pin which assigned with Button is configured as active high.
} BUTTON_enumConfig_t;
*/

/**
 * @struct BUTTON_strButton_t
 * @brief: Structure representing a button.
 */
typedef struct
{
    DIO_strPinConfig_t  Button;			  /**< Pin configuration of the Pin which assigned with the button.	   */
    BUTTON_enumState_t  ButtonState;	  /**< Current state of the button (pressed or released).		       */
  //  BUTTON_enumConfig_t ButtonConnection; /**< Connection of the button in Hardware(active low or active high).*/
} BUTTON_strButton_t;

/**
 * @enum BUTTON_enumError_t
 * @brief: Enumeration representing possible errors for the button module.
 */
typedef enum
{
    BUTTON_enumOk = 0,           /**< Everything is okay; the function performed correctly. */
    BUTTON_enumNullPointer,      /**< NULL pointer is passed as a function parameter.		*/
    BUTTON_enumWrongConfig,      /**< Select Button configuration type not found.			*/
	BUTTON_enumWrongState		 /**< Select Button State type for Initialization not found.*/
} BUTTON_enumError_t;

/**
 * @brief	 : Initialize the button.
 * This function initializes the button based on the provided configuration.
 * @param[in]: Add_strButtonConfig Pointer to the button configuration structure.
 * @return	 : BUTTON_enumError_t Error status indicating the success or failure of the operation.
 */
BUTTON_enumError_t BUTTON_enumInit(const BUTTON_strButton_t *Add_strButtonConfig);

/**
 * @brief	  : Read the status of the button.
 * This function reads the status of the button (pressed or released) and returns it.
 * @param[in] : Add_strButtonConfig Pointer to the button configuration structure.
 * @param[out]: Add_enumButtonState Pointer to store the read button state.
 * @return	  :	BUTTON_strButton_t Updated button structure with the current state.
 */
BUTTON_enumError_t BUTTON_enumReadStatus(const BUTTON_strButton_t *Add_strButtonConfig, BUTTON_enumState_t *Add_enumButtonState);



#endif /* BUTTON_H_ */