/*
 * File Name: LCD.c
 * Layer	: HAL
 * Module	: LCD
 * Version  : V 0.0
 * Created	: 12/31/2023 9:49:35 PM
 * Author	: Anas Khamees
 * Brief	: This source file defines the API implementation for LCD driver.
 */ 
#include "LCD.h"
#include "util/delay.h"

/************************* LCD 8-Bit Mode ********************************/
/*____________                 ____________
 | ATmega32  |                 |   LCD    |
 |           |                 |          |
 |        Px7|---------------->|DB7       |
 |        Px6|---------------->|DB6       |
 |        Px5|---------------->|DB5       |
 |        Px4|---------------->|DB4       |
 |        Px3|---------------->|DB3       |
 |        Px2|---------------->|DB2       |
 |        Px1|---------------->|DB1       |
 |        Px0|---------------->|DB0       |
 |           |                 |          |
 |        Px2|---------------->|E         |
 |        Px1|---------------->|RW        |
 |        Px0|---------------->|RS        |
 ------------                  ------------*/
/************************* LCD 4-Bit Mode ********************************/
/*____________                 ____________
 | ATmega32  |                 |   LCD    |
 |           |                 |          |
 |        Px7|---------------->|DB7       |
 |        Px6|---------------->|DB6       |
 |        Px5|---------------->|DB5       |
 |        Px4|---------------->|DB4       |
 |           |xxxxxxxxxxxxxxxxx|DB3       |
 |           |xxxxxxxxxxxxxxxxx|DB2       |
 |           |xxxxxxxxxxxxxxxxx|DB1       |
 |           |xxxxxxxxxxxxxxxxx|DB0       |
 |           |                 |          |
 |        Px3|---------------->|E         |
 |        Px2|---------------->|RW        |
 |        Px1|---------------->|RS        |
 ------------                  ------------*/
/*----------------------------------------- LCD Helper Function Prototypes---------------------------------------------------------*/
static LCD_enumError_t LCD_enumHelperSend4BitMode(const LCD_strConfig *Add_strLCDconfig,u8 DataORcommand);
static LCD_enumError_t LCD_enumHelperSend8BitMode(const LCD_strConfig *Add_strLCDconfig,u8 DataORcommand);
static LCD_enumError_t LCD_enumHelperSendEnableSignal(const LCD_strConfig *Add_strLCDconfig);
static LCD_enumError_t LCD_enumHelperSetCursorPosition(const LCD_strConfig *Add_strLCDconfig,u8 Copy_u8Row,u8 Copy_u8Colomn);
/*----------------------------- The documentation of the function below at the definition section ---------------------------------*/

/* @brief	 : Initializes the LCD module based on the provided configuration.
 * @param[in]: Add_strLCDconfig Pointer to the LCD configuration structure.
 * @return	 : LCD_enumError_t Error status indicating the success or failure of the initialization.
 * @details	 : This function initializes the LCD module based on the configuration provided in the @ref LCD_strConfig structure.
 * It configures the control pins (RegisterSelect and EnableSignal) and the data pins according to the selected LCD mode (4-bit or 8-bit).
 * The initialization process follows the steps recommended in the LMB161A LCD datasheet.
 * @note	 : The function returns an error if a NULL pointer is provided as the configuration structure.
 */
