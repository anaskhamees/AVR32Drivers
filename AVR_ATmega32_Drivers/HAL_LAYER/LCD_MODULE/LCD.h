/*
 * File Name: LCD.h
 * Layer	: HAL
 * Module	: LCD
 * Version  : V 0.0
 * Created	: 12/31/2023 9:49:35 PM
 * Author	: Anas Khamees
 * Brief	: This header file defines structures, Enumerators and functions for LCD driver.
 */ 

#ifndef LCD_H_
#define LCD_H_

#include "../../MCAL_LAYER/DIO_MODULE/DIO_Driver/DIO.h"
#include "../../MCAL_LAYER/DIO_MODULE/PORT_Driver/PORT.h"

/*---------------------------------------- Configuration MACROs-----------------------------------------------------------*/
#define FOUR_BIT_MODE	0x01
#define EIGHT_BIT_MODE  0x02
#define SELECT_LCD_MODE		 FOUR_BIT_MODE
#define LCD_ROW1		0x01
#define LCD_ROW2		0x02
/*---------------------------------------- Commands MACROs----------------------------------------------------------------*/

/** 
 *@brief: Clear command, write spaces on all DDRAM addresses.
 +----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 | RS | R/W | DB7 | DB6 | DB5 | DB4 | DB3 | DB2 | DB1 | DB0 |
 +----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 |  0 |  0  |  0  |  0  |  0  |  0  |  0  |  0  |  0  |  1  |
 ------------------------------------------------------------
 */
#define LCD_CLEAR_DISPLAY			0x01
/** 
 *@brief: Return Home command, Sets DDRAM address to (0x00) in AC and returns shifted display to its original position.
 *Cursor at home position at top left.
  +----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | RS | R/W | DB7 | DB6 | DB5 | DB4 | DB3 | DB2 | DB1 | DB0 |
  +----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |  0 |  0  |  0  |  0  |  0  |  0  |  0  |  0  |  1  |  X  |
  ------------------------------------------------------------
 */
#define LCD_RETURN_HOME				0x02
/** 
 *@brief: Entry Mode Set command, Sets cursor move direction(incremental or decremental) and enable the shift of entire display but cursor is fixed.
  +----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | RS | R/W | DB7 | DB6 | DB5 | DB4 | DB3 | DB2 | DB1 | DB0 |
  +----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |  0 |  0  |  0  |  0  |  0  |  0  |  0  |  1  | I/D |  SH |
  +----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |  0 |  0  |  0  |  0  |  0  |  0  |  0  |  1  |  0  |  0  |
  |  0 |  0  |  0  |  0  |  0  |  0  |  0  |  1  |  1  |  0  |
  |  0 |  0  |  0  |  0  |  0  |  0  |  0  |  1  |  0  |  1  |
  |  0 |  0  |  0  |  0  |  0  |  0  |  0  |  1  |  1  |  1  |
  ------------------------------------------------------------
 */
#define LCD_ENTRY_MODE_DEC_SHIFT_OFF		 0x04
#define LCD_ENTRY_MODE_INC_SHIFT_OFF		 0x06  /*Normal Mode*/
#define LCD_ENTRY_MODE_DEC_SHIFT_ON			 0x05
#define LCD_ENTRY_MODE_INC_SHIFT_ON			 0x07
/** 
 *@brief: Display ON/OFF command,Set ON/OFF of entire display (D), cursor underline ON/OFF(C), and blinking of cursor position character(B).
  +----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | RS | R/W | DB7 | DB6 | DB5 | DB4 | DB3 | DB2 | DB1 | DB0 |
  +----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |  0 |  0  |  0  |  0  |  0  |  0  |  1  |  D  |  C  |  B  |
  +----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |  0 |  0  |  0  |  0  |  0  |  0  |  1  |  0  |  0  |  0  |
  |  0 |  0  |  0  |  0  |  0  |  0  |  1  |  0  |  0  |  1  |  Not valid Ignore it
  |  0 |  0  |  0  |  0  |  0  |  0  |  1  |  0  |  1  |  0  |	Not valid Ignore it
  |  0 |  0  |  0  |  0  |  0  |  0  |  1  |  0  |  1  |  1  |	Not valid Ignore it
  |  0 |  0  |  0  |  0  |  0  |  0  |  1  |  1  |  0  |  0  |
  |  0 |  0  |  0  |  0  |  0  |  0  |  1  |  1  |  0  |  1  |
  |  0 |  0  |  0  |  0  |  0  |  0  |  1  |  1  |  1  |  0  |
  |  0 |  0  |  0  |  0  |  0  |  0  |  1  |  1  |  1  |  1  |
  ------------------------------------------------------------
 */
