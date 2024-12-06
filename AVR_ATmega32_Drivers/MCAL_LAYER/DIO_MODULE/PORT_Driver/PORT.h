/*
 * File Name: PORT.h
 * Layer	: MCAL
 * Module	: DIO
 * Version  : V 0.0
 * Created	: 12/10/2023 11:06:06 PM
 * Author	: Anas Khamees
 */ 

#ifndef PORT_H_
#define PORT_H_

#include "../DIO_Driver/DIO.h"
#include "PORT_Config.h"

/**
 *@brief  : Function to Configure the Pins to be INPUT pin or OUTPUT pin.
 *@param  : Add_strPinConfig, is a pointer points to struct of pin configuration > @ref:DIO_strPinConfig_t.
 *@param  : Port Number,Pin Number,Configuration type(Input/Output).
 *@return : Error State                                               
 */	
DIO_enumError_t PORT_enumSetPinConfig(const DIO_strPinConfig_t *Add_strPinConfig);

/**
 *@brief  : Function to Configure the whole Port(8 pins) at one time to be INPUT or OUTPUT port.
 *@param  : Port Number,Configuration type(Input/Output).
 *@return : Error State                                                                      
 */
DIO_enumError_t PORT_enumSetPortConfig(DIO_enumPorts_t Copy_enumPortNum,DIO_enumDirection_t Copy_enumDirection);

/**
 *@brief  : Function to Initialize the Configuration of port/Pins.
 *@param  : Add_strPinConfig, is a pointer points to struct of pin configuration > @ref:DIO_strPinConfig_t.
 *@param  : Port Number,Pin Number,Configuration type(Input/Output).
 *@return : Error State                                                                      
 */
DIO_enumError_t PORT_enumInitConfig(const DIO_strPinConfig_t *Add_strPinConfig);

#endif /* PORT_H_ */