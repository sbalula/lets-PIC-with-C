#ifndef IO_H
#define	IO_H
/*
#define LCD_ce      LATBbits.LATB7
#define LCD_rst     LATBbits.LATB3
#define LCD_dc      LATBbits.LATB2
#define LCD_din     LATBbits.LATB1
#define LCD_clk     LATDbits.LATD0
#define LED1        LATBbits.LATB6
 */
#define GSM_RX          LATBbits.LATB2
#define GSM_TX          LATBbits.LATB7
#define GSM_RST         LATBbits.LATB9
#define GSM_PWR         LATBbits.LATB8
#define GPS_RX          LATBbits.LATB1
#define GPS_TX          LATBbits.LATB0

#define GSM_RX_TRIS     TRISBbits.TRISB2
#define GSM_RST_TRIS    TRISBbits.TRISB9
#define GSM_PWR_TRIS    TRISBbits.TRISB8
#define GPS_RX_TRIS     TRISBbits.TRISB1
#define GPS_TX_TRIS     TRISBbits.TRISB0


//FRC = 7.37MHz
#define FCY 1842500 //Hz

extern void init_io();

#endif	/* IO_H */

