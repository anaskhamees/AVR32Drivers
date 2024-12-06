/*
 * File Name: LED.c
 * Layer	: HAL
 * Module	: LED
 * Version  : V 0.0
 * Created	: 12/12/2023 11:47:12 PM
 * Author	: Anas Khamees
 */ 
#include "LED.h"

/**
 * @brief	 :Initializes the LED  to be OFF.
 * If the LED is configured as ACTIVE_HIGH, it sets the logic state to DIO_enumLogicLow (LED OFF).
 * If the LED is configured as ACTIVE_LOW, it sets the logic state to DIO_enumLogicHigh (LED OFF).
 * @param[in]:Add_strLedConfig Pointer to the LED configuration structure.
 * @return	 :LED_enumError_t Error status indicating the success or failure of the initialization.
 */
LED_enumError_t LED_enumInit(LED_strConfig_t *Add_strLedConfig)
{
	LED_enumError_t LED_LocRetErr=LED_enumOk;
	/**
	 *brief: (Validation Statement) Make sure that, the user Not Pass a Null Pointer.
	 */
	if(NULL==Add_strLedConfig)
	{
		LED_LocRetErr=LED_enumNullPointer;
	}
	/**
	 *brief: (Validation Statement) Make sure that, the user Not Pass a LED Configuration not exist !.
	 */
	else if(((Add_strLedConfig->LedConfig)>ACTIVE_HIGH)||((Add_strLedConfig->LedConfig)<ACTIVE_LOW))
	{
		LED_LocRetErr=LED_enumWrongConfig;
	}
	/**
	 *brief: (Validation Statement) Make sure that, the user Not Pass a LED Logic not exist !.
	 */
	else if(((Add_strLedConfig->Led_Logic)>LED_ON)||((Add_strLedConfig->Led_Logic)<LED_OFF))
	{
		LED_LocRetErr=LED_enumWrongLogic;
	}
	/**
	 *brief: (Validation Statement) Everything is Ok, the function parameters is passed correctly.
	 */
	else
	{
		DIO_enumError_t DIO_LocRetErr=DIO_enumOk;
		/*LED module in HAL Layer uses DIO module in MCAL Layer to initialize the pins which connected with Led(Layer Abstraction)*/
		DIO_LocRetErr=PORT_enumSetPinConfig(&(Add_strLedConfig->Led));  
		/* Switch statement based on LED polarity configuration*/
		switch(Add_strLedConfig->LedConfig)
		{
			/*Configuring LED as ACTIVE_HIGH, sets the logic state to DIO_enumLogicLow (LED OFF)*/
			case ACTIVE_HIGH:	DIO_LocRetErr=DIO_enumSetPin(&(Add_strLedConfig->Led),DIO_enumLogicLow) ;break;
			/*Configuring LED as ACTIVE_LOW, sets the logic state to DIO_enumLogicHigh (LED OFF)*/
			case ACTIVE_LOW :	DIO_LocRetErr=DIO_enumSetPin(&(Add_strLedConfig->Led),DIO_enumLogicHigh);break;
			default: {/*Nothing to Do but For MISRA*/}
		}
	}
	return LED_LocRetErr;
}

/**
 * @brief	: Turns the LED ON based on provided configuration.
 *            Configures the LED logic state according to polarity configuration.
 *            If the LED is configured as ACTIVE_HIGH, it sets the logic state to DIO_enumLogicHigh(LED ON).
 *            If the LED is configured as ACTIVE_LOW, it sets the logic state to DIO_enumLogicLow  (LED ON).
 *
 * @param[in] : Add_strLedConfig Pointer to the LED configuration structure.
 * @return	  : LED_enumError_t Error status indicating the success or failure of the operation.
 */
LED_enumError_t LED_enumTurnOn(LED_strConfig_t *Add_strLedConfig)
{
	LED_enumError_t LED_LocRetErr = LED_enumOk;

	/**
	 * @brief: Validation Statement - Ensure that the user does not pass a Null Pointer.
	 */
	if (NULL == Add_strLedConfig)
	{
		LED_LocRetErr = LED_enumNullPointer;
	}
	/**
	 * @brief: Validation Statement - Ensure that the user does not pass a LED Configuration that does not exist!
	 */
	else if (((Add_strLedConfig->LedConfig) > ACTIVE_HIGH) || ((Add_strLedConfig->LedConfig) < ACTIVE_LOW))
	{
		LED_LocRetErr = LED_enumWrongConfig;
	}
	/**
	 * @brief: Validation Statement - Ensure that the user does not pass a LED Logic that does not exist!
	 */
	else if (((Add_strLedConfig->Led_Logic) > LED_ON) || ((Add_strLedConfig->Led_Logic) < LED_OFF))
	{
		LED_LocRetErr = LED_enumWrongLogic;
	}
	/**
	 * @brief: Validation Statement - Everything is OK, the function parameters are passed correctly.
	 */
	else
	{
		DIO_enumError_t DIO_LocRetErr = DIO_enumOk;

		/* Switch statement based on LED polarity configuration */
		switch (Add_strLedConfig->LedConfig)
		{
			case ACTIVE_HIGH:
				/*Configuring LED as ACTIVE_HIGH, sets the logic state to DIO_enumLogicHigh(LED ON)*/
				DIO_LocRetErr = DIO_enumSetPin(&(Add_strLedConfig->Led), DIO_enumLogicHigh);break;
			case ACTIVE_LOW:
				/*Configuring LED as ACTIVE_LOW, sets the logic state to DIO_enumLogicLow (LED ON)*/
				DIO_LocRetErr = DIO_enumSetPin(&(Add_strLedConfig->Led), DIO_enumLogicLow);break;
			default:
				{
					/* Nothing to do but for MISRA */
				}
		}
	}

	return LED_LocRetErr;
}