LCD_enumError_t	LCD_enumInit(const LCD_strConfig *Add_strLCDconfig)
{
	LCD_enumError_t Loc_LCDRetErr=LCD_enumOk;
	/* Validation Statement - Ensure that the user does not pass a NULL pointer.*/
	if(Add_strLCDconfig==NULL)
	{
		Loc_LCDRetErr=LCD_enumNullPointer;
	}
	/* Everything is Ok, the function parameters is passed correctly.			*/
	else
	{
		DIO_enumError_t PORT_LocRetErr=DIO_enumOk;
		DIO_enumError_t DIO_LocRetErr=DIO_enumOk;
	   /*Initialize control pins (RegisterSelect and EnableSignal) make them by default Output LOW*/
		PORT_LocRetErr=PORT_enumInitConfig(&(Add_strLCDconfig->RegisterSelect));
		PORT_LocRetErr=PORT_enumInitConfig(&(Add_strLCDconfig->EnableSignal));
	   /*Initialize data(or command) pins based on the selected LCD mode (4-bit or 8-bit)*/
	   
	/* If the user Select LCD 4-Bit Mode in LCD_Config.c file */
	#if (SELECT_LCD_MODE==FOUR_BIT_MODE)
		/*Initialize data(or command) pins in LCD 4-bit mode*/   
		for(u8 LCD_dataPin=0;LCD_dataPin<4;LCD_dataPin++)
		{
			PORT_LocRetErr=PORT_enumInitConfig(&(Add_strLCDconfig->LCD_Data[LCD_dataPin]));
		}
		
		/*Follow the Initialization steps of 4-bit mode based on LMB161A LCD datasheet (page 14)*/
		
		/* 1- Power on the LCD and wait for more than 30 ms after VDD rises to 4.5V */
		_delay_ms(50);
		/* 2- Clear Register Select Pin in LCD to send Command						*/
		DIO_LocRetErr=DIO_enumSetPin(&(Add_strLCDconfig->RegisterSelect),DIO_enumLogicLow); 
		/* 3- R/W pin connected to ground in hardware, So it is always LOW.			*/
		/* 4- Send Function Set Command for 4-bit mode								*/
	    Loc_LCDRetErr=LCD_enumSendCommand(Add_strLCDconfig,0X02); // 0x02 to follow the data sheet instructions (page14).
		Loc_LCDRetErr=LCD_enumSendCommand(Add_strLCDconfig,LCD_4BIT_MODE);
		/* 5- Wait for more than 39 us*/
		_delay_ms(1);
		/* 6- Send Display ON/OFF Control Command									*/
		Loc_LCDRetErr=LCD_enumSendCommand(Add_strLCDconfig,LCD_DISPLAY_CURSOR_BLINK_ALL_ON);
		/* 7- Wait for more than 39 us*/
		_delay_ms(1);
		/* 8- Send Display Clear Command											*/
		Loc_LCDRetErr=LCD_enumSendCommand(Add_strLCDconfig,LCD_CLEAR_DISPLAY);
		/* 9- Wait for more than 1.53 ms*/
		_delay_ms(2);
		/* 10- Send Entry mode Set Command											*/
		Loc_LCDRetErr=LCD_enumSendCommand(Add_strLCDconfig,LCD_ENTRY_MODE_INC_SHIFT_OFF);
		/* End of LCD 4-bit mode initialization.									*/
		
	/* If the user Select LCD 8-Bit Mode in LCD_Config.c file */
	#elif (SELECT_LCD_MODE==EIGHT_BIT_MODE)
		/*Initialize data(or command) pins in LCD 8-bit mode*/
		for(u8 LCD_dataPin=0;LCD_dataPin<8;LCD_dataPin++)
		{
			PORT_LocRetErr=PORT_enumInitConfig(&(Add_strLCDconfig->LCD_Data[LCD_dataPin]));
		}
		
	/* Follow the Initialization steps of 8-bit mode based on LMB161A LCD datasheet (page 13)*/
		
		/* 1- Power on the LCD and wait for more than 30 ms after VDD rises to 4.5V */
		_delay_ms(50);
		/* 2- Clear Register Select Pin in LCD to send Command						*/
		DIO_LocRetErr=DIO_enumSetPin(&(Add_strLCDconfig->RegisterSelect),DIO_enumLogicLow); 
		/* 3- R/W pin connected to ground in hardware, So it is always LOW.			*/
		/* 4- Send Function Set Command for 8-bit mode								*/
		Loc_LCDRetErr=LCD_enumSendCommand(Add_strLCDconfig,LCD_8BIT_MODE);
		/* 5- Wait for more than 39 us												*/
		_delay_us(50);
	    /* 6- Send Display ON/OFF Control Command									*/
		Loc_LCDRetErr=LCD_enumSendCommand(Add_strLCDconfig,LCD_DISPLAY_CURSOR_BLINK_ALL_ON);
		/* 7- Wait for more than 39 us												*/
		_delay_us(50);
		/* 8- Send Display Clear Command                                            */
		Loc_LCDRetErr=LCD_enumSendCommand(Add_strLCDconfig,LCD_CLEAR_DISPLAY);
		/* 9- Wait for more than 1.53 ms											*/
		_delay_ms(2);
		/* 10- Send Entry mode Set Command											*/
		Loc_LCDRetErr=LCD_enumSendCommand(Add_strLCDconfig,LCD_ENTRY_MODE_INC_SHIFT_OFF);
		/* End of LCD 4-bit mode initialization										*/
	#endif
	}
	return Loc_LCDRetErr;
}

