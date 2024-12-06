/*
 * File Name: PORT.c
 * Layer	: MCAL
 * Module	: DIO
 * Version  : V 0.0
 * Created	: 12/10/2023 11:06:23 PM
 * Author	: Anas Khamees
 */ 
#include "PORT.h"

static u8 PORT_u8InitType=UNINTIALIZED; /*Global Variable to hold the initialization type of the module, Initialized by pin or by port or uninitialized*/
 
/**
 *DDRX_Registers is an array of pointers each one points to DDR register of specific port in Hardware.
 *So, we can modify (read from/write on) on hardware register by modify its memory location which stored in the DDRX array.  
 */
volatile u8* DDRX_Registers [FOUR_PORT]={&DDRA,&DDRB,&DDRC,&DDRD	};
/**
 *PORTX_Registers is an array of pointers each one points to PORT register of specific port in Hardware.
 *So, we can modify (read from/write on) on hardware register by modify its memory location which stored in the PORTX array.  
 */
volatile u8* PORTX_Registers[FOUR_PORT]={&PORTA,&PORTB,&PORTC,&PORTD};
/**
 *PINX_Registers is an array of pointers each one points to DDR register of specific port in Hardware.
 *So, we can modify (read from/write on) on hardware register by modify its memory location which stored in the PINX array.  
 */
volatile u8* PINX_Registers [FOUR_PORT]={&PINA,&PINB,&PINC,&PIND	};
	
/**
 *@brief  : Function to Configure the Pins to be INPUT pin or OUTPUT pin.
 *@param  : Add_strPinConfig, is a pointer points to struct of pin configuration > @ref:DIO_strPinConfig_t.
 *@param  : Port Number,Pin Number,Configuration type(Input/Output).
 *@return : Error State                                               
 */	
DIO_enumError_t PORT_enumSetPinConfig(const DIO_strPinConfig_t *Add_strPinConfig)
{
	DIO_enumError_t PORT_LocEnumRetErr=DIO_enumOk;		/*Initialize the Return Error State by Default Ok*/	
		        
	/**
	 *brief: (Validation Statement) Make sure that, the user Not Pass a Null Pointer.
	 */
	if(NULL==Add_strPinConfig)
	{
		PORT_LocEnumRetErr=DIO_enumNullPointer;
	}
	/**
	 *brief: (Validation Statement) Make sure that, the user does Not Pass a Port Not exist in MCU.
	 */
	else if(((Add_strPinConfig->portNumber)>MAX_PORT_NUM)||((Add_strPinConfig->portNumber)<MIN_PORT_NUM))
	{
		PORT_LocEnumRetErr=DIO_enumWrongPort;
	}
	/**
	 *brief: (Validation Statement) Make sure that, the user does Not Pass a Pin Not exist in MCU.
	 */
	else if(((Add_strPinConfig->pinNumber)>MAX_PIN_NUM)||((Add_strPinConfig->pinNumber)<MIN_PIN_NUM))
	{
		PORT_LocEnumRetErr=DIO_enumWrongPin;
	}
	/**
	 *brief: (Validation Statement) Make sure that, the user does Not Pass a Direction Config Not exist.
	 */
	else if(((Add_strPinConfig->pinDirection)>MAX_DIR_OPTION)||((Add_strPinConfig->pinDirection)<MIN_DIR_OPTION))
	{
		PORT_LocEnumRetErr=DIO_enumWrongConfig;
	}
	/**
	 *brief: Everything is Ok.
	 */
	else
	{
		PORT_u8InitType=INITIALIZED_BY_PIN;    /*Set the flag by Initialization type*/
		switch(Add_strPinConfig->pinDirection)
		{
			case DIO_enumOutputLow: 
			{
				SET_BIT(*DDRX_Registers[Add_strPinConfig->portNumber],Add_strPinConfig->pinNumber);
				CLEAR_BIT(*PORTX_Registers[Add_strPinConfig->portNumber],Add_strPinConfig->pinNumber);
				break;
			}
			case DIO_enumOutputHigh: 
			{
				SET_BIT(*DDRX_Registers[Add_strPinConfig->portNumber],Add_strPinConfig->pinNumber);
				SET_BIT(*PORTX_Registers[Add_strPinConfig->portNumber],Add_strPinConfig->pinNumber);
				break;
			}
			case DIO_enumInputInternalPU:
			{
				CLEAR_BIT(*DDRX_Registers[Add_strPinConfig->portNumber],Add_strPinConfig->pinNumber);
				SET_BIT(*PORTX_Registers[Add_strPinConfig->portNumber],Add_strPinConfig->pinNumber);
				break;
			}
			case DIO_enumInputExternalPD:
			{	
				CLEAR_BIT(*DDRX_Registers[Add_strPinConfig->portNumber],Add_strPinConfig->pinNumber);
				CLEAR_BIT(*PORTX_Registers[Add_strPinConfig->portNumber],Add_strPinConfig->pinNumber);
				break;
			}
			default: 
			{
				/*Nothing To Do but For MISRA*/
			}
		}
	}
	
	return PORT_LocEnumRetErr;
}