/**
 * @brief	 : Turns the LED to be OFF based on provided polarity configuration.
 *            If the LED is configured as ACTIVE_HIGH, it sets the logic state to DIO_enumLogicLow (LED OFF).
 *            If the LED is configured as ACTIVE_LOW, it sets the logic state to DIO_enumLogicHigh (LED OFF).
 * @param[in]:Add_strLedConfig Pointer to the LED configuration structure > @Ref: LED_strConfig_t.
 * @return	 :LED_enumError_t Error status indicating the success or failure of the Function.
 */
LED_enumError_t LED_enumTurnOff(LED_strConfig_t *Add_strLedConfig)
{
	LED_enumError_t LED_LocRetErr=LED_enumOk;
	/**
	 *brief: (Validation Statement) Make sure that, the user Not Pass a Null Pointer.
	 */
	if(NULL==Add_strLedConfig)
	{
		LED_LocRetErr=LED_enumNullPointer;
	}
	/**
	 *brief: (Validation Statement) Make sure that, the user Not Pass a LED Configuration not exist !.
	 */
	else if(((Add_strLedConfig->LedConfig)>ACTIVE_HIGH)||((Add_strLedConfig->LedConfig)<ACTIVE_LOW))
	{
		LED_LocRetErr=LED_enumWrongConfig;
	}
	/**
	 *brief: (Validation Statement) Make sure that, the user Not Pass a LED Logic not exist !.
	 */
	else if(((Add_strLedConfig->Led_Logic)>LED_ON)||((Add_strLedConfig->Led_Logic)<LED_OFF))
	{
		LED_LocRetErr=LED_enumWrongLogic;
	}
	/**
	 *brief: (Validation Statement) Everything is Ok, the function parameters is passed correctly.
	 */
	else
	{
		DIO_enumError_t DIO_LocRetErr=DIO_enumOk;
		
		/* Switch statement based on LED polarity configuration*/
		switch(Add_strLedConfig->LedConfig)
		{
			/*Configuring LED as ACTIVE_HIGH, sets the logic state to DIO_enumLogicLow (LED OFF)*/
			case ACTIVE_HIGH:	DIO_LocRetErr=DIO_enumSetPin(&(Add_strLedConfig->Led),DIO_enumLogicLow) ;break;
			/*Configuring LED as ACTIVE_LOW, sets the logic state to DIO_enumLogicHigh (LED OFF)*/
			case ACTIVE_LOW :	DIO_LocRetErr=DIO_enumSetPin(&(Add_strLedConfig->Led),DIO_enumLogicHigh);break;
			default: {/*Nothing to Do but For MISRA*/}
		}
	}
	return LED_LocRetErr;
}

/**
 * @brief	 :Toggles the state of the LED (turns it on if it's off, and vice versa).
 * @param[in]:Add_strLedConfig Pointer to the LED configuration structure.
 * @return	 :LED_enumError_t Error status indicating the success or failure of the operation.
 */
LED_enumError_t LED_enumToggle(LED_strConfig_t *Add_strLedConfig)
{
	LED_enumError_t LED_LocRetErr = LED_enumOk;

	/**
	 * @brief: Validation Statement - Ensure that the user does not pass a Null Pointer.
	 */
	if (NULL == Add_strLedConfig)
	{
		LED_LocRetErr = LED_enumNullPointer;
	}
	/**
	 * @brief: Validation Statement - Ensure that the user does not pass a LED Configuration that does not exist!
	 */
	else if (((Add_strLedConfig->LedConfig) > ACTIVE_HIGH) || ((Add_strLedConfig->LedConfig) < ACTIVE_LOW))
	{
		LED_LocRetErr = LED_enumWrongConfig;
	}
	/**
	 * @brief: Validation Statement - Ensure that the user does not pass a LED Logic that does not exist!
	 */
	else if (((Add_strLedConfig->Led_Logic) > LED_ON) || ((Add_strLedConfig->Led_Logic) < LED_OFF))
	{
		LED_LocRetErr = LED_enumWrongLogic;
	}
	/**
	 * @brief: Validation Statement - Everything is OK, the function parameters are passed correctly.
	 */
	else
	{
		DIO_enumError_t DIO_LocRetErr = DIO_enumOk;

		DIO_LocRetErr=DIO_enumTogglePin(&(Add_strLedConfig->Led));
		
	}

	return LED_LocRetErr;
}