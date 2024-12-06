/*
 * File Name: Timer.c
 * Layer	: MCAL
 * Module	: TIMER
 * Version  : V 0.0
 * Target	: AVR-Atmega32
 * Created	: 2/26/2024 9:46:30 PM
 * Author	: Anas Khamees
 */ 

/*----------------------------------------------- Includes ------------------------------------------------*/
#include "Timer.h"
#include "TimerPrivate.h"
#include "TimerCFG.h"
/*------------------------------------------------ Defines ------------------------------------------------*/
#define TIMER0_MODE_MASK				(0x48)
#define TIMER0_COMPARE_OUTPUT_MASK		(0x30)
#define AVALIABLE_PERIODS				(5)
#define CLK_SOURCE_MASK					(7)

/*------------------------------------------------ Data Types ---------------------------------------------*/

/*------------------------------------------------ Variables ----------------------------------------------*/
/*============= Timer0 [OV mode] Preload Values Based on Calculations of avialable periods ==========================*/
const u8 Timer0_OVPreloadValues[AVALIABLE_PERIODS]={
	[_TICK_TIME_100MS]=243,
	[_TICK_TIME_500MS]=190,
	[_TICK_TIME_1000MS]=124,
	[_TICK_TIME_2000MS]=247,
	[_TICK_TIME_5000MS]=106
	};
	
/*====== Timer0 Overflows Number Based on Calculations of avialable periods and Prescaler 1024 =============*/
const u8 Timer0_OverflowsNumber[AVALIABLE_PERIODS]={
	[_TICK_TIME_100MS]=4,
	[_TICK_TIME_500MS]=16,
	[_TICK_TIME_1000MS]=31,
	[_TICK_TIME_2000MS]=62,
	[_TICK_TIME_5000MS]=153
};
/*========= Timer0 [CTC mode] Preload Values Based on Calculations of avialable periods and Prescaler 1024 ==========*/
const u8 Timer0_CTCPreloadValues[AVALIABLE_PERIODS]={
	[_TICK_TIME_100MS]=195,
	[_TICK_TIME_500MS]=255,
	[_TICK_TIME_1000MS]=255,
	[_TICK_TIME_2000MS]=255,
	[_TICK_TIME_5000MS]=255
	};
	
/*====== Timer0 CMP Match Number Based on Calculations of avialable periods and Prescaler 1024 =============*/
const u8 Timer0_CMPMatchNumber[AVALIABLE_PERIODS]={
	[_TICK_TIME_100MS]=4,
	[_TICK_TIME_500MS]=16,
	[_TICK_TIME_1000MS]=31,
	[_TICK_TIME_2000MS]=62,
	[_TICK_TIME_5000MS]=153
};

CallBackFun_t TIMER0_OverFlowCB=NULL;
CallBackFun_t TIMER0_CMPMatchCB=NULL;
u8 TIMER0_TimeMS;
/*-------------------------------------------- API's Implementation ---------------------------------------*/
/**
 * @brief Initializes Timer0 with the mode and compare output mode.
 * 
 * @return TIMER_enumErrorState_t Returns TIMER_enumOk if initialization is successful, otherwise an error state.
 */
TIMER_enumErrorState_t TIMER0_enumInit(void)
{
    TIMER_enumErrorState_t ReturnError = TIMER_enumOk;

    /* Select Timer0 Mode */
    u8 Loc_TCCR0 = TCCR0;
    Loc_TCCR0 &= ~TIMER0_MODE_MASK;
    Loc_TCCR0 |= TIMER0_MODE;
    TCCR0 = Loc_TCCR0;

    /* Select Timer0 Compare Output Mode */
    Loc_TCCR0 = TCCR0;
    Loc_TCCR0 &= ~TIMER0_COMPARE_OUTPUT_MASK;
    Loc_TCCR0 |= CMP_OUT_MODE;
    TCCR0 = Loc_TCCR0;

    /* Enable Global Interrupt */
    SREG |= (1 << 7);

    return ReturnError;
}

/**
 * @brief Sets the tick time of Timer0 in milliseconds and enables the specified interrupt source.
 * 
 * @param TimeMS The desired tick time in milliseconds.
 * @param InterruptSource The interrupt source to be enabled (TIMER_8BIT_OUT_CMP_INT_ON or TIMER_8BIT_OVF_INT_ON).
 * @return TIMER_enumErrorState_t Returns TIMER_enumOk if setting the tick time is successful, otherwise an error state.
 */