/**
 *@brief  : Function to Configure the whole Port(8 pins) at one time to be INPUT or OUTPUT port.
 *@param  : Port Number,Configuration type(Input/Output).
 *@return : Error State                                                                      
 */
DIO_enumError_t PORT_enumSetPortConfig(DIO_enumPorts_t Copy_enumPortNum,DIO_enumDirection_t Copy_enumDirection)
{
	DIO_enumError_t PORT_LocEnumRetErr=DIO_enumOk;		/*Initialize the Return Error State by Default Ok*/
	
	/**
	 *brief: (Validation Statement) Make sure that, the user does Not Pass a Port Not exist in MCU.
	 */
	if((Copy_enumPortNum>MAX_PORT_NUM)||(Copy_enumPortNum<MIN_PORT_NUM))
	{
		PORT_LocEnumRetErr=DIO_enumWrongPort;
	}
	/**
	 *brief: (Validation Statement) Make sure that, the user does Not Pass a Direction Config Not exist.
	 */
	else if((Copy_enumDirection>MAX_DIR_OPTION)||(Copy_enumDirection<MIN_DIR_OPTION))
	{
		PORT_LocEnumRetErr=DIO_enumWrongConfig;
	}
	/**
	 *brief: Everything is Ok.
	 */
	else
	{
		switch(Copy_enumDirection)
		{
			case DIO_enumOutputLow:
			{
				*DDRX_Registers[Copy_enumPortNum]=PORT_OUTPUT;
				*PORTX_Registers[Copy_enumPortNum]=PORT_LOGIC_LOW;
				break;
			}
			case DIO_enumOutputHigh:
			{
				*DDRX_Registers[Copy_enumPortNum]=PORT_OUTPUT;
				*PORTX_Registers[Copy_enumPortNum]=PORT_LOGIC_HIGH;
				break;
			}
			case DIO_enumInputInternalPU:
			{
				*DDRX_Registers[Copy_enumPortNum]=PORT_INPUT;
				*PORTX_Registers[Copy_enumPortNum]=PORT_PULLUP_ON;
				break;
			}
			case DIO_enumInputExternalPD:
			{
				*DDRX_Registers[Copy_enumPortNum]=PORT_INPUT;
				*PORTX_Registers[Copy_enumPortNum]=PORT_PULLDOWN_ON;
				break;
			} 
			default:
			{
				/*Nothing To Do but For MISRA*/
			}
		}
	}
	
	return PORT_LocEnumRetErr;
}

/**
 *@brief  : Function to Initialize the Configuration of port/Pins.
 *@param  : Add_strPinConfig, is a pointer points to struct of pin configuration > @ref:DIO_strPinConfig_t.
 *@param  : Port Number,Pin Number,Configuration type(Input/Output).
 *@return : Error State                                                                      
 */
DIO_enumError_t PORT_enumInitConfig(const DIO_strPinConfig_t *Add_strPinConfig)
{
	 DIO_enumError_t PORT_LocEnumRetErr=DIO_enumOk;		/*Initialize the Return Error State by Default Ok*/
	 PORT_LocEnumRetErr=PORT_enumSetPinConfig(Add_strPinConfig);
	return PORT_LocEnumRetErr; 
}