#define LCD_DISPLAY_CURSOR_BLINK_ALL_OFF		0x08
#define LCD_DISPLAY_ON_CURSOR_OFF_BLINK_OFF		0x0C
#define LCD_DISPLAY_ON_CURSOR_OFF_BLINK_ON		0x0D
#define LCD_DISPLAY_ON_CURSOR_ON_BLINK_OFF		0x0E
#define LCD_DISPLAY_CURSOR_BLINK_ALL_ON			0x0F
/** 
 *@brief: Cursor or Display shift command, Moves cursor and shifts display without changing DDRAM contents.
  +----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | RS | R/W | DB7 | DB6 | DB5 | DB4 | DB3 | DB2 | DB1 | DB0 |
  +----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |  0 |  0  |  0  |  0  |  0  |  0  | S/C | R/L |  X  |  X  |
  +----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |  0 |  0  |  0  |  0  |  0  |  1  |  0  |  0  |  0  |  0  |
  |  0 |  0  |  0  |  0  |  0  |  1  |  0  |  1  |  0  |  0  |
  |  0 |  0  |  0  |  0  |  0  |  1  |  1  |  0  |  0  |  0  |
  |  0 |  0  |  0  |  0  |  0  |  1  |  1  |  1  |  0  |  0  |
  ------------------------------------------------------------
 */
#define LCD_CURSOR_SHIFT_LEFT		0x10	/*Shifts cursor position to the left  (AC is decreased by 1).			   */
#define	LCD_CURSOR_SHIFT_RIGHT		0x14	/*Shifts cursor position to the right (AC is increased by 1).			   */
#define	LCD_DISPLAY_SHIFT_LEFT		0x18	/*Shifts the entire display to the left, cursor follows the display shift. */ 
#define LCD_DISPLAY_SHIFT_RIGHT		0x1C	/*Shifts the entire display to the right, cursor follows the display shift.*/
/** 
 *@brief: Function Set command, Sets interface data length (DL:8-bit/4-bit), numbers of display line (N: 2-line/1-line), and display font type (F: 5x11 dots/ 5x8 dots).
 *My LCD 16x2 and i prefer to use 5x7 dots, so in my case N must be HIGH and F must be LOW, So only TWO combination match my case.
  +----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | RS | R/W | DB7 | DB6 | DB5 | DB4 | DB3 | DB2 | DB1 | DB0 |
  +----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |  0 |  0  |  0  |  0  |  0  |  DL |  N  |  F  |  X  |  X  |
  +----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |  0 |  0  |  0  |  0  |  1  |  0  |  0  |  0  |  0  |  0  |   4-bit mode, 1 line, 5x7 dots (ignore it because my LCD is 2 Line).
  |  0 |  0  |  0  |  0  |  1  |  0  |  0  |  1  |  0  |  0  |   4-bit mode, 1 line, 5x10 dots(ignore it because my LCD is 2 Line and I use 5x7 dots).
  |  0 |  0  |  0  |  0  |  1  |  0  |  1  |  0  |  0  |  0  |	 4-bit mode, 2 line, 5x7 dots (Accepted: LCD is 2 Line and 5x7 dots).
  |  0 |  0  |  0  |  0  |  1  |  0  |  1  |  1  |  0  |  0  |	 4-bit mode, 2 line, 5x10 dots(ignore it because  I use 5x7 dots).
  |  0 |  0  |  0  |  0  |  1  |  1  |  0  |  0  |  0  |  0  |   8-bit mode, 1 line, 5x7 dots (ignore it because my LCD is 2 Line).
  |  0 |  0  |  0  |  0  |  1  |  1  |  0  |  1  |  0  |  0  |	 8-bit mode, 1 line, 5x10 dots(ignore it because my LCD is 2 Line and I use 5x7 dots).
  |  0 |  0  |  0  |  0  |  1  |  1  |  1  |  0  |  0  |  0  |   8-bit mode, 2 line, 5x7 dots (Accepted: LCD is 2 Line and 5x7 dots).
  |  0 |  0  |  0  |  0  |  1  |  1  |  1  |  1  |  0  |  0  |   8-bit mode, 2 line, 5x10 dots(ignore it because  I use 5x7 dots).
  ------------------------------------------------------------
 */
