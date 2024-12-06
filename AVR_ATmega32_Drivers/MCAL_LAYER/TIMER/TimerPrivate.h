/*
 * TimerPrivate.h
 *
 * Created: 2/26/2024 9:47:25 PM
 *  Author: anask
 */ 


#ifndef TIMERPRIVATE_H_
#define TIMERPRIVATE_H_

/*=========================================== Timer0 Registers Addresses in AVR Atmega32 ===========================================*/

/* 
 *@brief:  The Addresses of TIMER0 Registers in Hardware.
 *TCCR0	: Timer/Counter Control Register for Timer0. It controls the operation and configuration of Timer0.
 *TCNT0	: Timer/Counter Register for Timer0. It holds the current count value of Timer0.
 *OCR0	: Output Compare Register for Timer0. It sets the compare match value for Timer0.
 *TIMSK	: Timer/Counter Interrupt Mask Register for Timer0. It enables or disables Timer0-related interrupts.
 *TIFR	: Timer/Counter Interrupt Flag Register for Timer0. It contains flags indicating the status of Timer0-related interrupts.
 */
#define TCCR0   (*((volatile u8*)0x53)) 
#define TCNT0   (*((volatile u8*)0x52)) 
#define OCR0    (*((volatile u8*)0x5C)) 
#define TIMSK   (*((volatile u8*)0x59)) 
#define TIFR    (*((volatile u8*)0x58)) 
#define SREG	(*((volatile u8*)0x5F))  /* Address of Status Register in Hardware	  */

/*----------------------------------------- MACRO Functions For Validation -------------------------------------*/
#endif /* TIMERPRIVATE_H_ */