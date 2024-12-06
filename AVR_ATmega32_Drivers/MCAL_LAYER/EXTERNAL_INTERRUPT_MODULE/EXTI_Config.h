/*
 * File Name: EXTI_Config.h
 * Layer	: MCAL
 * Module	: EXTI
 * Version  : V 0.0
 * Target	: AVR-Atmega32
 * Created	: 1/4/2024 10:15:43 AM
 * Author	: Anas Khamees
 * Brief	: This header file defines Required MACROs for EXTI driver.
 * Note		: I used Pre-Compiled configuration in this driver to practice different types of design. 
 */ 
#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_

#include "EXTI.h"

/** 
 *@def    : EXTI0_CONFIG  -->  User-defined configuration macro.
 *@brief  : Choice the Sense Control method to Trigger the INT0.
 *@warning: The Options is below:
 *Option1 : EXTI_INT0_LOW_LEVEL			
 *Option2 : EXTI_INT0_LOGICAL_CHANGE	
 *Option3 : EXTI_INT0_FALLING_EDGE		
 *Option4 : EXTI_INT0_RISING_EDGE
 */
#define EXTI0_CONFIG	EXTI_INT0_LOW_LEVEL
/** 
 *@def    : EXTI1_CONFIG  -->  User-defined configuration macro.
 *@brief  : Choice the Sense Control method to Trigger the INT1
 *@warning: The Options is below:
 *Option1 : EXTI_INT1_LOW_LEVEL			
 *Option2 : EXTI_INT1_LOGICAL_CHANGE	
 *Option3 : EXTI_INT1_FALLING_EDGE		
 *Option4 : EXTI_INT1_RISING_EDGE
 */
#define EXTI1_CONFIG	EXTI_INT1_LOGICAL_CHANGE
/** 
 *@def    : EXTI2_CONFIG  -->  User-defined configuration macro.
 *@brief  : Choice the Sense Control method to Trigger the INT2
 *@warning: The Options is below:
 *Option1 : EXTI_INT2_FALLING_EDGE		
 *Option2 : EXTI_INT2_RISING_EDGE
 */
#define EXTI2_CONFIG	EXTI_INT2_RISING_EDGE
/** 
 *@def    : EXTI0_STATE  -->  User-defined configuration macro.
 *    		EXTI1_STATE  -->  User-defined configuration macro.
 *			EXTI2_STATE  -->  User-defined configuration macro.
 *@brief  : Select The State of Each External Interrupt Source to be Enable or Disable.
 *@warning: The Options is below:
 *Option1 : EXTI_DISABLE
 *Option2 : EXTI_ENABLE
 */
#define EXTI0_STATE		EXTI_ENABLE
#define EXTI1_STATE		EXTI_ENABLE
#define EXTI2_STATE		EXTI_ENABLE



#endif /* EXTI_CONFIG_H_ */