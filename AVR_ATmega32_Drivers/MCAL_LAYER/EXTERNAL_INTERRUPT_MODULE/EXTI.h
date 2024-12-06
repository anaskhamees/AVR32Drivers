/*
 * File Name: EXTI.h
 * Layer	: MCAL
 * Module	: EXTI
 * Version  : V 0.0
 * Target	: AVR-Atmega32
 * Created	: 1/4/2024 10:15:43 AM
 * Author	: Anas Khamees
 * Brief	: This header file defines Required MACROs for EXTI driver.
 * Note		: I used Pre-Compiled configuration in this driver to practice different types of design. 
 */ 

#ifndef EXTI_H_
#define EXTI_H_
#include "EXTI_Private.h"
#include "../MCAL_StdTypes.h"


/************************************************************************/
/*		The configuration MACROs of Interrupt Sources INT0,INT1,INT2    */
/************************************************************************/

/** 
 *@brief: MCU Control Register – MCUCR responsible for The Sense control configuration of INT0,INT1 (datasheet Pg.66).
 +---+---+---+---+-----+-----+-----+-----+
 | 7 | 6 | 5 | 4 |  3  |  2  |  1  |  0  |
 +---+---+---+---+-----+-----+-----+-----+
 | x | x | x | x |ISC11|ISC10|ISC01|ISC00|
 +----+-----+----+-----+-----+-----+-----+
 */

/**
 * @def     EXTI_INT0_LOW_LEVEL		 --> User-defined configuration macro.
 *			EXTI_INT0_LOGICAL_CHANGE --> User-defined configuration macro.
 *			EXTI_INT0_FALLING_EDGE	 --> User-defined configuration macro.
 *			EXTI_INT0_RISING_EDGE	 --> User-defined configuration macro.
 * @brief   Definition for INT0 sense control - Low Level or Logical Change or Rising Edge or Falling Edge.
 +-----+-----+-----------------------------------------------------------+
 |ISC01|ISC00| Description											     |
 +-----+-----+-----------------------------------------------------------+
 |  0  |  0  | The low level of INT0 generates an interrupt request.     |
 +-----+-----+-----------------------------------------------------------+
 |  0  |  1  | Any logical change on INT0 generates an interrupt request.|
 +-----+-----+-----------------------------------------------------------+
 |  1  |  0  | The falling edge of INT0 generates an interrupt request.  |
 +-----+-----+-----------------------------------------------------------+
 |  1  |  1  | The rising edge of INT0 generates an interrupt request.   |
 +-----+-----+-----------------------------------------------------------+
 */
#define EXTI_INT0_LOW_LEVEL			(0U)
#define EXTI_INT0_LOGICAL_CHANGE	(1U)
#define EXTI_INT0_FALLING_EDGE		(2U)
#define EXTI_INT0_RISING_EDGE		(3U)

/**

 * @def     EXTI_INT1_LOW_LEVEL		 --> User-defined configuration macro.
 *			EXTI_INT1_LOGICAL_CHANGE --> User-defined configuration macro.
 *			EXTI_INT1_FALLING_EDGE	 --> User-defined configuration macro.
 *			EXTI_INT1_RISING_EDGE	 --> User-defined configuration macro.
 * @brief   Definition for INT1 sense control - Low Level or Logical Change or Rising Edge or Falling Edge.
 +-----+-----+-----------------------------------------------------------+
 |ISC11|ISC10| Description											     |
 +-----+-----+-----------------------------------------------------------+
 |  0  |  0  | The low level of INT1 generates an interrupt request.     |
 +-----+-----+-----------------------------------------------------------+
 |  0  |  1  | Any logical change on INT1 generates an interrupt request.|
 +-----+-----+-----------------------------------------------------------+
 |  1  |  0  | The falling edge of INT1 generates an interrupt request.  |
 +-----+-----+-----------------------------------------------------------+
 |  1  |  1  | The rising edge of INT1 generates an interrupt request.   |
 +-----+-----+-----------------------------------------------------------+
 */
#define EXTI_INT1_LOW_LEVEL			(0U)
#define EXTI_INT1_LOGICAL_CHANGE	(1U)
#define EXTI_INT1_FALLING_EDGE		(2U)
#define EXTI_INT1_RISING_EDGE		(3U)

/** 
 *@brief: MCU Control and Status Register – MCUCSR (Bit6) responsible for The Sense control configuration of INT2 (datasheet Pg.67).
 +---+---+---+---+-----+---+---+---+
 | 7 |  6  | 5 | 4 | 3 | 2 | 1 | 0 |
 +---+-----+---+---+---+---+---+---+
 | x |ISC2 | x | x | x | x | x | x |
 +---+-----+---+---+---+---+---+---+
 */

