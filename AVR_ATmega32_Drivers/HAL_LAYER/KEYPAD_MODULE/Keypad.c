/*
 * File Name: Keypad.c
 * Layer	: HAL
 * Module	: KEYPAD
 * Version  : V 0.0
 * Created	: 1/7/2024 12:34:48 AM
 * Author	: Anas Khamees
 */ 

#include "Keypad.h"

/** 
 * @brief  : 4x4 Calculator Keypad Layout
 * @details: The layout of the 4x4 calculator keypad, where each button corresponds to a character.
 *           The keypad is organized as a matrix with rows and columns.
 */
static const u8 KeyArray[KEYPAD_ROWS_NUMBER][KEYPAD_COLOMNS_NUMBER] =
{
     {'7','8','9','/'},
     {'4','5','6','*'},
     {'1','2','3','-'},
     {'#','0','=','+'}
};

/**
 * @brief :  Initialize the Keypad Pins.
 * @param :  Add_strKeypadConfig, Pointer to the keypad configuration structure.
 * @return:  KEYPAD_enumError_t  Error status indicating the success or failure of the initialization.
 */
KEYPAD_enumError_t KEYPAD_enumInit(KEYPAD_strConfig_t* Add_strKeypadConfig)
{
    KEYPAD_enumError_t KEYPAD_LocRetErr = KEYPAD_enumOk;

    /**
	 *brief: (Validation Statement) Make sure that, the user Not Pass a Null Pointer.
	 */
    if (NULL == Add_strKeypadConfig)
    {
        KEYPAD_LocRetErr = KEYPAD_enumNullPointer;
    }
	/**
	 *brief: (Validation Statement) Everything is Ok, the function parameters is passed correctly.
	 */
    else
    {
        DIO_enumError_t PORT_LocRetErr = DIO_enumOk;
        u8 KPDLocRows = 0;
        u8 KPDLocColomns = 0;

        /* Initialize DIO configurations for pins of keypad rows  */
        for (KPDLocRows = 0; KPDLocRows < KEYPAD_ROWS_NUMBER; KPDLocRows++)
        {
            PORT_LocRetErr = PORT_enumInitConfig(&(Add_strKeypadConfig->KeypadRows[KPDLocRows]));
        }

        /* Initialize DIO configurations for pins of keypad columns */
        for (KPDLocColomns = 0; KPDLocColomns < KEYPAD_COLOMNS_NUMBER; KPDLocColomns++)
        {
            PORT_LocRetErr = PORT_enumInitConfig(&(Add_strKeypadConfig->KeypadColomns[KPDLocColomns]));
        }
    }

    return KEYPAD_LocRetErr;
}

/**
 * @brief	  :	Get the pressed value from the Calculator Keypad.
 * @param[in] : Add_strKeypadConfig Pointer to the keypad configuration structure.
 * @param[out]: Add_u8KeyValue Pointer to store the pressed key value.
 * @return	  : KEYPAD_enumError_t Error status indicating the success or failure of getting the pressed value.
 */
KEYPAD_enumError_t KEYPAD_enumGetPressedValue(KEYPAD_strConfig_t* Add_strKeypadConfig, u8* Add_u8KeyValue)
{
    KEYPAD_enumError_t KEYPAD_LocRetErr = KEYPAD_enumOk;

	/**
	 *brief: (Validation Statement) Make sure that, the user Not Pass a Null Pointer.
	 */    
	if ((NULL == Add_strKeypadConfig) || (NULL == Add_u8KeyValue))
    {
        KEYPAD_LocRetErr = KEYPAD_enumNullPointer;
    }
	/**
	 *brief: (Validation Statement) Everything is Ok, the function parameters is passed correctly.
	 */
    else
    {
        DIO_enumError_t DIO_LocRetErr = DIO_enumOk;
        u8 KPD_LocRowsPin = 0;
        u8 KPD_LocColomnsPin = 0;
        u8 KPD_LocColomnIterator = 0;
		DIO_enumLogicState_t DIO_LocLogicState = DIO_enumLogicHigh;
        /** Steps of check which key in keypad is Pressed:
		 * 1- Set the Pins of Keypad columns OUTPUT-HIGH.
		 * 2- Make only one column OUTPUT-LOW at a time and the rest is still OUTPUT-HIGH.
		 * 3- Set the Pins of Keypad Rows INPUT-PULLUP [Pins: Normally LOGIC-HIGH],[Pressed --> LOGIC-LOW].
		 * 4- Check of Rows Pins became LOGIC-LOW [Pressed] or NOT.
		 * 5- If any Row became LOGIC-LOW --> evidence of Pressed a Key.
		 * 6- Repeat the Steps.
		 */
        for (KPD_LocColomnsPin = 0; KPD_LocColomnsPin < KEYPAD_COLOMNS_NUMBER; KPD_LocColomnsPin++)
        {
            /* Make Sure that all columns are LOGIC-HIGH */
            for (KPD_LocColomnIterator = 0; KPD_LocColomnIterator < KEYPAD_COLOMNS_NUMBER; KPD_LocColomnIterator++)
            {
                DIO_LocRetErr = DIO_enumSetPin(&(Add_strKeypadConfig->KeypadColomns[KPD_LocColomnIterator]), DIO_enumLogicHigh);
            }
            /* Make only one column LOGIC-LOW at a time and the rest still LOGIC-HIGH.*/
            DIO_LocRetErr = DIO_enumSetPin(&(Add_strKeypadConfig->KeypadColomns[KPD_LocColomnsPin]), DIO_enumLogicLow);
            /* Check the rows pins for LOGIC-LOW state to identify the pressed key*/
            for (KPD_LocRowsPin = 0; KPD_LocRowsPin < KEYPAD_ROWS_NUMBER; KPD_LocRowsPin++)
            {
                DIO_LocRetErr = DIO_enumReadPinState(&(Add_strKeypadConfig->KeypadRows[KPD_LocRowsPin]), &DIO_LocLogicState);
                if (DIO_LocLogicState == DIO_enumLogicLow)
                {
					_delay_ms(40);
					DIO_LocRetErr = DIO_enumReadPinState(&(Add_strKeypadConfig->KeypadRows[KPD_LocRowsPin]), &DIO_LocLogicState);
					if (DIO_LocLogicState == DIO_enumLogicLow)
					{
						 /* Store the pressed key value in the provided pointer*/
						 *Add_u8KeyValue = KeyArray[KPD_LocRowsPin][KPD_LocColomnsPin];
					}
                }
				else
				{
					/* Nothing to do but for MISRA*/
				}
            }
        }
    }

    return KEYPAD_LocRetErr;
}