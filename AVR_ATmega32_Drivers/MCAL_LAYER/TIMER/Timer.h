/*
 * File Name: Timer.h
 * Layer	: MCAL
 * Module	: TIMER
 * Version  : V 0.0
 * Target	: AVR-Atmega32
 * Created	: 2/26/2024 9:46:22 PM
 * Author	: Anas Khamees
 */ 

#ifndef TIMER_H_
#define TIMER_H_

#include "../MCAL_StdTypes.h"
/*====================================================== Timer0 Registers Configurations ==========================================================*/
/*
 *@brief : Timer/Counter Control Register � TCCR0 responsible for Clock source Select, WaveForm Generation Mode, Compare output Mode and Force Output Compare.
-----------------------------------------------------------------------------
|  FOC0  |  WGM00  |  COM01  |  COM00  |  WGM01  |  CS02  |  CS01  |  CS00  |  
-----------------------------------------------------------------------------
| bit 7  |  bit 6  |  bit 5  |  bit 4  |  bit 3  |  bit 2 |  bit 1 |  bit 0 |
-----------------------------------------------------------------------------
*/
#define CS00		(0)
#define CS01		(1)
#define CS02		(2)
#define WGM01		(3)
#define COM00		(4)
#define COM01		(5)
#define WGM00		(6)
#define FOC0		(7)

#define TOIE0 0
#define OCIE0 1

#define TOV0 0
#define OCF0 1

/*======================================== Masks For Modify Timer0 Registers =======================================================*/

/*
------------------------------------------------------------------
| Mode | WGM01 (CTC0) | WGM00 (PWM0) | Description               |
------------------------------------------------------------------
|   0  |      0       |      0       | Normal                    |
------------------------------------------------------------------
|   1  |      0       |      1       | PWM/Phase Correct         |
------------------------------------------------------------------
|   2  |      1       |      0       | CTC                       |
------------------------------------------------------------------
|   3  |      1       |      1       | Fast PWM                  |
------------------------------------------------------------------
* But these 2 bits in position BIT3 and BIT6, so the following masks represent that 
*/

#define TIMER_8BIT_NORMAL_MODE		(0x00)
#define TIMER_8BIT_PWM_PHASE_MODE	(0x40)
#define TIMER_8BIT_CTC_MODE			(0x08)
#define TIMER_8BIT_FAST_PWM_MODE	(0x48)

/*
 *@brief : Compare Output Mode , Non-PWM mode
-----------------------------------------------------------
| COM01 | COM00 | Description							  |
-----------------------------------------------------------
|   0   |   0   | Normal port operation, OC0 disconnected |
-----------------------------------------------------------
|   0   |   1   | Toggle OC0 on compare match             |
-----------------------------------------------------------
|   1   |   0   | Clear OC0 on compare match              |
-----------------------------------------------------------
|   1   |   1   | Set OC0 on compare match                |
-----------------------------------------------------------
* But these bit in Position BIT4 and BIT5,so the following masks represent that.
*/
#define TIMER_8BIT_CMP_OUT_NON_PWM_MODE_DISCONNECT		(0x00)
#define TIMER_8BIT_CMP_OUT_NON_PWM_MODE_TOGGLE			(0x10)
#define TIMER_8BIT_CMP_OUT_NON_PWM_MODE_CLEAR			(0x20)
#define TIMER_8BIT_CMP_OUT_NON_PWM_MODE_SET				(0x30)
/*
 *@brief : Compare Output Mode , Fast-PWM mode
-----------------------------------------------------------
| COM01 | COM00 | Description							  |
-----------------------------------------------------------
|   0   |   0   | Normal port operation, OC0 disconnected |
-----------------------------------------------------------
|   0   |   1   | Reserved					              |
-----------------------------------------------------------
|   1   |   0   | Clear OC0 on compare match              |
-----------------------------------------------------------
|   1   |   1   | Set OC0 on compare match                |
-----------------------------------------------------------
*/
#define TIMER_8BIT_CMP_OUT_FAST_PWM_MODE_DISCONNECT		(0x00)
#define TIMER_8BIT_CMP_OUT_FAST_PWM_MODE_CLEAR			(0x20)
#define TIMER_8BIT_CMP_OUT_FAST_PWM_MODE_SET			(0x30)
/*
*@brief : Compare Output Mode , Phase Correct-PWM mode
-----------------------------------------------------------------------------------------------------------
| COM01 | COM00 | Description																			   |
-----------------------------------------------------------------------------------------------------------
|   0   |   0   | Normal port operation, OC0 disconnected												   |
-----------------------------------------------------------------------------------------------------------
|   0   |   1   | Reserved																				   |
-----------------------------------------------------------------------------------------------------------
|   1   |   0   |  Clear OC0 on compare match when up-counting. Set OC0 on compare match when down-counting|
-----------------------------------------------------------------------------------------------------------
|   1   |   1   |  Set OC0 on compare match when up-counting. Clear OC0 on compare match when down-counting|																   |
-----------------------------------------------------------------------------------------------------------
*/
#define TIMER_8BIT_CMP_OUT_PHASE_CORRECT_PWM_MODE_DISCONNECT			(0x00)
#define TIMER_8BIT_CMP_OUT_PHASE_CORRECT_PWM_MODE_UP_CLEAR_DOWN_SET		(0x20)
#define TIMER_8BIT_CMP_OUT_PHASE_CORRECT_PWM_MODE_UP_SET_DOWN_CLEAR		(0x30)
/**
 *@brief : Select the clock source to be used by the Timer/Counter.
-------------------------------------------------------------------------------
| CS02 | CS01 | CS00 | Description											   |
-------------------------------------------------------------------------------
|   0  |   0  |   0  | No clock source (Timer/Counter stopped)				   |
-------------------------------------------------------------------------------
|   0  |   0  |   1  | clk    (No prescaling)								   |
-------------------------------------------------------------------------------
|   0  |   1  |   0  | clk/8  (From prescaler)								   |
-------------------------------------------------------------------------------
|   0  |   1  |   1  | clk/64 (From prescaler)								   |
-------------------------------------------------------------------------------
|   1  |   0  |   0  | clk/256 (From prescaler)								   |
-------------------------------------------------------------------------------
|   1  |   0  |   1  | clk/1024 (From prescaler)							   |
-------------------------------------------------------------------------------
|   1  |   1  |   0  | External clock source on T0 pin. Clock on falling edge. |
-------------------------------------------------------------------------------
|   1  |   1  |   1  | External clock source on T0 pin. Clock on rising edge.  |
-------------------------------------------------------------------------------
*/

