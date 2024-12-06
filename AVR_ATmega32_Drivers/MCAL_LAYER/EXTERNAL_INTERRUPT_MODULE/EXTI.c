/*
 * File Name: EXTI.c
 * Layer	: MCAL
 * Module	: EXTI
 * Version  : V 0.0
 * Target	: AVR-Atmega32
 * Created	: 1/4/2024 10:15:24 AM
 * Author	: Anas Khamees
 * Brief	: This source file defines the driver functions implementation.
 * Note		: I used Pre-Compiled configuration in this driver to practice different types of design. 
 */ 
#include "EXTI_Config.h"

void (*EXTI0_ISR)(void)=NULL;
void (*EXTI1_ISR)(void)=NULL;
void (*EXTI2_ISR)(void)=NULL;

/*
 *@brief  : Validation Checks for External Interrupts (INT0, INT1, INT2) Configuration.
 *@details: Contains preprocessor checks to ensure valid configuration for
 * sense control settings of External Interrupts (INT0, INT1, INT2),it helps prevent invalid configurations during compile-time.
 */

#if !((EXTI0_CONFIG==EXTI_INT0_LOW_LEVEL)||(EXTI0_CONFIG==EXTI_INT0_LOGICAL_CHANGE)||(EXTI0_CONFIG==EXTI_INT0_FALLING_EDGE)||(EXTI0_CONFIG==EXTI_INT0_RISING_EDGE))
	#error "Invaild INT0 Sense Control Configuration"
#endif
/**
 * @def  :  EXTI1_CONFIG
 * @brief:  Sense control configuration for External Interrupt 1 (INT1).
 *          User-defined configuration macro.
 */
#if !((EXTI1_CONFIG==EXTI_INT1_LOW_LEVEL)||(EXTI1_CONFIG==EXTI_INT1_LOGICAL_CHANGE)||(EXTI1_CONFIG==EXTI_INT1_FALLING_EDGE)||(EXTI1_CONFIG==EXTI_INT1_RISING_EDGE))
	#error "Invaild INT1 Sense Control Configuration"
#endif
/**
 * @def  :  EXTI2_CONFIG
 * @brief:  Sense control configuration for External Interrupt 2 (INT2).
 *          User-defined configuration macro.
 */
#if !((EXTI2_CONFIG==EXTI_INT2_FALLING_EDGE)||(EXTI2_CONFIG==EXTI_INT2_RISING_EDGE))
	#error "Invaild INT2 Sense Control Configuration"
#endif

/**
 * @brief  : Initialize External Interrupts (INT0, INT1, INT2)
 * @details: This function initializes and configures External Interrupts (INT0, INT1, INT2) based on the user-defined
 *           configurations in external_interrupt_config.h file. It includes steps to enable/disable interrupts,
 *           set global interrupt enable, configure sense control, and handle invalid configurations during compile-time.
 */
