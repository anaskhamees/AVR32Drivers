/*
 * ADC.h
 *
 * Created: 3/22/2024 5:25:30 AM
 *  Author: anask
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "../MCAL_StdTypes.h"



/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
/*================= Configurations of  ADC Multiplexer Selection Register – ADMUX =========================
      +---------+-------+-------+-------+------+------+------+------+
Bit:  |     7   |   6   |   5   |   4   |  3   |  2   |  1   |  0   |
      +---------+-------+-------+-------+------+------+------+------+
      |  REFS1  | REFS0 | ADLAR |  MUX4 | MUX3 | MUX2 | MUX1 | MUX0 |
      +---------+-------+-------+-------+------+------+------+------+
*/
/*----------------------------------------- ADC Voltage Reference Masks -----------------------------------*/
#define ADC_VOLT_REF_AREF                   (0x00)
#define ADC_VOLT_REF_AVCC                   (0x40)
#define ADC_VOLT_REF_INTERNAL25600mV        (0xC0)
/*-------------------------- ADC Left/Right Adjust Result Masks ----------------------------*/
#define ADC_LEFT_ADJUST_RESULT_ON           (0x20)
#define ADC_RIGHT_ADJUST_RESULT_ON          (0x00)
/*----------------------------------------- ADC Channels -----------------------------------*/
#define ADC_SINGLE_CHANNEL0                 (0x00)
#define ADC_SINGLE_CHANNEL1                 (0x01)
#define ADC_SINGLE_CHANNEL2                 (0x02)
#define ADC_SINGLE_CHANNEL3                 (0x03)
#define ADC_SINGLE_CHANNEL4                 (0x04)
#define ADC_SINGLE_CHANNEL5                 (0x05)
#define ADC_SINGLE_CHANNEL6                 (0x06)
#define ADC_SINGLE_CHANNEL7                 (0x07)
/*================= Configurations of  ADC Control and Status Register A – ADCSRA =========================
      +-----+-----+-----+-----+-----+------+------+------+
Bit:  | 7   |  6  |   5 |   4 |  3  |  2   |  1   |  0   |
      +-----+-----+-----+-----+-----+------+------+------+
      | ADEN| ADSC|ADATE| ADIF| ADIE| ADPS2| ADPS1| ADPS0|
      +-----+-----+-----+-----+-----+------+------+------+
*/
#define ADC_ENABLE                           (0x80)
#define ADC_DISABLE                          (0x00)
#define ADC_START_CONVERSION                 (0x40)
/**
 * @note :The trigger source is selected by setting the ADC Trigger Select bits, ADTS in SFIOR
*/
#define ADC_AUTO_TRIGGER_ENABLE              (0x20)
#define ADC_SINGLE_CONVERSION_MODE           (0x00)
/**
 * @warning : Don't forget to Set I-bit in SREG is set
*/
#define ADC_INTERRUPT_ENABLE                 (0x08)
#define ADC_INTERRUPT_DISABLE                (0x00)

/*----------------------- ADC Prescaler Select Bits  --------------------*/
#define ADC_PRESCALER_2                       (0x01)
#define ADC_PRESCALER_4                       (0x02)
#define ADC_PRESCALER_8                       (0x03)
#define ADC_PRESCALER_16                      (0x04)
#define ADC_PRESCALER_32                      (0x05)
#define ADC_PRESCALER_64                      (0x06)
#define ADC_PRESCALER_128                     (0x07)

/*=================== Special FunctionIO Register – SFIOR =======================*/
#define ADC_TRIGGER_SOURCE_FREE_RUNNING           (0x00)
#define ADC_TRIGGER_SOURCE_ANALOG_COMPARATOR      (0x20)
#define ADC_TRIGGER_SOURCE_EXTI_REQ0              (0x40)
#define ADC_TRIGGER_SOURCE_TIM0_CMP_MATCH         (0x60)
#define ADC_TRIGGER_SOURCE_TIM0_OVF               (0x80)
#define ADC_TRIGGER_SOURCE_TIM1_CMP_MATCHB        (0xA0)
#define ADC_TRIGGER_SOURCE_TIM1_OVF               (0xC0)
#define ADC_TRIGGER_SOURCE_TIM1_CAPTURE_EVENT     (0xE0)
/*============================== MACROs for Chain State ===========================*/
#define IDLE    0
#define BUSY    1
/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

typedef enum
{
      ADC_OK,
	ADC_NOK,
	ADC_NullPointer
}ADC_enumErrorState_t;

typedef void (*EOJ_t)(void);
typedef struct 
{
    u16 *ChainResults;
    u8  ChainLength;
    u8  *ChainChannels;
    EOJ_t APP_Notification;

}ADC_Chain_t;

/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/

ADC_enumErrorState_t ADC_Init(void);
ADC_enumErrorState_t ADC_StartConversionSync(u8 ADC_Channel,u16* Result);
ADC_enumErrorState_t ADC_StartConversionAsync(ADC_Chain_t* ADC_Chain);



#endif /* ADC_H_ */