#define TIMER_8BIT_NO_CLK_SOURCE				(0)
#define TIMER_8BIT_CLK_NO_PRESCALAR				(1)
#define TIMER_8BIT_CLK_PRESCALAR_8				(2)
#define TIMER_8BIT_CLK_PRESCALAR_64				(3)
#define TIMER_8BIT_CLK_PRESCALAR_256			(4)
#define TIMER_8BIT_CLK_PRESCALAR_1024			(5)
#define TIMER_8BIT_EXTERNAL_CLK_SOURCE_FALLING	(6)
#define TIMER_8BIT_EXTERNAL_CLK_SOURCE_RISING	(7)

/*====================== Timer/Counter Interrupt Mask Register � TIMSK ====================================*/
/*
 *@brief : Output Compare Match Interrupt Enable
 */
#define TIMER_8BIT_OUT_CMP_INT_ON				(0) /* The I-bit in SREG must be HIGH */
//#define TIMER_8BIT_OUT_CMP_INT_OFF				(0)
/*
 *@brief :  Overflow Interrupt Enable
 */
#define TIMER_8BIT_OVF_INT_ON					(1) /* The I-bit in SREG must be HIGH */
//#define TIMER_8BIT_OVF_INT_OFF					(0)

/*======================================== Desired Time Delay ===============================================*/

/*============================================= Data Types ==================================================*/

typedef void (*CallBackFun_t)(void);
typedef enum{
	_TICK_TIME_100MS=0,
	_TICK_TIME_500MS,
	_TICK_TIME_1000MS,
	_TICK_TIME_2000MS,
	_TICK_TIME_5000MS
	}DesiredTimeMS_t;

/**
 * @brief Structure to hold configuration parameters for Timer0
 */
// typedef struct  
// {
//     u8 TIMER0_StrMode;          /**< It takes the following options:
// 								    - TIMER_8BIT_NORMAL_MODE
// 									- TIMER_8BIT_PWM_PHASE_MODE	
// 									- TIMER_8BIT_CTC_MODE			
// 									- TIMER_8BIT_FAST_PWM_MODE 
// 								**/
	
//     u8 TIMER0_CompareOutMode;   /**< It takes the following options:
// 								 ** if TIMER0_StrMode = TIMER_8BIT_NORMAL_MODE or TIMER_8BIT_CTC_MODE
// 									- TIMER_8BIT_CMP_OUT_NON_PWM_MODE_DISCONNECT		
// 									- TIMER_8BIT_CMP_OUT_NON_PWM_MODE_TOGGLE			
// 									- TIMER_8BIT_CMP_OUT_NON_PWM_MODE_CLEAR			
// 									- TIMER_8BIT_CMP_OUT_NON_PWM_MODE_SET	
// 								 ** if TIMER0_StrMode = TIMER_8BIT_PWM_PHASE_MODE	
// 									- TIMER_8BIT_CMP_OUT_PHASE_CORRECT_PWM_MODE_DISCONNECT			
// 									- TIMER_8BIT_CMP_OUT_PHASE_CORRECT_PWM_MODE_UP_CLEAR_DOWN_SET		
// 									- TIMER_8BIT_CMP_OUT_PHASE_CORRECT_PWM_MODE_UP_SET_DOWN_CLEAR
// 								 ** if TIMER0_StrMode =	TIMER_8BIT_FAST_PWM_MODE	
// 									- TIMER_8BIT_CMP_OUT_FAST_PWM_MODE_DISCONNECT		
// 									- TIMER_8BIT_CMP_OUT_FAST_PWM_MODE_CLEAR			
// 									- TIMER_8BIT_CMP_OUT_FAST_PWM_MODE_SET			
// 								 **/
	