/**
 * @brief	 : Sends a command to the LCD module.
 * @param[in]: Add_strLCDconfig Pointer to the LCD configuration structure.
 * @param[in]: Copy_u8LCDcommand, The command to be sent to the LCD.
 * @return	 : LCD_enumError_t Error status indicating the success or failure of the command transmission.
 * @details  : This function sends a command to the LCD module using the provided configuration structure.
 * It checks for a NULL pointer and then uses Helper functions to send the command based on the selected LCD mode (4-bit or 8-bit).
 * @note	 : The function returns an error if a NULL pointer is provided as the configuration structure.
 */
LCD_enumError_t LCD_enumSendCommand(const LCD_strConfig *Add_strLCDconfig, u8 Copy_u8LCDcommand)
{
    LCD_enumError_t Loc_LCDRetErr = LCD_enumOk;

	/* Validation Statement - Ensure that the user does not pass a NULL pointer.*/
    if (Add_strLCDconfig == NULL)
    {
        Loc_LCDRetErr = LCD_enumNullPointer;
    }
	/* Everything is Ok, the function parameters is passed correctly.			*/
    else
    {
        DIO_enumError_t Loc_DIO_RetErr = DIO_enumOk;
		/* Clear Register Select Pin in LCD to send Command						*/
		Loc_DIO_RetErr=DIO_enumSetPin(&(Add_strLCDconfig->RegisterSelect),DIO_enumLogicLow);

#if (SELECT_LCD_MODE == FOUR_BIT_MODE)
	/* Steps of Send Commands to LCD in 4-Bit Mode	  */
        /* 1- Send upper 4 bits of the command in 4-bit mode */
        Loc_LCDRetErr = LCD_enumHelperSend4BitMode(Add_strLCDconfig, Copy_u8LCDcommand >> 4);
        /* 2- Send Enable signal							 */
        Loc_LCDRetErr = LCD_enumHelperSendEnableSignal(Add_strLCDconfig);
        /* 3- Send lower 4 bits of the command in 4-bit mode */
        Loc_LCDRetErr = LCD_enumHelperSend4BitMode(Add_strLCDconfig, Copy_u8LCDcommand);
        /* 4- Send Enable signal       						 */
        Loc_LCDRetErr = LCD_enumHelperSendEnableSignal(Add_strLCDconfig);
		/* End of Sending Command*/
#elif (SELECT_LCD_MODE == EIGHT_BIT_MODE)
	/* Steps of Send Commands to LCD in 8-Bit Mode	  */
        /* 1- Send the command in 8-bit mode		  */
        Loc_LCDRetErr = LCD_enumHelperSend8BitMode(Add_strLCDconfig, Copy_u8LCDcommand);
        /* 2- Send Enable signal					  */
        Loc_LCDRetErr = LCD_enumHelperSendEnableSignal(Add_strLCDconfig);
#endif
    }

    return Loc_LCDRetErr;
}

/**
 * @brief	 : Sends a character to be displayed on the LCD.
 * @param[in]: Add_strLCDconfig Pointer to the LCD configuration structure.
 * @param[in]: Copy_u8LCDdata The character to be sent to the LCD.
 * @return	 : LCD_enumError_t Error status indicating the success or failure of the data transmission.
 * @details  : This function sends a character to the LCD module using the provided configuration structure.
 * It checks for a NULL pointer, sets the Register Select pin to high to indicate data transmission,
 * and uses Helper functions to send the character based on the selected LCD mode (4-bit or 8-bit).
 * @note	 : The function returns an error if a NULL pointer is provided as the configuration structure.
 */
