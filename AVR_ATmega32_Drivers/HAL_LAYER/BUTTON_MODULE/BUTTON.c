/*
 * File Name: BUTTON.h
 * Layer	: HAL
 * Module	: BUTTON
 * Version  : V 0.0
 * Created	: 12/17/2023 12:03:24 PM
 * Author	: Anas Khamees
 */ 
#include "BUTTON.h"

/**
 * @brief	 : Initialize the button.
 * This function initializes the button based on the provided configuration.
 * @param[in]: Add_strButtonConfig Pointer to the button configuration structure.
 * @return	 : BUTTON_enumError_t Error status indicating the success or failure of the operation.
 */
BUTTON_enumError_t BUTTON_enumInit(const BUTTON_strButton_t *Add_strButtonConfig)
{
	BUTTON_enumError_t 	BUTTON_LocRetErr=BUTTON_enumOk; 
	
	/**
     * @brief: Validation Statement - Ensure that the user does not pass a NULL pointer.
     */
    if (NULL == Add_strButtonConfig)
    {
        BUTTON_LocRetErr = BUTTON_enumNullPointer;
    }
    /**
     * @brief: Validation Statement - Ensure that the button configuration type is within the valid enumerators.
     */
   /* else if (((Add_strButtonConfig->ButtonConnection) > BUTTON_ACTIVE_HIGH) || ((Add_strButtonConfig->ButtonConnection) < BUTTON_ACTIVE_LOW))
    {
        BUTTON_LocRetErr = BUTTON_enumWrongConfig;
    }*/
    /**
     * @brief: Validation Statement - Ensure that the button state is within the valid enumerators.
     */
    else if (((Add_strButtonConfig->ButtonState) > BUTTON_PRESSED) || ((Add_strButtonConfig->ButtonState) < BUTTON_RELEASED))
    {
        BUTTON_LocRetErr = BUTTON_enumWrongState;
    }
	 /**
     * @brief: Everything is Ok, The Function Parameters passed Successfully :).
     */
	else
	{
		DIO_enumError_t	DIO_LocRetErr=PORT_enumInitConfig(&(Add_strButtonConfig->Button));
	}
	
	return BUTTON_LocRetErr;
}

/**
 * @brief	  : Read the status of the button.
 * This function reads the status of the button (pressed or released) and returns it.
 * @param[in] : Add_strButtonConfig Pointer to the button configuration structure.
 * @param[out]: Add_enumButtonState Pointer to store the read button state.
 * @return	  :	BUTTON_strButton_t Updated button structure with the current state.
 */
BUTTON_enumError_t BUTTON_enumReadStatus(const BUTTON_strButton_t *Add_strButtonConfig, BUTTON_enumState_t *Add_enumButtonState)
{
	BUTTON_enumError_t 	BUTTON_LocRetErr=BUTTON_enumOk; 
	
	/**
     * @brief: Validation Statement - Ensure that the user does not pass a NULL pointer.
     */
    if ((NULL == Add_strButtonConfig)||(NULL == Add_strButtonConfig))
    {
        BUTTON_LocRetErr = BUTTON_enumNullPointer;
    }
    /**
     * @brief: Validation Statement - Ensure that the button configuration type is within the valid enumerators.
     */
   /* else if (((Add_strButtonConfig->ButtonConnection) > BUTTON_ACTIVE_HIGH) || ((Add_strButtonConfig->ButtonConnection) < BUTTON_ACTIVE_LOW))
    {
        BUTTON_LocRetErr = BUTTON_enumWrongConfig;
    }*/
   
    /**
     * @brief: Validation Statement - Ensure that the button state is within the valid enumerators.
     */
    else if (((Add_strButtonConfig->ButtonState) > BUTTON_PRESSED) || ((Add_strButtonConfig->ButtonState) < BUTTON_RELEASED))
    {
        BUTTON_LocRetErr = BUTTON_enumWrongState;
    }
	 /**
     * @brief: Everything is Ok, The Function Parameters passed Successfully :).
     */
	else
	{
		DIO_enumLogicState_t DIO_LocPinValue;
		DIO_enumError_t		 DIO_LocRetErr=DIO_enumReadPinState(&(Add_strButtonConfig->Button),&DIO_LocPinValue);
		
		switch(Add_strButtonConfig->Button.pinDirection)
		{
			/*
			 * brief: BUTTON_ACTIVE_HIGH: The Pin which assigned with Button is configured by default LOW when No pressing (Released).
			 * When The Button Pressed The Pin which assigned with Button becomes HIGH.
			 */
			case DIO_enumInputExternalPD:
			{
				switch(DIO_LocPinValue)
				{
					case DIO_enumLogicHigh:
						/*
						 *brief: If the the Pin which assigned with Button is HIGH, So the Button is Pressed.
						 */
						*Add_enumButtonState=BUTTON_PRESSED ;break;
					case DIO_enumLogicLow :
						/*
						 *brief: If the the Pin which assigned with Button is LOW, So the Button is Released.
						 */
						*Add_enumButtonState=BUTTON_RELEASED;break;
				}
			}
			break;	// End of case BUTTON_ACTIVE_HIGH
			
			case DIO_enumInputInternalPU:
			{
				switch(DIO_LocPinValue)
				{
					case DIO_enumLogicHigh:
						/*
						 *brief: If the the Pin which assigned with Button is HIGH, So the Button is Released.
						 */
						*Add_enumButtonState=BUTTON_RELEASED;break;
					case DIO_enumLogicLow :
						/*
						 *brief: If the the Pin which assigned with Button is LOW, So the Button is Pressed.
						 */
						*Add_enumButtonState=BUTTON_PRESSED ;break;
				}
			}
			break;	// End of case BUTTON_ACTIVE_LOW
		}
	}
	
	return BUTTON_LocRetErr;
}