/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "ADC_CFG.h"
#include "ADC_Private.h"
/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
#define ADC_VOLT_REF_CLEAR_MASK             (0xC0)
#define ADC_RESULT_TYPE_CLEAR_MASK          (0x20)
#define ADC_CHANNELS_CLEAR_MASK             (0x1F)
#define ADC_PRESCALER_CLEAR_MASK            (0x07)
#define ADC_CONVERSION_MODE_CLEAR_MASK      (0x20)
#define ADC_AUTO_TRIGGER_SOURCE_CLEAR_MASK  (0xE0)
#define ADC_INTERRUPT_CLEAR_MASK            (0x08)

/*========================= Global Interrupt Bit in SREG ===========================*/
#define GIE_BIT 7

/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/
ADC_Chain_t* GlobalChain=NULL;
u8 volatile ChainCurrentIdx=0;
u8 volatile ChainState=IDLE;
/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/
static void ADC_SelectChannel(u8 Channel)
{
	u8 Loc_ADMUX=ADMUX;
	Loc_ADMUX&=~ADC_CHANNELS_CLEAR_MASK;
	Loc_ADMUX|=Channel;
	ADMUX=Loc_ADMUX;
}

static u16 ADC_GetResult(void)
{
	u16 ADC_Result=0;

	#ifdef ADC_ADJUST_TYPE
	#if (ADC_ADJUST_TYPE==ADC_LEFT_ADJUST_RESULT_ON)
	ADC_Result=((ADCL>>6)||((u16)ADCH<<2));
	#elif (ADC_ADJUST_TYPE==ADC_RIGHT_ADJUST_RESULT_ON)
	ADC_Result= (u16)ADCL||((u16)ADCH<<8);
	#endif
	#endif
	return ADC_Result;
}


/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/

ADC_enumErrorState_t ADC_Init(void)
{
	ADC_enumErrorState_t RetrunError=ADC_OK;
	u8 LocRegister=ADMUX;
	/* Set ADC Voltage Reference*/
	LocRegister&=~ADC_VOLT_REF_CLEAR_MASK;
	LocRegister|=ADC_VOLT_REF;
	/* Set Result Type Left/Right */
	LocRegister&=~ADC_RESULT_TYPE_CLEAR_MASK;
	LocRegister|=ADC_ADJUST_TYPE;
	ADMUX=LocRegister;
	/* Set Prescaler Bits*/
	LocRegister=ADCSRA;
	LocRegister&=~ADC_PRESCALER_CLEAR_MASK;
	LocRegister|=ADC_PRESCALER;
	/* Select ADC Conversion Mode*/
	LocRegister&=~ADC_CONVERSION_MODE_CLEAR_MASK;
	LocRegister|=ADC_CONVERSION_MODE;
	/* Select ADC Interrupt State (Enable or Disable) */
	LocRegister&=~ADC_INTERRUPT_CLEAR_MASK;
	LocRegister|=ADC_INTERRUPT_STATE;
	ADCSRA=LocRegister;
	/* If ADC_INTERRUPT_ENABLE, Enable System Global Interrupt*/
	#ifdef ADC_INTERRUPT_STATE
	#if(ADC_INTERRUPT_STATE==ADC_INTERRUPT_ENABLE)
	SREG|=(1<<GIE_BIT);
	#endif
	#endif
	/*If Auto Trigger Conversion, Select Trigger Source*/
	#ifdef ADC_CONVERSION_MODE
	#if(ADC_CONVERSION_MODE==ADC_AUTO_TRIGGER_ENABLE)
	LocRegister=SFIOR;
	LocRegister&=~ADC_AUTO_TRIGGER_SOURCE_CLEAR_MASK;
	LocRegister|=ADC_AUTO_TRIGGER_SOURCE;
	#endif
	#endif
	/* Enable ADC */
	ADCSRA|=ADC_ENABLE;
}
ADC_enumErrorState_t ADC_StartConversionSync(u8 ADC_Channel,u16* Result)
{
	u32 TimerOut=0;
	ADC_enumErrorState_t ReturnError;
	if(Result==NULL)
	{
		ReturnError=ADC_NullPointer;
	}
	else if(ADC_Channel>ADC_SINGLE_CHANNEL7)
	{
		ReturnError=ADC_NOK;
	}
	else
	{
		ADC_SelectChannel(ADC_Channel);
		/* Enable ADC Interrupt */
		ADCSRA|=(1<<ADIE);
		/* Start Conversion */
		ADCSRA|=ADC_START_CONVERSION;
		while ((!((ADCSRA>>ADIF)&1))&&(TimerOut<100000))
		{
			TimerOut++;
		}
		if(TimerOut==100000)
		{
			/* Time Out*/
			ReturnError=ADC_NOK;
		}
		else
		{
			*Result=ADC_GetResult();
			ReturnError=ADC_OK;
		}
	}
	return ReturnError;
}