LCD_enumError_t LCD_enumSendChar(const LCD_strConfig *Add_strLCDconfig, u8 Copy_u8LCDdata)
{
	LCD_enumError_t Loc_LCDRetErr = LCD_enumOk;

	/* Validation Statement - Ensure that the user does not pass a NULL pointer.*/
	if (Add_strLCDconfig == NULL)
	{
		Loc_LCDRetErr = LCD_enumNullPointer;
	}
	/* Everything is Ok, the function parameters is passed correctly.			*/
	else
	{
		DIO_enumError_t Loc_DIO_RetErr = DIO_enumOk;
		/* Set Register Select  Pin in LCD to send Data    */
		Loc_DIO_RetErr=DIO_enumSetPin(&(Add_strLCDconfig->RegisterSelect),DIO_enumLogicHigh);
		#if (SELECT_LCD_MODE == FOUR_BIT_MODE)
		/* Steps of Send Data to LCD in 4-Bit Mode	      */
		/* 1- Send upper 4 bits of the Data in 4-bit mode */
		Loc_LCDRetErr = LCD_enumHelperSend4BitMode(Add_strLCDconfig, Copy_u8LCDdata >> 4);
		/* 2- Send Enable signal						  */
		Loc_LCDRetErr = LCD_enumHelperSendEnableSignal(Add_strLCDconfig);
		/* 3- Send lower 4 bits of the Data in 4-bit mode */
		Loc_LCDRetErr = LCD_enumHelperSend4BitMode(Add_strLCDconfig, Copy_u8LCDdata);
		/* 4- Send Enable signal       				   	  */
		Loc_LCDRetErr = LCD_enumHelperSendEnableSignal(Add_strLCDconfig);
		/* End of Sending Data in 4-Bit mode			  */
		#elif (SELECT_LCD_MODE == EIGHT_BIT_MODE)
		/* Steps of Send Data to LCD in 8-Bit Mode	      */
		/* 1- Send the Data in 8-bit mode				  */
		Loc_LCDRetErr = LCD_enumHelperSend8BitMode(Add_strLCDconfig, Copy_u8LCDdata);
		/* 2- Send Enable signal			     		  */
		Loc_LCDRetErr = LCD_enumHelperSendEnableSignal(Add_strLCDconfig);
		/* End of Sending Data in 8-Bit mode			  */
		#endif
	}

	return Loc_LCDRetErr;
}

/**
 * @brief	 : Sends a character to be displayed at a specified position on the LCD.
 * @param[in]: Add_strLCDconfig Pointer to the LCD configuration structure.
 * @param[in]: Copy_u8Row, The row position on the LCD (1 to 2), the user has to select Only two defined Macro(LCD_ROW1 or LCD_ROW2).
 * @param[in]: Copy_u8Colomn, The column position on the LCD (0 to 15) (16 position).
 * @param[in]: Copy_u8LCDdata, The character to be sent to the LCD to display it.
 * @return	 : LCD_enumError_t Error status indicating the success or failure of the data transmission.
 * @details	 : This function sends a character to the specified position on the LCD module using the provided
 * configuration structure. It checks for a NULL pointer, sets the cursor position using a helper function,
 * and sends the character using LCD_enumSendChar function.
 * @note	 : The function returns an error if a NULL pointer is pass as a parameter.
 */
LCD_enumError_t LCD_enumSendCharPosition(const LCD_strConfig *Add_strLCDconfig,u8 Copy_u8Row,u8 Copy_u8Colomn, u8 Copy_u8LCDdata)
{
	LCD_enumError_t Loc_LCDRetErr = LCD_enumOk;

	/* Validation Statement - Ensure that the user does not pass a NULL pointer.*/
	if (Add_strLCDconfig == NULL)
	{
		Loc_LCDRetErr = LCD_enumNullPointer;
	}
	/* Everything is Ok, the function parameters is passed correctly.			*/
	else
	{
		/* Set the Cursor of LCD at specific position (Set the Address counter to specific location at DDRAM)*/
		Loc_LCDRetErr=LCD_enumHelperSetCursorPosition(Add_strLCDconfig,Copy_u8Row,Copy_u8Colomn);
		/* Send the character to the specified position to display it on the LCD*/
		Loc_LCDRetErr=LCD_enumSendChar(Add_strLCDconfig,Copy_u8LCDdata);
	}

	return Loc_LCDRetErr;
}

/**
 * @brief	 : Sends a string of characters (e.g., names) to be displayed on the LCD.
 * @param[in]: Add_strLCDconfig, Pointer to the LCD configuration structure.
 * @param[in]: Add_u8LCDstring, Pointer to the null-terminated string (e.g., names) to be sent to the LCD.
 * @return	 : LCD_enumError_t Error status indicating the success or failure of the data transmission.
 * @details	 : This function sends a string of characters (e.g., names) to the LCD module using the provided
 * configuration structure. It checks for NULL pointers and iterates through the string, sending
 * each character to the LCD using the helper function LCD_enumSendChar. The string is expected to be
 * null-terminated, and the function continues to send characters until the null terminator is encountered.
 * @note	 : The function returns an error if a NULL pointer is provided as the configuration structure
 * or if the string pointer is NULL.
 */
LCD_enumError_t LCD_enumSendString(const LCD_strConfig *Add_strLCDconfig, u8* Add_u8LCDstring)
{
	LCD_enumError_t Loc_LCDRetErr = LCD_enumOk;

	/* Validation Statement - Ensure that the user does not pass a NULL pointer.*/
	if ((Add_strLCDconfig == NULL) ||(NULL==Add_u8LCDstring))
	{
		Loc_LCDRetErr = LCD_enumNullPointer;
	}
	/* Everything is Ok, the function parameters is passed correctly.			*/
	else
	{
		/* Send the characters of string until reach to Null terminator */
		while(*Add_u8LCDstring)
		{
			Loc_LCDRetErr=LCD_enumSendChar(Add_strLCDconfig,*Add_u8LCDstring++);
		}
	}
	
	return Loc_LCDRetErr;
}

