#include "delays.h"

void delay_ms(unsigned int b) {
    unsigned int a;
    while(--b)
        for (a = 500; a; --a); //~1ms delay
}