/**
 * @def     EXTI_INT2_FALLING_EDGE	 --> User-defined configuration macro.
 *			EXTI_INT2_RISING_EDGE	 --> User-defined configuration macro.
 * @brief   Definition for INT2 sense control - Rising Edge or Falling Edge.
+-----+------------------------------------------------------+
|ISC2 | Description								       		 |
+-----+------------------------------------------------------+
|  0  | The Falling Edge on INT2 activates the interrupt.    |
+-----+------------------------------------------------------+
|  1  | The Rising Edge on INT2 activates the interrupt.     |
+-----+------------------------------------------------------+
*/
#define EXTI_INT2_FALLING_EDGE	(0U)
#define EXTI_INT2_RISING_EDGE	(1U)
/**
 *@brief: ISC2 Bit Position in the MCUCSR(INT2 Interrupt Sense Control). 
 * See to the table of MCUCSR above to understand.
 */
#define EXTI_INT2_ISC_BIT		(6U)
/**
 *@brief: MACROs for Enable/Disable the Interrupt. 
 */
 #define EXTI_DISABLE		(0U)
 #define EXTI_ENABLE		(1U)
/*
 *@brief: Mask MACROs for clear the INT0 and INT1 bits in sense control register MCUCR.
 */
#define EXTI_INT0_CLEAR_MASK	(0xFC) /* 0b 1111 1100 (See to the register table above to understand)*/
#define EXTI_INT1_CLEAR_MASK	(0xF3) /* 0b 1111 0011 (See to the register table above to understand)*/

/**
 *@brief: INT0,INT1,INT2 Bit Position in the GICR(General Interrupt Control Register). 
 */

/** 
 *@brief: General Interrupt Control Register – GICR (datasheet Pg.67).
 +----+----+----+---+---+---+---+---+
 |  7 | 6  | 5  | 4 | 3 | 2 | 1 | 0 |
 +----+----+----+---+---+---+---+---+
 |INT1|INT0|INT2| - | - | - | x | x |
 +----+----+----+---+---+---+---+---+
 */
#define EXTI_INT0_BIT_POS		(6U)
#define EXTI_INT1_BIT_POS		(7U)
#define EXTI_INT2_BIT_POS		(5U)
 
 /** 
 *@brief: General Interrupt Flag Register – GIFR (datasheet Pg.68).
 +----+----+----+---+---+---+---+---+
 |  7 | 6  | 5  | 4 | 3 | 2 | 1 | 0 |
 +----+----+----+---+---+---+---+---+
 |INT1|INT0|INT2| x | x | x | x | x |
 +----+----+----+---+---+---+---+---+
 */
#define EXTI_INT0_FLAG_BIT		(6U)
#define EXTI_INT1_FLAG_BIT		(7U)
#define EXTI_INT2_FLAG_BIT		(5U)

/** 
 *@brief: Status  Register – SREG (datasheet Pg.10).
 *The Global Interrupt Enable bit (Bit-7) must be set for the interrupts to be enabled.
 +---+---+---+---+---+---+---+---+
 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 +---+---+---+---+---+---+---+---+
 | I | x | x | x | x | x | x | x |
 +---+---+---+---+---+---+---+---+
 */
#define GLOBAL_INT_BIT			(7U)

/** 
 *@brief: User-defined  macros represent the Interrupt Sources.
 */
#define EXTI0_SOURCE		(1U)
#define EXTI1_SOURCE		(2U)
#define EXTI2_SOURCE		(3U)
/** 
 *@brief: User-defined macros for Error status of functions.
 */
#define EXTI_OK				   (0U)
#define EXTI_NULL_POINTER	   (1U)
#define EXTI_WRONG_SENSE_CFG   (2U)
#define EXTI_WRONG_INT_SOURCE  (3U)


/************************************************************************/
/*		   The APIs of Interrupt Sources INT0,INT1,INT2				    */
/************************************************************************/

/**
 * @brief  : Initialize External Interrupts (INT0, INT1, INT2)
 * @details: This function initializes and configures External Interrupts (INT0, INT1, INT2) based on the user-defined
 *           configurations in external_interrupt_config.h file. It includes steps to enable/disable interrupts,
 *           set global interrupt enable, configure sense control, and handle invalid configurations during compile-time.
 */
void EXTI_voidInit(void);
/**
 * @brief  : Set Callback Function for External Interrupts (INT0, INT1, INT2)
 * @details: This function allows users to set their own callback functions to be executed when the corresponding
 *           External Interrupts (INT0, INT1, INT2) occur. Users should provide the callback function and specify
 *           the interrupt source (INT0_SOURCE, INT1_SOURCE, INT2_SOURCE) for which the callback is intended.
 *
 * @param  : App_ISR        Pointer to the user-defined interrupt service routine (ISR).
 * @param  : Copy_u8INTSource  The interrupt source for which the callback is intended (INT0_SOURCE, INT1_SOURCE, INT2_SOURCE).
 * @warning: There are only 3-options for "Copy_u8INTSource":
 * Option1 : INT0_SOURCE  ---> User-defined configuration Macro.
 * Option2 : INT1_SOURCE  ---> User-defined configuration Macro.
 * Option3 : INT2_SOURCE  ---> User-defined configuration Macro.
 */
void EXTI_voidSetCallBack(void(*App_ISR)(void),u8 Copy_u8INTSource);

#endif /* EXTI_H_ */