/*
 * File Name: DIO.c
 * Layer	: MCAL
 * Module	: DIO
 * Version  : V 0.0
 * Created	: 12/10/2023 10:59:41 PM
 * Author	: Anas Khamees
 */ 
#ifndef DIO_H_
#define DIO_H_

#include "../DIO_AddReg.h"
#include "../../MCAL_StdTypes.h"

/*************** Helper Macros To set any bit by 0 or 1******************/
#define PINx_LOW			0
#define PINx_HIGH			1
/**********************PORT DRIVER MACROs********************************/
#define	 ONE_PORT			0x01
#define	 TWO_PORT			0x02
#define  THREE_PORT			0x03
#define  FOUR_PORT			0x04
/********************** Helper PORT MACROs********************************/
#define  PORT_OUTPUT		0xFF	/* Set The Whole Port To be OUTPUT		(DDRX) : 0b1111 1111						 */
#define  PORT_INPUT			0x00	/* Set The Whole Port To be INPUT		(DDRX) : 0b0000 0000						 */
#define  PORT_PULLUP_ON		0xFF    /* Set The Whole Port To be INPUT PU	(PORTX): 0b1111 1111 and (DDRX) : 0b0000 0000*/
#define	 PORT_PULLDOWN_ON	0x00	/* Set The Whole Port To be INPUT PD	(PORTX): 0b0000 0000 and (DDRX) : 0b0000 0000*/
#define  PORT_LOGIC_HIGH	0xFF	/* Set The Whole Port To be OUTPUT HIGH (PORTX): 0b1111 1111 and (DDRX) : 0b1111 1111*/
#define	 PORT_LOGIC_LOW     0x00	/* Set The Whole Port To be OUTPUT LOW  (PORTX): 0b0000 0000 and (DDRX) : 0b1111 1111*/
#define  PORT_TOGGLE_MASK	0xFF    /* Toggle the Logic of Whole Port  0b1111 1111										 */				
/***********************************************************************/
#define INITIALIZED_BY_PIN	0x00    /* Helper Macro to ensure that the PORT Driver Initialized by Pins		*/
#define INITIALIZED_BY_PORT	0x01	/* Helper Macro to ensure that the PORT Driver Initialized by Whole Port*/
#define UNINTIALIZED		0x02	/* Helper Macro to Initialize the Initialization Flag by default value	*/
/**********************************************************************/
/**
 *DDRX_Registers is an array of pointers each one points to DDR register of specific port in Hardware.
 *So, we can modify (read from/write on) on hardware register by modify its memory location which stored in the DDRX array.  
 */
extern volatile u8* DDRX_Registers [FOUR_PORT];
/**
 *PORTX_Registers is an array of pointers each one points to PORT register of specific port in Hardware.
 *So, we can modify (read from/write on) on hardware register by modify its memory location which stored in the PORTX array.  
 */
extern volatile u8* PORTX_Registers[FOUR_PORT];
/**
 *PINX_Registers is an array of pointers each one points to DDR register of specific port in Hardware.
 *So, we can modify (read from/write on) on hardware register by modify its memory location which stored in the PINX array.  
 */
extern volatile u8* PINX_Registers [FOUR_PORT];

typedef enum
{
	DIO_enumLogicLow=0, 
	DIO_enumLogicHigh
}DIO_enumLogicState_t;

typedef enum
{  
	DIO_enumPortA=0,
	DIO_enumPortB,
	DIO_enumPortC,
	DIO_enumPortD
}DIO_enumPorts_t;

/**
 *@brief : Maximum Port Number                                           
 */
#define MAX_PORT_NUM	DIO_enumPortD

/**
 *@brief : Minimum Port Number                                           
 */
#define MIN_PORT_NUM	DIO_enumPortA


typedef enum
{
	DIO_enumPin0=0,
	DIO_enumPin1,
	DIO_enumPin2,
	DIO_enumPin3,
	DIO_enumPin4,
	DIO_enumPin5,
	DIO_enumPin6,
	DIO_enumPin7
}DIO_enumPins_t;

/**
 *@brief : Maximum Pin Number the User can Select                                       
 */
#define MAX_PIN_NUM		DIO_enumPin7
/**
 *@brief : Minimum Pin Number, the User can Select                                           
 */
#define MIN_PIN_NUM		DIO_enumPin0
/**
 *@brief : The Error List Type                                           
 */
typedef enum 
{
	/**
	 *@brief : Everything Ok, Function Performed Correctly.
	 */
	DIO_enumOk=0,             
	/**
	 *@brief : NULL Pointer is passed.
	 */
	DIO_enumNullPointer,
	/**
	 *@brief : Select Port Not exist ! .
	 */    
	DIO_enumWrongPort,      
	/**
	 *@brief : Select Pin Not exist ! .
	 */
	DIO_enumWrongPin, 
	/**
	 *@brief : Select Configuration type Not Found .
	 */     
	DIO_enumWrongConfig,    
	/**
	 *@brief : Select Logic State type Not Found .
	 */     
	DIO_enumWrongLogic
}DIO_enumError_t;
	
