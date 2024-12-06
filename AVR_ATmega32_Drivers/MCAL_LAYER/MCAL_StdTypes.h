/*
 * File Name: MCAL_StdTypes.h
 * Layer	: MCAL
 * Version  : V 0.0
 * Created	: 12/10/2023 11:41:19 PM
 * Author	: Anas Khamees
 */ 



#ifndef MCAL_STDTYPES_H_
#define MCAL_STDTYPES_H_

typedef unsigned char u8;
typedef short unsigned int u16;
typedef unsigned long int u32;
typedef float f32;

/***************************MACROs Declerations**************************************/
#define  BIT_MASK	0x01      /*Helper Macro*/
#define  NULL	((void *)0)
/************************************************************************************/

/***********************Macro Functions Declaration*********************************/
#define SET_BIT(REG,BIT_POSN)       (REG|=(BIT_MASK<<BIT_POSN))
#define CLEAR_BIT(REG,BIT_POSN)     (REG&=~(BIT_MASK<<BIT_POSN))
#define TOGGLE_BIT(REG,BIT_POSN)    (REG^=(BIT_MASK<<BIT_POSN))
#define READ_BIT(REG,BIT_POSN)      ((REG>>BIT_POSN)&BIT_MASK)
/**********************************************************************************/





#endif /* MCAL_STDTYPES_H_ */