#define LCD_4BIT_MODE		0x28
#define LCD_8BIT_MODE		0x38
/** 
 *@brief: Set CGRAM command, Set CGRAM address in address counter.
 * (AC3 ~ AC5) refer to CGRAM Locations (0 ---> 7) 8 characters.
 * (AC0 ~ AC2) refer to the rows for each location (character) (0 ---> 7) 8 rows because each character 5x8 dot.
  +----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | RS | R/W | DB7 | DB6 | DB5 | DB4 | DB3 | DB2 | DB1 | DB0 |
  +----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |  0 |  0  |  0  |  1  | AC5 | AC4 | AC3 | AC2 | AC1 | AC0 |
  |  0 |  0  |  0  |  1  |  0  |  0  |  0  |  0  |  0  |  0  | 
  ------------------------------------------------------------
 */

/* CGRAM locations:

| Character 0  |   Character 1  |  Character 2  |  Character 3  |  Character 4  |  Character 5  |  Character 6  |  Character 7  |
| -------------------------------------------------------------------------------------------------------------------------------
| 0 1 0 1 1    |   1 1 0 1 0    |  0 0 0 0 0    |  1 1 1 1 1    |  1 0 1 0 1    |  0 0 0 1 1    |  1 1 1 1 0    |  0 0 0 0 0    |
| x x x x x    |   x x x x x    |  x x x x x    |  x x x x x    |  x x x x x    |  x x x x x    |  x x x x x    |  x x x x x    |
| x x x x x    |   x x x x x    |  x x x x x    |  x x x x x    |  x x x x x    |  x x x x x    |  x x x x x    |  x x x x x    |
| x x x x x    |   x x x x x    |  x x x x x    |  x x x x x    |  x x x x x    |  x x x x x    |  x x x x x    |  x x x x x    |
| x x x x x    |   x x x x x    |  x x x x x    |  x x x x x    |  x x x x x    |  x x x x x    |  x x x x x    |  x x x x x    |
| x x x x x    |   x x x x x    |  x x x x x    |  x x x x x    |  x x x x x    |  x x x x x    |  x x x x x    |  x x x x x    |
| x x x x x    |   x x x x x    |  x x x x x    |  x x x x x    |  x x x x x    |  x x x x x    |  x x x x x    |  x x x x x    |
| x x x x x    |   x x x x x    |  x x x x x    |  x x x x x    |  x x x x x    |  x x x x x    |  x x x x x    |  x x x x x    |
| 0 0 0 0 0    |   0 0 0 0 0    |  0 0 0 0 0    |  0 0 0 0 0    |  0 0 0 0 0    |  0 0 0 0 0    |  0 0 0 0 0    |  0 0 0 0 0    |
*/

#define LCD_CGRAM_START_ADDRESS			0x40
/** 
 *@brief: Set DDRAM command, Set DDRAM address in address counter.
  +----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | RS | R/W | DB7 | DB6 | DB5 | DB4 | DB3 | DB2 | DB1 | DB0 |
  +----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |  0 |  0  |  0  |  1  | AC5 | AC4 | AC3 | AC2 | AC1 | AC0 |
  |  0 |  0  |  1  |  0  |  0  |  0  |  0  |  0  |  0  |  0  | 
  ------------------------------------------------------------
 */
#define LCD_DDRAM_START_ADDRESS			0x80

/*------------------------------------- User Defined Data Types Declaration---------------------------------*/

/**
 * @brief: Enumeration of LCD module error states.
 */
typedef enum
{
	LCD_enumOk = 0,           /**< Everything is okay; the function performed correctly. */
	LCD_enumNullPointer,      /**< NULL pointer is passed as a function parameter.	   */
} LCD_enumError_t;

