#include <p24F32KA301.h>
#include <uart.h>
#include <stdio.h>
#include <libpic30.h>		//C30 compiler definitions
#include <timer.h>
#include <string.h>

#include "uart1.h"
#include "uart2.h"
#include "io.h"

int main() {

    //OSCCONbits.COSC = 0b111;
    //OSCCONbits.NOSC = 0b111;

    RCONbits.SWDTEN = 0;


    init_io();

    init_uart1();
    init_uart2();

    printf1("\r\nWelcome to UART1 :D\n");
    printf2("\r\nWelcome to UART2 :D\n");

    while (1) {

    }
}
