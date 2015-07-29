#include <p24F32KA301.h>
#include "io.h"

void init_io()
{
    ANSA = 0;
    ANSB = 0;
/*
    LCD_ce          =   1;
    LCD_rst         =   1;
    LCD_dc          =   1;
    LCD_din         =   0;
    LCD_clk         =   0;
    LED1            =   1;
 */
    GSM_RST = 0;
    GSM_PWR = 0;


 /*
    LCD_ce_TRIS     =   0;
    LCD_rst_TRIS    =   0;
    LCD_dc_TRIS     =   0;
    LCD_din_TRIS    =   0;
    LCD_clk_TRIS    =   0;
    LED1_TRIS       =   0;
 */
    GSM_RX_TRIS     =   1;
    GSM_RST_TRIS    =   0;
    GSM_PWR_TRIS    =   0;
    GPS_RX_TRIS  = 1;
    GPS_TX_TRIS  = 0;
}