/**
 * @brief: Structure representing the configuration for 8-bit mode of the LCD module.
 */
typedef struct
{
	DIO_strPinConfig_t	RegisterSelect;  /* Select communication with instruction or data register*/
	DIO_strPinConfig_t	EnableSignal  ;  /* Enable signal to send the data or command to LCD MPU  */
 #ifdef SELECT_LCD_MODE
	#if (SELECT_LCD_MODE==EIGHT_BIT_MODE)
	DIO_strPinConfig_t	LCD_Data[8]	  ;  /* 8 pins of data/commands (DB0~DB7)					  */
	#elif (SELECT_LCD_MODE==FOUR_BIT_MODE)
	DIO_strPinConfig_t	LCD_Data[4]	  ;  // 4 pins of data/commands (DB4~DB7)
	#endif
#endif
}LCD_strConfig;

/*--------------------------------------------- APIs Interfaces ------------------------------------------*/

/* @brief	 : Initializes the LCD module based on the provided configuration.
 * @param[in]: Add_strLCDconfig Pointer to the LCD configuration structure.
 * @return	 : LCD_enumError_t Error status indicating the success or failure of the initialization.
 * @details	 : This function initializes the LCD module based on the configuration provided in the @ref LCD_strConfig structure.
 * It configures the control pins (RegisterSelect and EnableSignal) and the data pins according to the selected LCD mode (4-bit or 8-bit).
 * The initialization process follows the steps recommended in the LMB161A LCD datasheet.
 * @note	 : The function returns an error if a NULL pointer is provided as the configuration structure.
 */
LCD_enumError_t	LCD_enumInit(const LCD_strConfig *Add_strLCDconfig);
/**
 * @brief	 : Sends a command to the LCD module.
 * @param[in]: Add_strLCDconfig Pointer to the LCD configuration structure.
 * @param[in]: Copy_u8LCDcommand, The command to be sent to the LCD.
 * @return	 : LCD_enumError_t Error status indicating the success or failure of the command transmission.
 * @details  : This function sends a command to the LCD module using the provided configuration structure.
 * It checks for a NULL pointer and then uses helper functions to send the command based on the selected LCD mode (4-bit or 8-bit).
 * @note	 : The function returns an error if a NULL pointer is provided as the configuration structure.
 */
LCD_enumError_t LCD_enumSendCommand(const LCD_strConfig *Add_strLCDconfig, u8 Copy_u8LCDcommand);
/**
 * @brief	 : Sends a character to be displayed on the LCD.
 * @param[in]: Add_strLCDconfig Pointer to the LCD configuration structure.
 * @param[in]: Copy_u8LCDdata The character to be sent to the LCD.
 * @return	 : LCD_enumError_t Error status indicating the success or failure of the data transmission.
 * @details  : This function sends a character to the LCD module using the provided configuration structure.
 * It checks for a NULL pointer, sets the Register Select pin to high to indicate data transmission,
 * and uses helper functions to send the character based on the selected LCD mode (4-bit or 8-bit).
 * @note	 : The function returns an error if a NULL pointer is provided as the configuration structure.
 */
LCD_enumError_t LCD_enumSendChar(const LCD_strConfig *Add_strLCDconfig, u8 Copy_u8LCDdata);
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
LCD_enumError_t LCD_enumSendCharPosition(const LCD_strConfig *Add_strLCDconfig,u8 Copy_u8Row,u8 Copy_u8Colomn, u8 Copy_u8LCDdata);
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
LCD_enumError_t LCD_enumSendString(const LCD_strConfig *Add_strLCDconfig, u8* Add_u8LCDstring);
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

LCD_enumError_t LCD_enumSendStringPosition(const LCD_strConfig *Add_strLCDconfig,u8 Copy_u8Row,u8 Copy_u8Colomn, u8* Add_u8LCDstring);
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



LCD_enumError_t LCD_enumSendSpecialChar(const LCD_strConfig *Add_strLCDconfig, u8 Copy_u8Row,u8 Copy_u8Colomn,u8* Add_u8CharArrPattern,u8 Copy_u8CGRAM_Location);


#endif /* LCD_H_ */