//     u8 TIMER0_ClockSource;      /**< It takes the following options:
// 									 - TIMER_8BIT_NO_CLK_SOURCE				
// 									 - TIMER_8BIT_CLK_NO_PRESCALAR				
// 									 - TIMER_8BIT_CLK_PRESCALAR_8				
// 									 - TIMER_8BIT_CLK_PRESCALAR_64				
// 									 - TIMER_8BIT_CLK_PRESCALAR_256			
// 									 - TIMER_8BIT_CLK_PRESCALAR_1024			
// 									 - TIMER_8BIT_EXTERNAL_CLK_SOURCE_FALLING	
// 									 - TIMER_8BIT_EXTERNAL_CLK_SOURCE_RISING	
// 								 **/
    
// 	u8 TIMER0_OV_INT_State;     /**< Timer0 overflow interrupt state:
// 									 - TIMER_8BIT_OVF_INT_ON
// 									 - TIMER_8BIT_OVF_INT_OFF
// 								 **/
    
// 	u8 TIMER0_CMP_INT_State;    /**< Timer0 compare match interrupt state :
// 									 - TIMER_8BIT_OUT_CMP_INT_ON
// 									 - TIMER_8BIT_OUT_CMP_INT_OFF
// 								 **/
// } TIMER0_CFG_t;


typedef enum{
	/**
	 *@brief : Everything Ok, Function had Performed Correctly.
	 */
	TIMER_enumOk,
	/**
	  *@brief : Everything NOT Ok, Function had Performed InCorrectly.
	  */
	TIMER_enumNOk,   
	 /**
	  *@brief : Send Null Pointer
	  */   
	 TIMER_enumNullPointer,
	 /**
	  * @brief : user send invalid Time
	 */
	 TIMER_enumWrongTime,
	 /**
	  *@brief : Select Wrong DutyCycle
	  */  
	 TIMER_enumWrongDutyCycle,
	 /**
	  *@brief : Select wrong Timer Mode 
	  */  
	 TIMER_enumWrongMode,
	  /**
	   *@brief : Select wrong PWM Type 
	   */  
	 TIMER_enumWrongPWMType,
	
}TIMER_enumErrorState_t;

/*============================================= Functions API's ==================================================*/

TIMER_enumErrorState_t TIMER0_enumInit(void);
/**
 * @brief Sets the tick time of Timer0 in milliseconds and enables the specified interrupt source.
 * 
 * @param TimeMS The desired tick time in milliseconds :
 *  _TICK_TIME_100MS
 *  _TICK_TIME_500MS
 *	_TICK_TIME_1000MS
 *	_TICK_TIME_2000MS
 *	_TICK_TIME_5000MS
 * 
 * @param InterruptSource The interrupt source to be enabled (TIMER_8BIT_OUT_CMP_INT_ON or TIMER_8BIT_OVF_INT_ON).
 * @return TIMER_enumErrorState_t Returns TIMER_enumOk if setting the tick time is successful, otherwise an error state.
 */
TIMER_enumErrorState_t TIMER0_enumSetTickTimeMS(DesiredTimeMS_t TimeMS,u8 InterruptSource);
/**
 * @brief Starts Timer0 with the specified clock source.
 * 
 * @return TIMER_enumErrorState_t Returns TIMER_enumOk if starting Timer0 is successful, otherwise an error state.
 */
TIMER_enumErrorState_t Timer0_Start(void);
/**
 * @brief Sets the callback function for the specified interrupt source of Timer0.
 * 
 * @param CB_Fun The callback function to be set.
 * @param InterruptSource The interrupt source for which the callback function will be set(TIMER_8BIT_OUT_CMP_INT_ON or TIMER_8BIT_OVF_INT_ON).
 * @return TIMER_enumErrorState_t Returns TIMER_enumOk if setting the callback function is successful, otherwise an error state.
 */
TIMER_enumErrorState_t Timer0_SetCallBack(CallBackFun_t CB_Fun, u8 InterruptSource);

#endif /* TIMER_H_ */