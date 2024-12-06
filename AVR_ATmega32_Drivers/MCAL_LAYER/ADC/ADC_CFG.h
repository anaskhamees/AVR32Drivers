/*
 * ADC_CFG.h
 *
 * Created: 3/22/2024 5:25:44 AM
 *  Author: anask
 */ 


#ifndef ADC_CFG_H_
#define ADC_CFG_H_

#include "ADC.h"
/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
/**
 * @brief : Select ADC voltage Reference from options :
 * ADC_VOLT_REF_AREF
 * ADC_VOLT_REF_AVCC
 * ADC_VOLT_REF_INTERNAL25600mV
*/
#define ADC_VOLT_REF                ADC_VOLT_REF_AVCC
/**
 * @brief : Select ADC Adjust Type from options :
 * ADC_LEFT_ADJUST_RESULT_ON
 * ADC_RIGHT_ADJUST_RESULT_ON
*/
#define ADC_ADJUST_TYPE             ADC_RIGHT_ADJUST_RESULT_ON 
/**
 * @brief : Select ADC Prescaler Options:
 * ADC_PRESCALER_2
 * ADC_PRESCALER_4
 * ADC_PRESCALER_8
 * ADC_PRESCALER_16
 * ADC_PRESCALER_32
 * ADC_PRESCALER_64
 * ADC_PRESCALER_128
*/
#define ADC_PRESCALER               ADC_PRESCALER_8 
/**
 * @brief : Select ADC Conversion Mode
 * ADC_AUTO_TRIGGER_ENABLE
 * ADC_SINGLE_CONVERSION_MODE
*/
#define ADC_CONVERSION_MODE         ADC_SINGLE_CONVERSION_MODE
/**
 * @brief : ADC Interrupt State
 * ADC_INTERRUPT_ENABLE
 * ADC_INTERRUPT_DISABLE
*/
#define ADC_INTERRUPT_STATE         ADC_INTERRUPT_ENABLE
/**
 * @brief : ADC Auto Trigger Source
 * 
 * ADC_TRIGGER_SOURCE_FREE_RUNNING
 * ADC_TRIGGER_SOURCE_ANALOG_COMPARATOR
 * ADC_TRIGGER_SOURCE_EXTI_REQ0
 * ADC_TRIGGER_SOURCE_TIM0_CMP_MATCH
 * ADC_TRIGGER_SOURCE_TIM0_OVF
 * ADC_TRIGGER_SOURCE_TIM1_CMP_MATCHB
 * ADC_TRIGGER_SOURCE_TIM1_OVF
 * ADC_TRIGGER_SOURCE_TIM1_CAPTURE_EVENT
*/
#define ADC_AUTO_TRIGGER_SOURCE     ADC_TRIGGER_SOURCE_FREE_RUNNING




#endif /* ADC_CFG_H_ */