/**
 *@brief : The Configuration Type of Pins to be Input or Output !        
 */
typedef enum
{	
	DIO_enumOutputLow=0,			/* Select Pin Configuration to be Output LOW     */
	DIO_enumOutputHigh,				/* Select Pin Configuration to be Output HIGH    */
	DIO_enumInputInternalPU,		/* Select Pin Configuration to be Input Pull Up  */
	DIO_enumInputExternalPD			/* Select Pin Configuration to be Input Pull DOWN*/
}DIO_enumDirection_t;

/**
 *@brief : Maximum Pin Direction option , the User can Select                                          
 */
#define MAX_DIR_OPTION		DIO_enumInputExternalPD
/**
 *@brief : Minimum Pin Direction option, the User can Select                                           
 */
#define MIN_DIR_OPTION		DIO_enumOutputLow
/*
 * Structure representing the configuration of a Digital Input/Output (DIO) pin.
 * Each Pin has 4 attributes:
 * Port Number	: PortA, PortB, PortC, PortD.
 * Pin  Number	: Pin0, Pin1, Pin2, Pin3, Pin4 ,Pin5 ,Pin6 ,Pin7.
 * Pin Direction: OUTPUT_HIGH, OUTPUT_LOW, INPUT PULLUP, INPUT PULLDOWN.
 * Initial Logic: Logic_HIGH, Logic_LOW.
 */
typedef struct {
    // Enumeration to represent the port of the DIO pin (3 bits).
    DIO_enumPorts_t       portNumber  : 3;		/* we need only 3 bits to represent the port, the max port number is 4(0100)PortD)*/

    // Enumeration to represent the pin number of the DIO pin (3 bits).
    DIO_enumPins_t        pinNumber	  : 3;		/* we need only 3 bits to represent the pin, the max pin number is 7(0111)Pin7).  */

    // Enumeration to represent the direction of the DIO pin (1 bit).
    DIO_enumDirection_t   pinDirection: 3;		/* we need only 3 bit to represent the Pin Direction							  */
	
    // Enumeration to represent the logic state of the DIO pin (1 bit).
    DIO_enumLogicState_t  pinLogic    : 1;		/* we need only 1 bit to represent the Pin Logic								  */

} DIO_strPinConfig_t;


/************************************Functions Declaration(DIO_MODULE_INTERFACES)*************************/

/**
 *@brief : Function to Set the pins of MCU to be Logic HIGH  or Logic LOW.
 *@param : Add_strPinConfig, is a pointer points to struct of pin configuration > @ref:DIO_strPinConfig_t.
 *@param : Logic State(HIGH/LOW).
 *@return: Error State.                                                                      
 */
DIO_enumError_t DIO_enumSetPin(const DIO_strPinConfig_t *Add_strPinConfig,DIO_enumLogicState_t Copy_enumLogic);

/**
 *@brief  : Function to Set the whole Port(8 pins) at one time to be Logic HIGH  or Logic LOW.
 *@param  : Port Number,Logic State(HIGH/LOW).
 *@warning: Copy_u8LogicState has only two values: PORT_LOGIC_LOW or PORT_LOGIC_HIGH
 *@return : Error State.                                                                      
 */
DIO_enumError_t DIO_enumSetPort(DIO_enumPorts_t Copy_enumPortNum,u8 Copy_u8PortLogic); 
/**
 *@brief : Function to Toggle the Pin.
 *@param : Add_strPinConfig, is a pointer points to struct of pin configuration > @ref:DIO_strPinConfig_t.
 *@Param :Port Number,Pin Number.
 *@return:Error State.
 */
DIO_enumError_t DIO_enumTogglePin(const DIO_strPinConfig_t *Add_strPinConfig);

/**
 *@brief  : Function to Toggle the Logic of the whole Port(8 pins) at one time .
 *@param  : Port Number.
 *@return : Error State.                                                                      
 */
DIO_enumError_t DIO_enumTogglePort(DIO_enumPorts_t Copy_enumPortNum); 
/**
 *@brief  : Function to Read the Logic State of the Pin (Is it HIGH or LOW).
 *@param : Add_strPinConfig, is a pointer points to struct of pin configuration > @ref:DIO_strPinConfig_t.
 *@param  : Port Number,Pin Number, Pointer points to DIO_enumLogicState_t passed by address (to return the value of pin state).
 *@return : Error State                                                                     
 */
DIO_enumError_t DIO_enumReadPinState(const DIO_strPinConfig_t *Add_strPinConfig,volatile DIO_enumLogicState_t* Add_PenumPinValue);



#endif /* DIO_H_ */