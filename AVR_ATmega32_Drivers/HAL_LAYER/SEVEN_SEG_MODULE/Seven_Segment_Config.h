/*
 * File Name: Seven_Segment_config.h
 * Layer	: HAL
 * Module	: SEVEN_SEG
 * Version  : V 0.0
 * Created	: 12/18/2023 9:41:36 PM
 * Author	: Anas Khamees
 */ 

#ifndef SEVEN_SEGMENT_CONFIG_H_
#define SEVEN_SEGMENT_CONFIG_H_
#include "Seven_Segment.h"

/**
 * @brief Macro representing the first used 7-segment display SSD.
 */
#define _7SEGMENT_1     0x00

/**
 * @brief Macro representing the second used 7-segment display SSD.
 */
#define _7SEGMENT_2     0x01

/**
 * @brief Macro representing the third used 7-segment display SSD.
 */
#define _7SEGMENT_3     0x02

/**
 * @brief Macro representing the fourth used 7-segment display SSD.
 */
#define _7SEGMENT_4     0x03

/**
 * @brief Macro representing the fifth used 7-segment display SSD.
 */
#define _7SEGMENT_5      0x04

/**
 * @brief Macro representing one 7-segment display.
 */
#define ONE_7SEGMENT      0x01

/**
 * @brief Macro representing two 7-segment displays.
 */
#define TWO_7SEGMENT      0x02

/**
 * @brief Macro representing three 7-segment displays.
 */
#define THREE_7SEGMENT    0x03

/**
 * @brief Macro representing four 7-segment displays.
 */
#define FOUR_7SEGMENT     0x04

/**
 * @brief Macro representing five 7-segment displays.
 */
#define FIVE_7SEGMENT     0x05

/**
 * @brief Macro representing the total number of 7-segment displays used.
 *
 * This macro is used to specify the actual number of 7-segment displays employed in the project.
 * It is set to TWO_7SEGMENT by default, indicating the default number.
 * Users should modify this macro to represent the actual number of 7-segment displays in their project.
 */
#define MAX_7SEGMENTS_USED   ONE_7SEGMENT

/**
 * @brief: External array to hold the configuration of multiple 7-segment displays.
 * This array is of type _7SEG_strConfig_t, and its size is determined by the MAX_7SEG macro.
 * Each element in the array represents the configuration of a single 7-segment display.
 */
extern _7SEG_strConfig_t _7Segment[MAX_7SEGMENTS_USED];






#endif /* SEVEN_SEGMENT_CONFIG_H_ */