TIMER_enumErrorState_t TIMER0_enumSetTickTimeMS(DesiredTimeMS_t TimeMS, u8 InterruptSource)
{
    TIMER_enumErrorState_t ReturnError;

    if (TimeMS > AVALIABLE_PERIODS)
    {
        ReturnError = TIMER_enumWrongTime;
    }
    else if (InterruptSource > TIMER_8BIT_OVF_INT_ON)
    {
        ReturnError = TIMER_enumNOk;
    }
    else
    {
        TIMER0_TimeMS = TimeMS;
        switch (InterruptSource)
        {
        case TIMER_8BIT_OUT_CMP_INT_ON:
            /* Assign PreloadValue in Output compare match register in case of the fractions of desired Time */
            OCR0 = Timer0_CTCPreloadValues[TimeMS];
            /* Enable the Output compare match interrupt */
            TIMSK |= (1 << OCIE0);
            break;
        case TIMER_8BIT_OVF_INT_ON:
            TCNT0 = Timer0_OVPreloadValues[TimeMS];
            /* Enable the overflow interrupt */
            TIMSK |= (1 << TOIE0);
            break;
        default:
            ReturnError = TIMER_enumNOk;
            break;
        }
        ReturnError = TIMER_enumOk;
    }
    return ReturnError;
}

/**
 * @brief Starts Timer0 with the specified clock source.
 * 
 * @return TIMER_enumErrorState_t Returns TIMER_enumOk if starting Timer0 is successful, otherwise an error state.
 */
TIMER_enumErrorState_t Timer0_Start(void)
{
    TIMER_enumErrorState_t ReturnError = TIMER_enumOk;
    u8 Loc_TCCR0 = TCCR0;
    Loc_TCCR0 &= ~CLK_SOURCE_MASK;
    Loc_TCCR0 |= TIMER0_CLK_SOURCE;
    TCCR0 = Loc_TCCR0;
    return ReturnError;
}

/**
 * @brief Sets the callback function for the specified interrupt source of Timer0.
 * 
 * @param CB_Fun The callback function to be set.
 * @param InterruptSource The interrupt source for which the callback function will be set.
 * @return TIMER_enumErrorState_t Returns TIMER_enumOk if setting the callback function is successful, otherwise an error state.
 */
TIMER_enumErrorState_t Timer0_SetCallBack(CallBackFun_t CB_Fun, u8 InterruptSource)
{
    TIMER_enumErrorState_t ReturnError;

    if (CB_Fun == NULL)
    {
        ReturnError = TIMER_enumNullPointer;
    }
    else if (InterruptSource > TIMER_8BIT_OVF_INT_ON)
    {
        ReturnError = TIMER_enumNOk;
    }
    else
    {
        switch (InterruptSource)
        {
        case TIMER_8BIT_OUT_CMP_INT_ON:
            TIMER0_CMPMatchCB = CB_Fun;
            break;
        case TIMER_8BIT_OVF_INT_ON:
            TIMER0_OverFlowCB = CB_Fun;
            break;
        default:
            ReturnError = TIMER_enumNOk;
            break;
        }
        ReturnError = TIMER_enumOk;
    }
    return ReturnError;
}

/* ISR of OverFlow*/
void __vector_11(void) __attribute__((signal,used));
void __vector_11(void)
{
	static u8 Counter=0;
	Counter++;
	if(TIMER0_OverFlowCB&&(Counter==Timer0_OverflowsNumber[TIMER0_TimeMS]))
	{
			TCNT0=Timer0_OVPreloadValues[TIMER0_TimeMS];
			Counter=0;
     		TIMER0_OverFlowCB();
	}
}

void __vector_10(void) __attribute__((signal,used));
void __vector_10(void)
{
	static u8 Counter=0;
	Counter++;
	if(TIMER0_CMPMatchCB&&(Counter==Timer0_CMPMatchNumber[TIMER0_TimeMS]))
	{
			OCR0=Timer0_CTCPreloadValues[TIMER0_TimeMS];
			Counter=0;
     		TIMER0_CMPMatchCB();
	}
}