/**
 * @brief	 : Sends a string of characters to be displayed on the LCD at a specified position.
 * @param[in]: Add_strLCDconfig, Pointer to the LCD configuration structure.
 * @param[in]: Copy_u8Row, Row position where the string should be displayed, the user has to select Only two defined Macro(LCD_ROW1 or LCD_ROW2).
 * @param[in]: Copy_u8Colomn Column position where the string should start (0 ~ 15) 16 locations.
 * @param[in]: Add_u8LCDstring, Pointer to the null-terminated string to be sent to the LCD.
 * @return	 : LCD_enumError_t Error status indicating the success or failure of the data transmission.
 * @details	 : This function sends a string of characters to the LCD module using the provided configuration
 * structure. It also specifies the position (row and column) where the string should be displayed on the LCD.
 * The function checks for NULL pointers and sets the cursor position before sending each character to the LCD
 * using the helper function LCD_enumSendChar. The string is expected to be null-terminated, and the function
 * continues to send characters until the null terminator is encountered.
 * @note	: The function returns an error if a NULL pointer is provided as the configuration structure or if the string pointer is NULL.
 */

LCD_enumError_t LCD_enumSendStringPosition(const LCD_strConfig *Add_strLCDconfig,u8 Copy_u8Row,u8 Copy_u8Colomn, u8* Add_u8LCDstring)
{
	LCD_enumError_t Loc_LCDRetErr = LCD_enumOk;

	/* Validation Statement - Ensure that the user does not pass a NULL pointer.*/
	if ((Add_strLCDconfig == NULL) ||(NULL==Add_u8LCDstring))
	{
		Loc_LCDRetErr = LCD_enumNullPointer;
	}
	/* Everything is Ok, the function parameters is passed correctly.			*/
	else
	{
		/* Set the Cursor of LCD at specific position (Set the Address counter to specific location at DDRAM)*/
		Loc_LCDRetErr=LCD_enumHelperSetCursorPosition(Add_strLCDconfig,Copy_u8Row,Copy_u8Colomn);
		/* Send the characters of string  to the specified position to display it on the LCD
		 * Looping until to reach to the Null terminator of the string.
		 */
		while(*Add_u8LCDstring)
		{
			Loc_LCDRetErr=LCD_enumSendChar(Add_strLCDconfig,*Add_u8LCDstring++);
		}
	}
	
	return Loc_LCDRetErr;
}
/**
 * @brief    : Displays a special character on the LCD at the specified row and column.
 *
 * @param[in]:  Add_strLCDconfig		--> Pointer to the LCD configuration structure @ref: LCD_strConfig.
 * @param[in]:  Copy_u8Row				--> Row position on LCD where the special character will be displayed .
 * @param[in]:  Copy_u8Colomn			--> Column position on LCD where the special character will be displayed.
 * @param[in]:  Add_u8CharArrPattern	--> Pointer to an array containing the custom character pattern.
 * @param[in]:  Copy_u8CGRAM_Location   --> The Location in CGRAM where the custom character will be stored (0 to 7).
 * There are 8 Locations for 8 Special Characters.
 * @return   :  LCD_enumError_t       Error status indicating the success or failure of the operation.
 *
 * @details  :  This function allows the user to display a custom character on the LCD. It writes the
 *             custom character pattern to the specified location in CGRAM and then displays it at the
 *             specified position on the LCD. The custom character is defined by an array of 8 bytes,
 *             where each byte represents a row of the 5x8 dot matrix.
 *
 *             The character code corresponding to the CGRAM location is used to display the custom character.
 *             This function is useful for displaying symbols or characters not present in the standard character set ASCII.
 *
 * @note     :  The CGRAM has 8 memory locations, each storing an 5x8 dot matrix character. The character code
 *             is used to reference the desired CGRAM location when displaying the character on the LCD.
 */