void EXTI_voidInit(void)
{
	/**********************************************************************************************/
	/*                              INT0 Initialization Steps			                          */
	/**********************************************************************************************/
	
	/* 1 - Is Interrupt 0 Enable ?*/
	#if (EXTI0_STATE==EXTI_ENABLE)
	/* 2- If yes, Set Bit 7 in SREG register to enable Global Interrupt in the system*/
		SET_BIT(SREG,GLOBAL_INT_BIT);
	/* 3- Set INT0 Bit in GICR register (Peripheral Interrupt) to Enable Interrupt 0 */
		SET_BIT(GICR,EXTI_INT0_BIT_POS);
	/* 4- Set The Sense Control Configuration of INT0 based on User Configuration (See in EXTI_Config.h)*/
		u8 EXTI0_u8LocMCUCR=MCUCR;			    /* Read the MCUCR register									   */
		EXTI0_u8LocMCUCR&=EXTI_INT0_CLEAR_MASK; /* Clear associated bits of INT0	   						   */
		EXTI0_u8LocMCUCR|=EXTI0_CONFIG;		    /* Set the associated bits of INT0 based on user configuration */
		MCUCR=EXTI0_u8LocMCUCR;					/* Set the MCUCR register by user configuration value for INT0 */	
	/* 5- If Interrupt 0 is Disabled */
	#elif (EXTI0_STATE==EXTI_DISABLE)       
	/* 6- Clear INT0 Bit in GICR register (Peripheral Interrupt) to Disable Interrupt 0*/
		CLEAR_BIT(GICR,EXTI_INT0_BIT_POS);     
	#else
		#error "Invaild Interrupt State Configuration of INT0";
	#endif
	
	/**********************************************************************************************/
	/*                              INT1 Initialization Steps			                          */
	/**********************************************************************************************/
	
	/* 1 - Is Interrupt 1 Enable ?*/
	#if (EXTI1_STATE==EXTI_ENABLE)
	/* 2- If yes, Set Bit 7 in SREG register to enable Global Interrupt in the system*/
	SET_BIT(SREG,GLOBAL_INT_BIT);
	/* 3- Set INT1 Bit in GICR register (Peripheral Interrupt) to Enable Interrupt 1 */
	SET_BIT(GICR,EXTI_INT1_BIT_POS);
	/* 4- Set The Sense Control Configuration of INT1 based on User Configuration (See in EXTI_Config.h)   */
	u8 EXTI1_u8LocMCUCR=MCUCR;			    /* Read the MCUCR register									   */
	EXTI1_u8LocMCUCR&=EXTI_INT1_CLEAR_MASK; /* Clear associated bits of INT1							   */
	EXTI1_u8LocMCUCR|=(EXTI1_CONFIG<<2);	/* Set the associated bits of INT1 based on user configuration */
	MCUCR=EXTI1_u8LocMCUCR;					/* Set the MCUCR register by user configuration value for INT1 */
	/* 5- If Interrupt 1 is Disabled */
	#elif (EXTI1_STATE==EXTI_DISABLE)
	/* 6- Clear INT1 Bit in GICR register (Peripheral Interrupt) to Disable Interrupt 1*/
	CLEAR_BIT(GICR,EXTI_INT1_BIT_POS);
	#else
		#error "Invaild Interrupt State Configuration of INT1";
	#endif
	
	/**********************************************************************************************/
	/*                              INT2 Initialization Steps			                          */
	/**********************************************************************************************/
	
	/* 1 - Is Interrupt 2 Enable ?*/
	#if (EXTI2_STATE==EXTI_ENABLE)
	/* 2- If yes, Set Bit 7 in SREG register to enable Global Interrupt in the system*/
	SET_BIT(SREG,GLOBAL_INT_BIT);
	/* 3- Set INT2 Bit in GICR register (Peripheral Interrupt) to Enable Interrupt 2 */
	SET_BIT(GICR,EXTI_INT2_BIT_POS);
	/* 4- Set The Sense Control Configuration of INT2 based on User Configuration (See in EXTI_Config.h)*/
	#if (EXTI2_CONFIG==EXTI_INT2_FALLING_EDGE)
		CLEAR_BIT(MCUCSR,EXTI_INT2_ISC_BIT);
	#elif (EXTI2_CONFIG==EXTI_INT2_RISING_EDGE)
		SET_BIT(MCUCSR,EXTI_INT2_ISC_BIT);
	#endif
	/* 5- If Interrupt 2 is Disabled */
	#elif (EXTI2_STATE==EXTI_DISABLE)
	/* 6- Clear INT2 Bit in GICR register (Peripheral Interrupt) to Disable Interrupt 2*/
	CLEAR_BIT(GICR,EXTI_INT2_BIT_POS);
	#else
		#error "Invaild Interrupt State Configuration of INT 2";
	#endif
			
}

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
void EXTI_voidSetCallBack(void(*App_ISR)(void),u8 Copy_u8INTSource)
{
	if(Copy_u8INTSource==EXTI0_SOURCE)
	{		
		EXTI0_ISR=App_ISR;
	}
	else if(Copy_u8INTSource==EXTI1_SOURCE)
	{
		EXTI1_ISR=App_ISR;
	}
	else if(Copy_u8INTSource==EXTI2_SOURCE)
	{
		EXTI2_ISR=App_ISR;
	}
	else
	{
		/* Nothing To Do but For MISRA Standard */
	}
}

/**
 * @brief  : External Interrupt (INT0) Interrupt Service Routine (ISR)
 * @details: This ISR is executed when External Interrupt INT0 is triggered. It checks if a callback function is
 *           assigned for INT0 and executes it if available. Users can set their own callback functions for INT0
 *           using the EXTI_voidSetCallBack function in the Application Layer.
 */
void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	/* Validation Statement - Check if Pointer to function EXTI0_ISR equal NULL or Not*/
	if(EXTI0_ISR)
	{
		EXTI0_ISR();
	}
	else
	{
		/* Nothing to do but for MISRA*/
	}
}

/**
 * @brief  : External Interrupt (INT1) Interrupt Service Routine (ISR)
 * @details: This ISR is executed when External Interrupt INT1 is triggered. It checks if a callback function is
 *           assigned for INT1 and executes it if available. Users can set their own callback functions for INT1
 *           using the EXTI_voidSetCallBack function in the Application Layer.
 */

void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
	/* Validation Statement - Check if Pointer to function EXTI1_ISR equal NULL or Not */
	if(EXTI1_ISR)
	{
		EXTI1_ISR();
	}
	else
	{
		/* Nothing to do but for MISRA*/
	}
}

/**
 * @brief  : External Interrupt (INT2) Interrupt Service Routine (ISR)
 * @details: This ISR is executed when External Interrupt INT2 is triggered. It checks if a callback function is
 *           assigned for INT2 and executes it if available. Users can set their own callback functions for INT2
 *           using the EXTI_voidSetCallBack function in the Application Layer.
 */
void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
	/* Validation Statement - Check if Pointer to function EXTI1_ISR equal NULL or Not */
	if(EXTI2_ISR)
	{
		EXTI2_ISR();
	}
	else
	{
		/* Nothing to do but for MISRA*/
	}
}