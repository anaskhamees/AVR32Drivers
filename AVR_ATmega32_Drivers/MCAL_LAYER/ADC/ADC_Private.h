/*
 * ADC_Private.h
 *
 * Created: 3/22/2024 6:17:39 PM
 *  Author: anask
 */ 


#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_



#define ADMUX       *((volatile u8*)0x27)
#define ADCSRA      *((volatile u8*)0x26)
#define ADCH        *((volatile u8*)0x25)
#define ADCL        *((volatile u8*)0x24)
#define SFIOR       *((volatile u8*)0x50)
#define SREG        *((volatile u8*)0x5F)

#define ADATE						(5)
#define ADIF						(4)

#define ADEN						(7)
#define ADIE						(3)
#define ADLAR						(5)
#define ADSC						(6)


#endif /* ADC_PRIVATE_H_ */