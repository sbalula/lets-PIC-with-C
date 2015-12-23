#define _XTAL_FREQ 16000000UL

#include <pic12f1840.h>
#include <xc.h>
#include <stdint.h>
#include <stdlib.h>
#define ABS(x) (x>0?x:-x)

//#define CONFIG_REG1 0b1111111111100111

//CONFIG1 = 0b1111111111100111;

void define_nota(int nota);

static uint16_t notas[] = {0xEEE, 0xD4D, 0xBDA, 0xB2F, 0x9F7, 0x8E1, 0x7E9, 0x777};

int main(void) {

    //__CONFIG(1, 0b1111111111100111);

    OSCCON = 0b11111010;
    WDTCONbits.WDTPS = 0b10010;

    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA4 = 1;
    ANSELAbits.ANSA4 = 0;

    CCP1CON = 0b00000010;
    define_nota(0);


    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.CCP1IE = 1;
    PIR1bits.CCP1IF = 0;
    PIR1bits.TMR1IF = 0;


    T2CONbits.TMR2ON = 1;
//    uint_8_t period=300;
    int i = 0;
    uint16_t j = 0;
    while (1) {
        if (PORTAbits.RA4 != 0) {
            T1CON = 0b00000001;
            for (j = 0; j < 50; ++j) {
                i = (i > 6 ? 0 : i + 1);
                define_nota((TMR2 & 0x03) ^ ((TMR2 & 0b11100000)>>5));
                __delay_ms(200);
            }

            T1CON = 0;
        }
        CLRWDT();
    }
}

void interrupt ISR() {
    if (PIR1bits.CCP1IF) { // if timer flag is set & interrupt enabled
        PIR1bits.CCP1IF = 0;
        TMR1H = 0;
        TMR1L = 0;
        LATAbits.LATA4 = !LATAbits.LATA4;
    }

}

void define_nota(int nota) {
    CCPR1L = notas[nota] & 0x00ff;
    CCPR1H = (notas[nota] >> 8) & 0x00ff;
}