LCD_enumError_t LCD_enumSendSpecialChar(const LCD_strConfig *Add_strLCDconfig, u8 Copy_u8Row,u8 Copy_u8Colomn,u8* Add_u8CharArrPattern,u8 Copy_u8CGRAM_Location)
{
	LCD_enumError_t Loc_LCDRetErr = LCD_enumOk;

	/* Validation Statement - Ensure that the user does not pass a NULL pointer.*/
	if (Add_strLCDconfig == NULL)
	{
		Loc_LCDRetErr = LCD_enumNullPointer;
	}
	/* Everything is Ok, the function parameters is passed correctly.			*/
	else
	{
		/*
		 *@brief: There are 8 memory locations in CGRAM, each location is 8 byte (5x8 dots).
		 * Make The AC points to CGRAM
		 */
		
		/* Steps of Display Special character does not exist in CGROM */
		
		/* 1- Set Address Counter to CGRAM  */ 
		Loc_LCDRetErr=LCD_enumSendCommand(Add_strLCDconfig,(LCD_CGRAM_START_ADDRESS+(8*Copy_u8CGRAM_Location)));
		/*
		 *@brief: write the data on CGRAM and it will transfer to DDRAM Automatically.
		 * Each Location has 5x8 dot matrix, So there are 8 rows for each location (remember that the eighth row reserved for cursor).
		 * Address counter increments to the next position automatically (I/D bit must be HIGH)
		 */
		
		/* 2- Store the Special character in CGRAM*/
		for(u8 LOC_u8Location_Row=0;LOC_u8Location_Row<8;LOC_u8Location_Row++)
		{
			/* Write 8 byte for 1 character */
			Loc_LCDRetErr=LCD_enumSendChar(Add_strLCDconfig,Add_u8CharArrPattern[LOC_u8Location_Row]);
		}
		/* 3-  Get the data from CGRAM by its Location address and Return the Address counter to DDRAM */
		
		/**
		  *@note: Any  Send_Data_Function such as: 
		  * LCD_enumSendCharPosition(lcd,row,colomn,data) or LCD_enumSendChar(lcd, data):
		  * If     (data ='0') : character data is passed. So, the number Zero will display on the LCD.
		  * If     (data ='2') : character data is passed. So, the number Two will display on the LCD.
		  * But if (data = 0 ) : Not character data. So, The Stored character in Location 0 in CGRAM will display on LCD. 
		  * IF     (data = 2 ) : The Stored character in Location 2 in CGRAM will display on LCD.
		  * Copy_u8CGRAM_Location has 8 probabilities from location 0 to location 7 (000 to 111) to cover the 8 possible characters. 
		  */
		Loc_LCDRetErr=LCD_enumSendCharPosition(Add_strLCDconfig,Copy_u8Row,Copy_u8Colomn,Copy_u8CGRAM_Location);
	}
	
	return Loc_LCDRetErr;
}


/*-------------------------------------------- LCD Helper Function----------------------------------------------------*/
 
/**
 * @brief	 : Helper function to send upper 4 bits of data or command to the LCD in 4-bit mode.
 * @param[in]: Add_strLCDconfig, Pointer to the LCD configuration structure.
 * @param[in]: DataORcommand, Data or command to be sent to the LCD. Only upper 4 bits are considered.
 * @return	 : LCD_enumError_t Error status indicating the success or failure of the data transmission.
 * @details	 : This function is a helper function used to send the upper 4 bits of data or command to the
 * LCD in 4-bit mode. It takes the LCD configuration structure and the data or command to be sent as parameters.
 * The function checks for a NULL pointer in the configuration structure and sets the corresponding data pins
 * based on the bits of the provided data or command. The data pins are set according to the values of the bits
 * in the provided parameter, and the function returns an error if a NULL pointer is encountered.
 * @note	: The function is specifically designed for 4-bit mode data transmission to the LCD.
 */
static LCD_enumError_t LCD_enumHelperSend4BitMode(const LCD_strConfig *Add_strLCDconfig, u8 DataORcommand)
{
	LCD_enumError_t Loc_LCDRetErr = LCD_enumOk;

	/* Validation Statement - Ensure that the user does not pass a NULL pointer.*/
	if (Add_strLCDconfig == NULL)
	{
		Loc_LCDRetErr = LCD_enumNullPointer;
	}
	/* Everything is Ok, the function parameters is passed correctly.			*/
	else
	{
		DIO_enumError_t Loc_DIO_RetErr = DIO_enumOk;

		/* Iterate through the upper 4 bits of data or command*/
		for (u8 LCD_command_pin = 0; LCD_command_pin < 4; LCD_command_pin++)
		{
			/* Set the corresponding data pin based on the bit value*/
			Loc_DIO_RetErr = DIO_enumSetPin((&(Add_strLCDconfig->LCD_Data[LCD_command_pin])), ((DataORcommand >> LCD_command_pin) & 0x01));
		}
	}

	return Loc_LCDRetErr;
}

