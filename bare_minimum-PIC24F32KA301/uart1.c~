#include <p24F32KA301.h>		//defines dspic registers
#include <stdio.h>		//standart IO library C
#include <libpic30.h>		//C30 compiler definitions
#include <uart.h>		//UART (serial port) function and utilities library
#include <timer.h>		//timer library
#include <string.h>

#include "uart1.h"
//#include "lcd.h"


unsigned int UMODEvalue, U1STAvalue, str_pos1 = -1; //auxiliary UART config variables
char RXbuffer1[80];

void init_uart1() {
    U1MODE = 0b1000100000000000;
    U1STA = 0b0000001000000000;
    U1BRG = 12;
    _U1RXIE = 1;
}

/****************************************************
 ************     Interruptions   *******************
 ****************************************************/

/* This is UART1 receive ISR */
// UART Interruption handler

void __attribute__((__interrupt__, auto_psv)) _U1RXInterrupt(void) {
    IFS0bits.U1RXIF = 0; //resets and reenables the Rx1 interrupt flag

    // Read the receive buffer until at least one or more character can be read
    while (U1STAbits.URXDA) {
        //increments the position in the buffer to store the next char
        //if(++str_pos >= 80){str_pos = 0;}    //if the last position is reached then return to initial position
        RXbuffer1[++str_pos1 > 79 ? str_pos1 = 0 : str_pos1] = U1RXREG; //stores the last received char in the buffer
        U2TXREG = RXbuffer1[str_pos1];
        //printf("%c", RXbuffer[str_pos]);  //prints the last received char
        //if (RXbuffer[str_pos ? str_pos - 1 : 0] == '\r') str_pos = -1;
    }
}

void clear_RXbuffer1() {
    int i;
    str_pos1 = -1;
    for (i = 0; i < 80; i++) {
        RXbuffer1[i] = '\0';
    }
}
