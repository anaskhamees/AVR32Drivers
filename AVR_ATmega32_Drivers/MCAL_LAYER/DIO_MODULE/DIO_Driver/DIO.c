/*
 * File Name: DIO.c
 * Layer	: MCAL
 * Module	: DIO
 * Version  : V 0.0
 * Created	: 12/10/2023 11:05:30 PM
 * Author	: Anas Khamees
 */ 
#include "DIO.h"

/**
 *@brief : Function to Set the pins of MCU to be Logic HIGH  or Logic LOW.
 *@param : Add_strPinConfig, is a pointer points to struct of pin configuration > @ref:DIO_strPinConfig_t.
 *@param : Logic State(HIGH/LOW).
 *@return: Error State.                                                                      
 */
DIO_enumError_t DIO_enumSetPin(const DIO_strPinConfig_t *Add_strPinConfig,DIO_enumLogicState_t Copy_enumLogic)
{
	DIO_enumError_t DIO_LocEnumRetErr=DIO_enumOk;		/*Initialize the Return Error State by Default Ok*/
	
	/**
	 *brief: (Validation Statement) Make sure that, the user Not Pass a Null Pointer.
	 */
	if(NULL==Add_strPinConfig)
	{
		DIO_LocEnumRetErr=DIO_enumNullPointer;
	}
	/**
	 *brief: (Validation Statement) Make sure that, the user does Not Pass a Port Not exist in MCU.
	 */
	else if(((Add_strPinConfig->portNumber)>MAX_PORT_NUM)||((Add_strPinConfig->portNumber)<MIN_PORT_NUM))
	{
		DIO_LocEnumRetErr=DIO_enumWrongPort;
	}
	/**
	 *brief: (Validation Statement) Make sure that, the user does Not Pass a Pin Not exist in MCU.
	 */
	else if(((Add_strPinConfig->pinNumber)>MAX_PIN_NUM)||((Add_strPinConfig->pinNumber)<MIN_PIN_NUM))
	{
		DIO_LocEnumRetErr=DIO_enumWrongPin;
	}
	/**
	 *brief: (Validation Statement) Make sure that, the user does Not Pass a Direction Config Not exist.
	 */
	else if(((Add_strPinConfig->pinDirection)==DIO_enumInputInternalPU)||((Add_strPinConfig->pinDirection)==DIO_enumInputExternalPD))
	{
		DIO_LocEnumRetErr=DIO_enumWrongConfig;
	}
	/**
	 *brief: (Validation Statement) Make sure that, the user does Not Pass a Logic Config Not exist.
	 */
	else if(((Add_strPinConfig->pinLogic)>DIO_enumLogicHigh)||((Add_strPinConfig->pinLogic)<DIO_enumLogicLow))
	{
		DIO_LocEnumRetErr=DIO_enumWrongLogic;
	}
	/**
	 *brief: Everything is Ok.
	 */
	else
	{
		switch(Copy_enumLogic)
		{
			case DIO_enumLogicHigh: SET_BIT(*PORTX_Registers[Add_strPinConfig->portNumber],Add_strPinConfig->pinNumber);break;
			case DIO_enumLogicLow :CLEAR_BIT(*PORTX_Registers[Add_strPinConfig->portNumber],Add_strPinConfig->pinNumber);break;
			default: { /*Nothing To Do but For MISRA*/}
		}
	}
	
	return DIO_LocEnumRetErr;
}

/**
 *@brief : Function to Set the whole Port(8 pins) at one time to be Logic HIGH  or Logic LOW.
 *@param : Port Number,Logic State(HIGH/LOW).
 *@return: Error State.                                                                      
 */
DIO_enumError_t DIO_enumSetPort(DIO_enumPorts_t Copy_enumPortNum,u8 Copy_u8PortLogic)
{
	DIO_enumError_t DIO_LocEnumRetErr=DIO_enumOk;		/*Initialize the Return Error State by Default Ok*/
	
	/**
	 *brief: (Validation Statement) Make sure that, the user does Not Pass a Port Not exist in MCU.
	 */
	if((Copy_enumPortNum>MAX_PORT_NUM)||(Copy_enumPortNum<MIN_PORT_NUM))
	{
		DIO_LocEnumRetErr=DIO_enumWrongPort;
	}
	/**
	 *brief: (Validation Statement) Make sure that, the user does Not Pass a Wrong Logic Config.
	 */
	else if((Copy_u8PortLogic !=PORT_LOGIC_HIGH)&&(Copy_u8PortLogic !=PORT_LOGIC_LOW))
	{
		DIO_LocEnumRetErr=DIO_enumWrongLogic;
	}
	/** 
	 *brief: Everything is Ok.
	 */
	else
	{
		*PORTX_Registers[Copy_enumPortNum]=Copy_u8PortLogic;
	}
	
	return DIO_LocEnumRetErr;
}
/**
 *@brief : Function to Toggle the Pin.
 *@param : Add_strPinConfig, is a pointer points to struct of pin configuration > @ref:DIO_strPinConfig_t.
 *@Param :Port Number,Pin Number.
 *@return:Error State.
 */
