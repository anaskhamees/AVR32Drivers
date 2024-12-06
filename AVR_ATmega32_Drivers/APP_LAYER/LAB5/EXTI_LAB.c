/*
 * File Name: EXTI_LAB.c
 * Layer	: MCAL
 * Module	: EXTI
 * Version  : V 0.0
 * Target	: AVR-Atmega32
 * Created	: 1/6/2024 11:16:53 PM
 * Author	: Anas Khamees
 * Brief	: This Source file is the main application.
 */ 
#include "../APP.h"
#ifdef APP
#if (APP==EXTI_LAB)  //Select the Lab Application from APP.h
#include <util/delay.h>
#include "../../MCAL_LAYER/EXTERNAL_INTERRUPT_MODULE/EXTI_Config.h"
#include "../../HAL_LAYER/BUTTON_MODULE/BUTTON_Config.h"
#include "../../HAL_LAYER/LED_MODULE/LED_Config.h"

/**
 * @brief  : External Interrupt 0 Handler
 * @details: This handler is executed when External Interrupt INT0 is triggered. It turns on the LED associated
 *           with INT0 using the LED driver.
 */
void INT0_Handler(void)
{
	LED_enumError_t LED_Loc_RetErr=LED_enumTurnOn(&INT0_Led);
}

/**
 * @brief  : External Interrupt 1 Handler.
 * @details: This handler is executed when External Interrupt INT1 is triggered. It turns on the LED associated
 *           with INT1 using the LED driver.
 */
void INT1_Handler(void)
{
	LED_enumError_t LED_Loc_RetErr=LED_enumTurnOn(&INT1_Led);
}
/**
 * @brief  : External Interrupt 2 Handler
 * @details: This handler is executed when External Interrupt INT2 is triggered. It turns on the LED associated
 *           with INT2 using the LED driver.
 */
void INT2_Handler(void)
{
	LED_enumError_t LED_Loc_RetErr=LED_enumTurnOn(&INT2_Led);
}

int main(void)
{
	/*Initialize LED Module*/
	LED_enumError_t LED_Loc_RetErr=LED_enumInit(&INT0_Led);
	LED_Loc_RetErr=LED_enumInit(&INT1_Led);
	LED_Loc_RetErr=LED_enumInit(&INT2_Led);
	/* Initialize Button Module*/
	BUTTON_enumError_t BUTTON_LocRetErr=BUTTON_enumInit(&INT0_Button);
	BUTTON_LocRetErr=BUTTON_enumInit(&INT1_Button);
	BUTTON_LocRetErr=BUTTON_enumInit(&INT2_Button);
	/* Initialize Interrupt Module*/
	EXTI_voidInit();
	/* Set CallBack Function to ISR*/
	EXTI_voidSetCallBack(INT0_Handler,EXTI0_SOURCE);
	EXTI_voidSetCallBack(INT1_Handler,EXTI1_SOURCE);
	EXTI_voidSetCallBack(INT2_Handler,EXTI2_SOURCE);
	
	while (1)
	{
		
	}
}
#endif // (APP == EXTI_LAB)
#endif // ifdef APP