ADC_enumErrorState_t ADC_StartConversionAsync(ADC_Chain_t* ADC_Chain)
{
	ADC_enumErrorState_t ReturnError;
	if((ADC_Chain==NULL)||(ADC_Chain->ChainChannels==NULL)||
	(ADC_Chain->ChainResults==NULL)||(ADC_Chain->APP_Notification==NULL))
	{
		ReturnError=ADC_NullPointer;
	}
	else
	{
		if(ChainState==IDLE)
		{
			ChainState=BUSY;
			/* Save the Chain data globally */
			GlobalChain=ADC_Chain;
			/* Select ADC Channel*/
			ADC_SelectChannel(ADC_Chain->ChainChannels[0]);
			/* Enable ADC Interrupt */
			ADCSRA|=(1<<ADIE);
			/* Start Conversion */
			ADCSRA|=ADC_START_CONVERSION;
			ReturnError=ADC_OK;
		}

		else
		{
			/* The ADC Busy NOW */
			ReturnError=ADC_NOK;
		}
	}

	return ReturnError;

}

/* ISR of ADC Conversion Complete*/
void __vector_16 (void) __attribute__((signal,used));
void __Vector_16(void)
{
	//if(ChainState==BUSY)
	/* Get the ADC Conversion Result */
	GlobalChain->ChainResults[ChainCurrentIdx]=ADC_GetResult();
	/* Incremnet the index of Chain*/
	ChainCurrentIdx++;
	if(ChainCurrentIdx==GlobalChain->ChainLength)
	{
		/* Set the ADC State to IDEL*/
		ChainState=IDLE;
		/* Call CallBack Function */
		GlobalChain->APP_Notification();
		/* Reset the ChainCurrent Index to start from Channel 0 again */
		ChainCurrentIdx=0;
		#ifdef ADC_CONVERSION_MODE
		#if ((ADC_CONVERSION_MODE==ADC_AUTO_TRIGGER_ENABLE)&&(ADC_AUTO_TRIGGER_SOURCE==ADC_TRIGGER_SOURCE_FREE_RUNNING))
		ADC_SelectChannel(GlobalChain->ChainChannels[0]);
		#endif
		#endif
	}
	else
	{
		/* Update ADC Channel*/
		ADC_SelectChannel(GlobalChain->ChainChannels[ChainCurrentIdx]);
		#ifdef ADC_CONVERSION_MODE
		#if (ADC_CONVERSION_MODE==ADC_SINGLE_CONVERSION_MODE)
		/* Start Conversion again*/
		ADCSRA|=ADC_START_CONVERSION;
		#elif ((ADC_CONVERSION_MODE==ADC_AUTO_TRIGGER_ENABLE)&&(ADC_AUTO_TRIGGER_SOURCE==ADC_TRIGGER_SOURCE_FREE_RUNNING))
		/* Clear Interrupt Flag which case by the previous Channel */
		ADCSRA|=(1<<ADIF);
		#endif
		#endif
	}
}