/**
 * @brief	 : Helper function to send 8 bits of data or command to the LCD in 8-bit mode.
 * @param[in]: Add_strLCDconfig, Pointer to the LCD configuration structure.
 * @param[in]: DataORcommand, Data or command to be sent to the LCD.
 * @return	 : LCD_enumError_t Error status indicating the success or failure of the data transmission.
 * @details  : This function is a helper function used to send 8 bits of data or command to the
 * LCD in 8-bit mode. It takes the LCD configuration structure and the data or command to be sent as parameters.
 * The function checks for a NULL pointer in the configuration structure and sets the corresponding data pins
 * based on the bits of the provided data or command. The data pins are set according to the values of the bits
 * in the provided parameter, and the function returns an error if a NULL pointer is encountered.
 * @note	: The function is specifically designed for 8-bit mode data transmission to the LCD.
 */
static LCD_enumError_t LCD_enumHelperSend8BitMode(const LCD_strConfig *Add_strLCDconfig, u8 DataORcommand)
{
	LCD_enumError_t Loc_LCDRetErr = LCD_enumOk;

	/* Validation Statement - Ensure that the user does not pass a NULL pointer.*/
	if (Add_strLCDconfig == NULL)
	{
		Loc_LCDRetErr = LCD_enumNullPointer;
	}
	/* Everything is Ok, the function parameters is passed correctly.			*/
	else
	{
		DIO_enumError_t Loc_DIO_RetErr = DIO_enumOk;

		/* Iterate through the 8 bits of data or command*/
		for (u8 LCD_command_pin = 0; LCD_command_pin < 8; LCD_command_pin++)
		{
			/* Set the corresponding data pin based on the bit value*/
			Loc_DIO_RetErr = DIO_enumSetPin((&(Add_strLCDconfig->LCD_Data[LCD_command_pin])), ((DataORcommand >> LCD_command_pin) & 0x01));
		}
	}

	return Loc_LCDRetErr;
}

/**
 * @brief	 : Helper function to send the Enable signal to the LCD.
 * @param[in]: Add_strLCDconfig, Pointer to the LCD configuration structure.
 * @return	 : LCD_enumError_t Error status indicating the success or failure of the Enable signal transmission.
 * @details	 : This function is a helper function used to send the Enable signal to the LCD. It takes the LCD configuration
 * structure as a parameter and sets the corresponding pin to a logic high level, waits for a short delay, and then sets
 * the pin to a logic low level. The pulse width of the Enable signal must be greater than 230 nanoseconds according to
 * the LCD datasheet. The function checks for a NULL pointer in the configuration structure and returns an error if encountered.
 */
static LCD_enumError_t LCD_enumHelperSendEnableSignal(const LCD_strConfig *Add_strLCDconfig)
{
	LCD_enumError_t Loc_LCDRetErr = LCD_enumOk;

	/* Validation Statement - Ensure that the user does not pass a NULL pointer.*/
	if (Add_strLCDconfig == NULL)
	{
		Loc_LCDRetErr = LCD_enumNullPointer;
	}
	/* Everything is Ok, the function parameters is passed correctly.			*/
	else
	{
		DIO_enumError_t Loc_DIO_RetErr = DIO_enumOk;

		/* Set the Enable signal pin to logic high*/
		Loc_DIO_RetErr = DIO_enumSetPin(&(Add_strLCDconfig->EnableSignal), DIO_enumLogicHigh);

		/* Wait for a short delay (pulse width > 230 nanoseconds)*/
		_delay_us(1);

		/* Set the Enable signal pin to logic low*/
		Loc_DIO_RetErr = DIO_enumSetPin(&(Add_strLCDconfig->EnableSignal), DIO_enumLogicLow);
	}

	return Loc_LCDRetErr;
}
/** 
 *@brief: Set DDRAM command, Set DDRAM address in address counter.
  +----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | RS | R/W | DB7 | DB6 | DB5 | DB4 | DB3 | DB2 | DB1 | DB0 |
  +----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |  0 |  0  |  0  |  1  | AC5 | AC4 | AC3 | AC2 | AC1 | AC0 |
  |  0 |  0  |  1  |  0  |  0  |  0  |  0  |  0  |  0  |  0  | 
  ------------------------------------------------------------
 */

/*
 *@note: Any address in DDRAM must be added to constant value (128 or 0x80) based on the Data sheet.
 */

