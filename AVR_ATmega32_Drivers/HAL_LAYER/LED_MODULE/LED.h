/*
 * File Name: LED.h
 * Layer	: HAL
 * Module	: LED
 * Version  : V 0.0
 * Created	: 12/12/2023 11:47:12 PM
 * Author	: Anas Khamees
 */ 

#ifndef LED_H_
#define LED_H_
#include "../../MCAL_LAYER/DIO_MODULE/DIO_Driver/DIO.h"
#include "../../MCAL_LAYER/DIO_MODULE/PORT_Driver/PORT.h"



/**
 * @brief Enumeration defining the configuration options for LED polarity.
 */
typedef enum {
    ACTIVE_LOW=0,   /**< LED is active low (low voltage level corresponds to LED ON).  */
    ACTIVE_HIGH,    /**< LED is active high (high voltage level corresponds to LED ON).*/

} LED_enumConfig_t;

/**
 * @brief Enumeration defining the logic states for LED.
 */
typedef enum {
    LED_OFF = 0, /**< LED is turned off. */
    LED_ON      /**< LED is turned on. */
} LED_enumLogic_t;

typedef enum 
{
	/**
	 *@brief : Everything Ok, Function Performed Correctly.
	 */
	LED_enumOk=0,             
	/**
	 *@brief : NULL Pointer is passed.
	 */
	LED_enumNullPointer, 
	/**
	 *@brief : Select Configuration type Not Found .
	 */     
	LED_enumWrongConfig,    
	/**
	 *@brief : Select Logic State type Not Found .
	 */     
	LED_enumWrongLogic
}LED_enumError_t;
/**
 * @brief Structure defining the LED configuration.
 */
typedef struct {
	DIO_strPinConfig_t  Led;          /**< Configuration structure for the associated DIO pin of the LED. */
	LED_enumLogic_t  Led_Logic;    /**< Logic state of the LED (ON/OFF). */
	LED_enumConfig_t LedConfig;    /**< Configuration option for LED polarity (ACTIVE_HIGH/ACTIVE_LOW). */
} LED_strConfig_t;

/**
 * @brief	 :Initializes the LED based on the provided configuration.
 * @param[in]:Add_strLedConfig Pointer to the LED configuration structure.
 * @return	 :LED_enumError_t Error status indicating the success or failure of the initialization.
 */
LED_enumError_t LED_enumInit(LED_strConfig_t *Add_strLedConfig);

/**
 * @brief	 :Turns on the LED.
 * @param[in]:Add_strLedConfig Pointer to the LED configuration structure.
 * @return	 :LED_enumError_t Error status indicating the success or failure of the operation.
 */
LED_enumError_t LED_enumTurnOn(LED_strConfig_t *Add_strLedConfig);

/**
 * @brief	 :Turns off the LED.
 * @param[in]:Add_strLedConfig Pointer to the LED configuration structure.
 * @return	 :LED_enumError_t Error status indicating the success or failure of the operation.
 */
LED_enumError_t LED_enumTurnOff(LED_strConfig_t *Add_strLedConfig);

/**
 * @brief	 :Toggles the state of the LED (turns it on if it's off, and vice versa).
 * @param[in]:Add_strLedConfig Pointer to the LED configuration structure.
 * @return	 :LED_enumError_t Error status indicating the success or failure of the operation.
 */
LED_enumError_t LED_enumToggle(LED_strConfig_t *Add_strLedConfig);



#endif /* LED_H_ */