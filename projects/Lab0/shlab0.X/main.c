/* 
 * File:   main.c
 * Author: Ayeay
 *
 * Created on Feb 27, 2026, 3:13 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include <xc.h>
#include "BOARD.h"

#warning main compile test


//#define part1 //comment out for part 2

void NOP_delay_ms(int amount) {
    int milsecs = amount * 1000;
    for (int i = 0; i < milsecs; i++) {
        asm (" nop ");
    }
}

//btn - 4, 34, 36, 37 - RG6, RF2, RG3, RG2
// actually i lied its RF1, RD5, RD6, RD7

int main(void){
    BOARD_Init();
    
    TRISFbits.TRISF1 = 1;
    TRISDbits.TRISD5 = 1;
    TRISDbits.TRISD6 = 1;
    TRISDbits.TRISD7 = 1;

    // active low butons
    int but1 = (PORTFbits.RF1 == 0);
    int but2 = (PORTDbits.RD5 == 0);
    int but3 = (PORTDbits.RD6 == 0);
    int but4 = (PORTDbits.RD7 == 0);
    
    
    TRISE = 0x00; //set led pins as outputs
    LATECLR  = 0xFF; //set's all off
    
    #ifdef part1
        while (1) { //button test
            but1 = (PORTFbits.RF1 == 0);
            but2 = (PORTDbits.RD5 == 0);
            but3 = (PORTDbits.RD6 == 0);
            but4 = (PORTDbits.RD7 == 0);
            LATEINV = 128*but4 + 64*but3 + 32*but4 + 16*but3 + 8*but1 + 4*but2 + 2*but1 + 1*but2;
            NOP_delay_ms(1000);
        }
    #else
        //counter
        //int invlist = [1, 3, 7, 15, 31, 63, 127, 255];
        //int currlist = [];
        int counter = 0;
        LATEINV = 255; //init leds properly
        while(1) {
            but1 = (PORTFbits.RF1 == 0);
            but2 = (PORTDbits.RD5 == 0);
            but3 = (PORTDbits.RD6 == 0);
            but4 = (PORTDbits.RD7 == 0);
            if (!but1 | !but2 | !but3 | !but4) {
                LATEINV = counter-1;
                //reset leds to 0
                counter = 0;
                LATEINV = 255; //init leds properly
                while (!but1 | !but2 | !but3 | !but4) {
                    asm("nop");
                    but1 = (PORTFbits.RF1 == 0);
                    but2 = (PORTDbits.RD5 == 0);
                    but3 = (PORTDbits.RD6 == 0);
                    but4 = (PORTDbits.RD7 == 0);
                }
            } else {
            LATEINV = 128*(counter % 128 == 0) + 64*(counter % 64 == 0) + 32*(counter % 32 == 0) + 16*(counter % 16 == 0)
                    + 8*(counter % 8 == 0) + 4*(counter % 4 == 0) + 2*(counter % 2 == 0) + 1*(counter % 1 == 0);
            NOP_delay_ms(250); //slow down count speed here
            counter++;
            }
        }
    // inv = 1, 3, 1, 7, 1, 3, 1, 15, 1, 3, 1, 7, 1

    #endif
    
    /*while (1) { //blink test
        LATESET = 0xFF;
        NOP_delay_ms(1000);
        LATEbits.LATE0 = 0;
        LATEbits.LATE1 = 0;
        LATEbits.LATE2 = 0;
        LATEbits.LATE3 = 0;
        LATEbits.LATE4 = 0;
        LATEbits.LATE5 = 0;
        LATEbits.LATE6 = 0;
        LATEbits.LATE7 = 0;
        //LATESET == 0x00;
        NOP_delay_ms(1000);
    }*/
        
}