/* The relation between DDRAM addresses and LCD Locations:
|------------------------------------|
| Address | Position				 |
|------------------------------------|
| 0x00    | 1st position of 1st row  |
| 0x01    | 2nd position of 1st row  |
| 0x02    | 3rd position of 1st row  |
| 0x03    | 4th position of 1st row  |
| 0x04    | 5th position of 1st row  |
| 0x05    | 6th position of 1st row  |
| 0x06    | 7th position of 1st row  |
| 0x07    | 8th position of 1st row  |
| 0x08    | 9th position of 1st row  |
| 0x09    | 10th position of 1st row |
| 0x0A    | 11th position of 1st row |
| 0x0B    | 12th position of 1st row |
| 0x0C    | 13th position of 1st row |
| 0x0D    | 14th position of 1st row |
| 0x0E    | 15th position of 1st row |
| 0x0F    | 16th position of 1st row |
|------------------------------------|
| 0x40    | 1st position of 2nd row  |
| 0x41    | 2nd position of 2nd row  |
| 0x42    | 3rd position of 2nd row  |
| 0x43    | 4th position of 2nd row  |
| 0x44    | 5th position of 2nd row  |
| 0x45    | 6th position of 2nd row  |
| 0x46    | 7th position of 2nd row  |
| 0x47    | 8th position of 2nd row  |
| 0x48    | 9th position of 2nd row  |
| 0x49    | 10th position of 2nd row |
| 0x4A    | 11th position of 2nd row |
| 0x4B    | 12th position of 2nd row |
| 0x4C    | 13th position of 2nd row |
| 0x4D    | 14th position of 2nd row |
| 0x4E    | 15th position of 2nd row |
| 0x4F    | 16th position of 2nd row |
|------------------------------------|
*/

/**
 * @brief    : Helper function to set the cursor position on the LCD (Set Address counter by specific Address in DDRAM ).
 * @param[in]: Add_strLCDconfig, Pointer to the LCD configuration structure.
 * @param[in]: Copy_u8Row, The row (line) on the LCD (LCD_ROW1 or LCD_ROW2) because I use 16x2 LCD.
 * @param[in]: Copy_u8Colomn, The column position on the LCD (0 to 15 for 16 columns).
 * @return	 : LCD_enumError_t Error status indicating the success or failure of setting the cursor position.
 * @details  : This function is a helper function used to set the cursor position on the LCD. It takes the LCD configuration
 * structure and the desired row and column as parameters. The row is specified as LCD_ROW1 or LCD_ROW2, and the column
 * is specified as a value from 0 to 15, representing 16 columns. The function calculates the corresponding command value
 * based on the row and column and sends the command to the LCD using the LCD_enumSendCommand function. The function
 * checks for a NULL pointer in the configuration structure and returns an error if encountered.
 */
static LCD_enumError_t LCD_enumHelperSetCursorPosition(const LCD_strConfig *Add_strLCDconfig, u8 Copy_u8Row, u8 Copy_u8Colomn)
{
	LCD_enumError_t Loc_LCDRetErr = LCD_enumOk;

	/* Validation Statement - Ensure that the user does not pass a NULL pointer.*/
	if (Add_strLCDconfig == NULL)
	{
		Loc_LCDRetErr = LCD_enumNullPointer;
	}
	/* Everything is Ok, the function parameters is passed correctly.			*/
	else
	{
		/* Set cursor position based on row and column*/
		switch (Copy_u8Row)
		{
			case LCD_ROW1:
			/* 
			 * @note: start Address of DDRAM is  0x80.
			 * The first location in DDRAM is (0x80 +0x00) > First Location in the First Row at LCD.
			 * The second location is (0x80 +0x01) > Second Location in the First Row at LCD, and so on.
			 */
				Loc_LCDRetErr = LCD_enumSendCommand(Add_strLCDconfig, (u8)(0x80 + Copy_u8Colomn));
				break;
			case LCD_ROW2:
			/* 
			 * @note: The Second Line at LCD start from (0x80 + 0x40) because each line can stores 40 characters.
			 * The First Location in the Second Row at LCD is 0xC0 (0x80+0x40).
			 * The Second Location in the Second Row at LCD is (0xC0 +0x01), and so on.
			 */
				Loc_LCDRetErr = LCD_enumSendCommand(Add_strLCDconfig, (u8)((0x80 + 0x40) + Copy_u8Colomn));
				break;
			default:
				{
					/* Nothing to Do, but for MISRA standard */
				}
		}
	}

	return Loc_LCDRetErr;
}