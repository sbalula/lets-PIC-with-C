#ifndef UART2_H
#define	UART2_H

#define printf2(...) __C30_UART = 2; printf(__VA_ARGS__)

extern unsigned int str_pos2; //auxiliary UART config variables
extern char RXbuffer2[80];
extern int erase;

extern void init_uart2();
extern void __attribute__((__interrupt__,auto_psv)) _U2RXInterrupt(void);
extern void clear_RXbuffer2();
#endif	/* UART1_H */

