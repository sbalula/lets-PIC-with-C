#include <p24F32KA301.h>
#include <uart.h>
#include <stdio.h>
#include <libpic30.h>		//C30 compiler definitions
#include <timer.h>
#include <string.h>

#include "uart1.h"
#include "uart2.h"
#include "io.h"
#include "gsm.h"
#include "delays.h"
#include "gps.h"

//_FOSC(0b0000000100000011); //Fast internal RC oscilator
//_FWDT(WDT_ON); //watchdog timer is off

int main() {

    char lixo[30];
    int send;
    // char RXbuffer2_cpy[100];

    //OSCCONbits.COSC = 0b111;
    //OSCCONbits.NOSC = 0b111;

    //int a;

    RCONbits.SWDTEN = 1;

    gps.valid = 0;

    delay_ms(2000);
    init_io();

    init_uart1();
    init_uart2();

    printf1("\r\nWelcome to UART1 :D\n");
    printf2("\r\nWelcome to UART2 :D\n");
    /*
   for (a = 0; a < 6000; ++a) {
       U2BRG = a;
       printf2("BRG = %lu\r\n ", a);
   }
     */

    init_gsm();

    sprintf(gps.texto, "NADA!");
    //sms_send((char *) "+351926373955",gps.texto);
    while (1) {
        //printf2("loop\n");
        erase = 1;
        if (!wait_for1("+CMTI:", 1)) {
            send = 1;
            printf2("Recebi uma mensagem...\n");
        }
        if (!wait_for_gps("GPRMC")) {
            //printf2("gprmc detected \n");
            while (erase);
            //printf2("%s", RXbuffer2);
            sscanf(RXbuffer2, "GPRMC,%lu.%lu,A,%lu.%lu,%c,%lu.%lu,%c,%lu.%lu,%lu.%lu,%lu%s",
                    &temp.time1, &temp.time2,
                    &temp.lat1, &temp.lat2, &temp.NS,
                    &temp.lon1, &temp.lon2, &temp.WE,
                    &temp.speed1, &temp.speed2,
                    &temp.course1, &temp.course2,
                    &temp.date,
                    lixo);

            {
                gps.time1 = temp.time1;
                gps.time2 = temp.time2;
                gps.lat1 = temp.lat1;
                gps.lat2 = temp.lat2;
                gps.NS = temp.NS;
                gps.lon1 = temp.lon1;
                gps.lon2 = temp.lon2;
                gps.WE = temp.WE;
                gps.speed1 = temp.speed1;
                gps.speed2 = temp.speed2;
                gps.course1 = temp.course1;
                gps.course2 = temp.course2;
                gps.date = temp.date;

                sprintf(gps.texto,
                        "maps.google.com/maps?q=%lu+%lu.%lu%c,%lu+%lu.%lu%c %lu-%luUTC",
                        gps.lat1 / 100, gps.lat1 % 100, gps.lat2, gps.NS,
                        gps.lon1 / 100, gps.lon1 % 100, gps.lon2, gps.WE,
                        gps.date, gps.time1);
                printf2("\n\r");
                printf2(gps.texto);
                printf2("\n\r");
                gps.valid = 1;

                //    $GPRMC,195306.463,A,3844.8813,N,00908.2309,W,5.35,120.75,170514,,,A*71$
                //  $GPRMC,144604.00,A,3844.89568,N,00909.11318,W,2.565,195.69,020615,,,D*76$
            }
        }
        if (send == 1 && gps.valid) {
            printf2("Vou enviar uma mensagem...\n");
            sms_send((char *) "+351926373955", gps.texto);
            send = 0;
            printf2("Ja esta :D\n");
        }
        //pull_uart1();
        ClrWdt();
    }
}
