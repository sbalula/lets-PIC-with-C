#include <p24F32KA301.h>		//defines dspic registers
#include <stdio.h>		//standart IO library C
#include <libpic30.h>		//C30 compiler definitions
#include <uart.h>		//UART (serial port) function and utilities library
#include <timer.h>		//timer library
#include <string.h>

#include "uart2.h"
#include "uart1.h"
//#include "lcd.h"

/*
  bibf and bibv struct store strings to compare with inputs.
  For every string, there is a pointer to the corresponding function or variable
 */

unsigned int str_pos2 = -1; //auxiliary UART config variables
char RXbuffer2[80];
int erase = 0;

void init_uart2() {

    U2MODE = 0b1000100000001000;
    U2STA = 0b0000001000000000;
    U2BRG = 12;
    _U2RXIE = 1;
    //__C30_UART = 2; //define UART1 as predefined for use with stdio library, printf etc

}


/****************************************************
 ************     Interruptions   *******************
 ****************************************************/

/* This is UART1 receive ISR */
// UART Interruption handler

void __attribute__((__interrupt__, auto_psv)) _U2RXInterrupt(void) {
    IFS1bits.U2RXIF = 0; //resets and reenables the Rx1 interrupt flag

    // Read the receive buffer until at least one or more character can be read
    while (U2STAbits.URXDA) {
        //increments the position in the buffer to store the next char
        //if(++str_pos >= 80){str_pos = 0;}    //if the last position is reached then return to initial position
        if (erase == 1) {
            RXbuffer2[++str_pos2 > 79 ? str_pos2 = 0 : str_pos2] = U2RXREG; //stores the last received char in the buffer
            U2TXREG = RXbuffer2[str_pos2];
            if (RXbuffer2[str_pos2] == '$')
                clear_RXbuffer2();
            if (RXbuffer2[str_pos2] == '*')
                erase = 0;
        }
        else
            U2RXREG;
    }
}

void clear_RXbuffer2() {
    int i;
    str_pos2 = -1;
    for (i = 0; i < 80; i++) {
        RXbuffer2[i] = '\0';
    }
}