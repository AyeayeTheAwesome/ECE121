/* 
 * File:   Uart.c
 * Author: Ayeay
 *
 * Created on March 2, 2026, 1:17 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "BOARD.h"
#include <sys/attribs.h>

/*******************************************************************************
 * #INCLUDES                                                                   *
 ******************************************************************************/

#include "Uart.h" // The header file for this source file. 

/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
#define BAUDRATE 115200
#define PBCLK 40000000L
#define UART_check
/*******************************************************************************
 * PRIVATE TYPEDEFS                                                            *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES                                                 *
 ******************************************************************************/

/*******************************************************************************
 * PUBLIC FUNCTION IMPLEMENTATIONS                                             *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE FUNCTION IMPLEMENTATIONS                                            *
 ******************************************************************************/



void Uart_Init(unsigned long baudRate) {
  
    U1MODE = 0x00; //clear regs, rx, tx
    U1STA  = 0x00;

    // Set baud rate
    U1BRG = (PBCLK / (16 * baudRate)) - 1; //sets peripheral clock and baud

    // config
    U1MODEbits.BRGH = 0;   // Standard speed mode
    U1MODEbits.PDSEL = 0;  // 8bit no parity
    U1MODEbits.STSEL = 0;  // 1 stop bit

    // Enable TX and RX
    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;
    
    // Enable UART module
    U1MODEbits.ON = 1;
    
    //pps setup
        // Map UART1 TX to RPB3
    //RPB3Rbits.RPB3R = 0b0001;   // U1TX

    // Map UART1 RX to RPB2
    //U1RXRbits.U1RXR = 0b0100;   // RPB
}


void Uart_WriteChar(char car) {
    // buff is empt write char
    while (U1STAbits.UTXBF);
    U1TXREG = car; //transfer reg
   
}

bool Uart_CharAvailable(void) {
    return U1STAbits.URXDA;   //urxda bit is available
    
}

uint8_t Uart_ReadChar(void) {
    while (!Uart_CharAvailable());
    return U1RXREG; //contains info
}

//test harn
#ifdef UART_check

int main(void) {
    BOARD_Init();
    Uart_Init(BAUDRATE);

    while (1) {
        if (Uart_CharAvailable()) { //see bit, send it back
            uint8_t cr2 = Uart_ReadChar();
            Uart_WriteChar(cr2);
        }
    }
    /*while (1) {
         U1TXREG = 'U';   
    }*/
    

    return 0;
}

#endif