/*
 * TimerCFG.h
 *
 * Created: 2/26/2024 9:46:44 PM
 *  Author: anask
 */ 


#ifndef TIMERCFG_H_
#define TIMERCFG_H_
#include "Timer.h"
/**< It takes the following options:
    - TIMER_8BIT_NORMAL_MODE
    - TIMER_8BIT_PWM_PHASE_MODE	
    - TIMER_8BIT_CTC_MODE			
    - TIMER_8BIT_FAST_PWM_MODE 
**/
#define TIMER0_MODE     TIMER_8BIT_NORMAL_MODE

/**< It takes the following options:
     ** if TIMER0_StrMode = TIMER_8BIT_NORMAL_MODE or TIMER_8BIT_CTC_MODE
        - TIMER_8BIT_CMP_OUT_NON_PWM_MODE_DISCONNECT		
        - TIMER_8BIT_CMP_OUT_NON_PWM_MODE_TOGGLE			
        - TIMER_8BIT_CMP_OUT_NON_PWM_MODE_CLEAR			
        - TIMER_8BIT_CMP_OUT_NON_PWM_MODE_SET	
        ** if TIMER0_StrMode = TIMER_8BIT_PWM_PHASE_MODE	
        - TIMER_8BIT_CMP_OUT_PHASE_CORRECT_PWM_MODE_DISCONNECT			
        - TIMER_8BIT_CMP_OUT_PHASE_CORRECT_PWM_MODE_UP_CLEAR_DOWN_SET		
        - TIMER_8BIT_CMP_OUT_PHASE_CORRECT_PWM_MODE_UP_SET_DOWN_CLEAR
        ** if TIMER0_StrMode =	TIMER_8BIT_FAST_PWM_MODE	
        - TIMER_8BIT_CMP_OUT_FAST_PWM_MODE_DISCONNECT		
        - TIMER_8BIT_CMP_OUT_FAST_PWM_MODE_CLEAR			
        - TIMER_8BIT_CMP_OUT_FAST_PWM_MODE_SET			
        **/
#define CMP_OUT_MODE    TIMER_8BIT_CMP_OUT_NON_PWM_MODE_DISCONNECT

/**< It takes the following options:
        - TIMER_8BIT_NO_CLK_SOURCE				
        - TIMER_8BIT_CLK_NO_PRESCALAR				
        - TIMER_8BIT_CLK_PRESCALAR_8				
        - TIMER_8BIT_CLK_PRESCALAR_64				
        - TIMER_8BIT_CLK_PRESCALAR_256			
        - TIMER_8BIT_CLK_PRESCALAR_1024			
        - TIMER_8BIT_EXTERNAL_CLK_SOURCE_FALLING	
        - TIMER_8BIT_EXTERNAL_CLK_SOURCE_RISING	
    **/
#define TIMER0_CLK_SOURCE    TIMER_8BIT_CLK_PRESCALAR_1024            


#endif /* TIMERCFG_H_ */