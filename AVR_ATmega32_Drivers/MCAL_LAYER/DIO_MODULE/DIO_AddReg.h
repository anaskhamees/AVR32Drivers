/*
 * File Name: DIO_AddReg.h
 * Layer	: MCAL
 * Module	: DIO
 * Version  : V 0.0
 * Created	: 12/10/2023 11:09:01 PM
 * Author	: Anas Khamees
 */ 

#ifndef DIO_ADDREG_H_
#define DIO_ADDREG_H_

/*****************************MACROs Declerations of Registers Addresses*********************************/
#define DDRA  (*((volatile u8*)0x3A))  /* Address of Data Direction Register of Port A*/
#define PINA  (*((volatile u8*)0X39))  /* Address of Input Pins Register of Port A    */
#define PORTA (*((volatile u8*)0x3B))  /* Address of Data Register of Port A          */

#define DDRB  (*((volatile u8*)0x37))  /* Address of Data Direction Register of Port B*/
#define PINB  (*((volatile u8*)0X36))  /* Address of Input Pins Register of Port B    */
#define PORTB (*((volatile u8*)0x38))  /* Address of Data Register of Port B          */

#define DDRC  (*((volatile u8*)0x34))  /* Address of Data Direction Register of Port C*/
#define PINC  (*((volatile u8*)0X33))  /* Address of Input Pins Register of Port C    */
#define PORTC (*((volatile u8*)0x35))  /* Address of Data Register of Port C          */

#define DDRD  (*((volatile u8*)0x31))  /* Address of Data Direction Register of Port D*/
#define PIND  (*((volatile u8*)0X30))  /* Address of Input Pins Register of Port D    */
#define PORTD (*((volatile u8*)0x32))  /* Address of Data Register of Port D          */

/**************************************************************************************/



#endif /* DIO_ADDREG_H_ */