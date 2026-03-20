/* 
 * File:   Uart.h
 * Author: <Ayman>
 * Brief:  uart protocol file
* Created on March 2, 2026, 1:18 PM
 */

#ifndef UART_H // Header guard
#define	UART_H //

/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/

//#include "otherHeaderFile.h" 
//#include "anotherOne.h"
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

//func defs
void Uart_Init(unsigned long baudRate);
void Uart_WriteChar(char car);
uint8_t Uart_ReadChar(void);
bool Uart_CharAvailable(void);


#endif	/* LIBRARYTEMPLATE_H */ // End of header guard