DIO_enumError_t DIO_enumTogglePin(const DIO_strPinConfig_t *Add_strPinConfig)
{
	DIO_enumError_t DIO_LocEnumRetErr=DIO_enumOk;		/*Initialize the Return Error State by Default Ok*/
	
	/**
	 *@brief: (Validation Statement) Make sure that, the user Not Pass a Null Pointer.
	 */
	if(NULL==Add_strPinConfig)
	{
		DIO_LocEnumRetErr=DIO_enumNullPointer;
	}
	/**
	 *@brief: (Validation Statement) Make sure that, the user does Not Pass a Port Not exist in MCU.
	 */
	else if(((Add_strPinConfig->portNumber)>MAX_PORT_NUM)||((Add_strPinConfig->portNumber)<MIN_PORT_NUM))
	{
		DIO_LocEnumRetErr=DIO_enumWrongPort;
	}
	/**
	 *@brief: (Validation Statement) Make sure that, the user does Not Pass a Pin Not exist in MCU.
	 */
	else if(((Add_strPinConfig->pinNumber)>MAX_PIN_NUM)||((Add_strPinConfig->pinNumber)<MIN_PIN_NUM))
	{
		DIO_LocEnumRetErr=DIO_enumWrongPin;
	}
	/**
	 *@brief: (Validation Statement) Make sure that, the user does Not Pass a Direction Config Not exist.
	 */
	else if(((Add_strPinConfig->pinDirection)==DIO_enumInputInternalPU)||((Add_strPinConfig->pinDirection)==DIO_enumInputExternalPD))
	{
		DIO_LocEnumRetErr=DIO_enumWrongConfig;
	}
	/** 
	 *@brief: Everything is Ok.
	 */
	else
	{
		TOGGLE_BIT(*PORTX_Registers[Add_strPinConfig->portNumber],Add_strPinConfig->pinNumber);
	}
	
	return DIO_LocEnumRetErr;
}
/**
 *@brief  : Function to Read the Logic State of the Pin (Is it HIGH or LOW).
 *@param : Add_strPinConfig, is a pointer points to struct of pin configuration > @ref:DIO_strPinConfig_t.
 *@param  : Port Number,Pin Number, Pointer points to DIO_enumLogicState_t passed by address (to return the value of pin state).
 *@return : Error State                                                                     
 */
DIO_enumError_t DIO_enumReadPinState(const DIO_strPinConfig_t *Add_strPinConfig,volatile DIO_enumLogicState_t* Add_PenumPinValue)
{
	DIO_enumError_t DIO_LocEnumRetErr=DIO_enumOk;		/*Initialize the Return Error State by Default Ok*/
	
	/**
	 *@brief: (Validation Statement) Make sure that, the user Not Pass a Null Pointer.
	 */
	if((NULL==Add_strPinConfig)||(NULL==Add_PenumPinValue))
	{
		DIO_LocEnumRetErr=DIO_enumNullPointer;
	}
	/**
	 *@brief: (Validation Statement) Make sure that, the user does Not Pass a Port Not exist in MCU.
	 */
	else if(((Add_strPinConfig->portNumber)>MAX_PORT_NUM)||((Add_strPinConfig->portNumber)<MIN_PORT_NUM))
	{
		DIO_LocEnumRetErr=DIO_enumWrongPort;
	}
	/**
	 *@brief: (Validation Statement) Make sure that, the user does Not Pass a Pin Not exist in MCU.
	 */
	else if(((Add_strPinConfig->pinNumber)>MAX_PIN_NUM)||((Add_strPinConfig->pinNumber)<MIN_PIN_NUM))
	{
		DIO_LocEnumRetErr=DIO_enumWrongPin;
	}
	/**
	 *@brief: (Validation Statement) Make sure that, the user does Not Pass a Direction Config Not exist.
	 */
	else if(((Add_strPinConfig->pinDirection)==DIO_enumOutputHigh)||((Add_strPinConfig->pinDirection)==DIO_enumOutputLow))
	{
		DIO_LocEnumRetErr=DIO_enumWrongConfig;
	}
	/** 
	 *@brief: Everything is Ok.
	 */
	else
	{
		*Add_PenumPinValue=READ_BIT(*PINX_Registers[Add_strPinConfig->portNumber],Add_strPinConfig->pinNumber);
		
	}
	
	return DIO_LocEnumRetErr;
}

/**
 *@brief  : Function to Toggle the Logic of the whole Port(8 pins) at one time .
 *@param  : Port Number.
 *@return : Error State.                                                                      
 */
DIO_enumError_t DIO_enumTogglePort(DIO_enumPorts_t Copy_enumPortNum)
{
	DIO_enumError_t DIO_LocEnumRetErr=DIO_enumOk;		/*Initialize the Return Error State by Default Ok*/
	
	/**
	 *brief: (Validation Statement) Make sure that, the user does Not Pass a Port Not exist in MCU.
	 */
	if((Copy_enumPortNum>MAX_PORT_NUM)||(Copy_enumPortNum<MIN_PORT_NUM))
	{
		DIO_LocEnumRetErr=DIO_enumWrongPort;
	}
	else
	{
		*PORTX_Registers[Copy_enumPortNum]^=PORT_TOGGLE_MASK;
	}
	
	
	
	return DIO_LocEnumRetErr;
}
