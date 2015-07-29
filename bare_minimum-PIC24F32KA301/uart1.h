#ifndef UART1_H
#define	UART1_H


#define printf1(...) __C30_UART = 1; printf(__VA_ARGS__)

extern unsigned int str_pos1; //auxiliary UART config variables
extern char RXbuffer1[80];

extern void init_uart1();
extern void __attribute__((__interrupt__,auto_psv)) _U1RXInterrupt(void);
extern void clear_RXbuffer1();

#endif	/* UART1_H */

