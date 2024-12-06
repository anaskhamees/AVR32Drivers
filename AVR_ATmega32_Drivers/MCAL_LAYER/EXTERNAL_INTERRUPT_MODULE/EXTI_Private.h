/*
 * File Name: EXTI_Private.h
 * Layer	: MCAL
 * Module	: EXTI
 * Version  : V 0.0
 * Target	: AVR-Atmega32
 * Created	: 1/5/2024 12:37:03 AM
 * Author	: Anas Khamees
 * Brief	: This header file defines Addresses of Interrupt Registers in Hardware.
 * Note		: I used Pre-Compiled configuration in this driver to practice different types of design. 
 */ 

#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

/************************************************************************/
/*           The Addresses of Interrupt Registers in Hardware                                                                     */
/************************************************************************/

#define SREG	(*((volatile u8*)0x5F))  /* Address of Status Register in Hardware	  */

/* The MCU Control Register contains control bits for interrupt sense control (INT0, INT1).
 * Bit0 ~ Bit1 for INT0.
 * Bit2 ~ Bit3 for INT1.
 */
#define MCUCR	(*((volatile u8*)0x55)) /* Address of MCU Control Register			  */
/* The MCU Control Register contains control bits for interrupt sense control (INT2).
 * Bit6 for INT2.
 */
#define MCUCSR	(*((volatile u8*)0x54))			  
/*
 *@brief: General Interrupt Control Register (Peripheral Interrupt control register). 
 */
#define GICR	(*((volatile u8*)0x5B))	
/*
 *@brief: General Interrupt Flag Register
 */
#define GIFR	(*((volatile u8*)0x5A))


 
#endif /* EXTI_PRIVATE_H_ */