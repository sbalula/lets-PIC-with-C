#include <p24F32KA301.h>
#include <uart.h>
#include <stdio.h>
#include <libpic30.h>		//C30 compiler definitions
#include <timer.h>
#include <string.h>


#include "gsm.h"
#include "io.h"
#include "delays.h"
#include "uart1.h"



unsigned int gsm_state = 0;
unsigned char a;

int init_gsm() {
    if (gsm_state == 0) {
        /*
        GSM_PWR = 1;
        delay_ms(1000);
        GSM_PWR = 0;
        gsm_state = 1;
         */


        //delay_ms(2000);
        
        printf1("AT\r");
        //delay_ms(2000);
        //WAIT("OK\r\n");
        //printf("ATE0\r");

        WAIT("OK");
        //delay_ms(2000);
        printf1("AT+CSCA=\"+351962100000\"\r"); //Centro de mensagens TMN
        WAIT("OK");
        //delay_ms(2000);
        //printf("AT+CSMP=17,167,0,240\r");
        printf1("AT+CSMP=17,167,0,8\r");
        WAIT("OK");
        //delay_ms(2000);
        printf1("AT+CMGF=1\r");
        //delay_ms(2000);
        WAIT("OK");
        /*
        printf("AT+CMGS=\"+351926373955\"\r");
        delay_ms(2000);
        puts1USART((char *) "Ola!!!");

        delay_ms(2000);
        TXREG1 = 0x1A;
        delay_ms(20000);
        GSM_PWR = 1;
        delay_ms(1000);
        GSM_PWR = 0;
         */
    }
    return 0;
}

int sms_send(char* number, char* text) {
    printf1("AT+CMGS=\"%s\"\r", number);
    WAIT(">");
    delay_ms(2000);
    printf1("%s%c", text, 0x1A);
    WAIT("OK");
    printf1("AT+CMGDA=\"DEL ALL\"\r");
    WAIT("OK");
    return 0;
}

void close_gsm() {
    if (gsm_state == 1) {
        GSM_PWR = 1;
        delay_ms(1000);
        GSM_PWR = 0;
        gsm_state = 0;
    }
}

int wait_for1(char * thing, unsigned long b) {
    int sizeofthing = strlen(thing);
    //char * trash1, trash2;
    int i;
    //sprintf(temp, "sizeofthing=%u\r\n", sizeofthing);
    //puts1USART((char *) temp);
    for (; b > 0; b = b - 1) {
        //printf("RX1[%i]=%h\tt[%i]=%h\r", j, RXbuffer[j], i, thing[i])
        //for (i=0; i<80; ++i) printf("%c ", RXbuffer[i]);
        //printf("\n");
        for(i= 0; i < 80; ++i){

        if (!strncmp(RXbuffer1+i, thing, sizeofthing)) {
            clear_RXbuffer1();
            delay_ms(1000);
            return 0;
        }
        }
    }
    return 1;
}
//puts1USART((char *) "UM ERRO OCORREU\r");

