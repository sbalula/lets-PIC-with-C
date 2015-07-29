#ifndef GSM_H
#define	GSM_H

#define WAIT(x) if(wait_for1((char * ) x, 20000)) return 1
//#define WAIT(x) delay_ms(x)
extern unsigned int gsm_state;

extern int init_gsm();
extern int sms_send(char* number, char* text);

extern int wait_for1(char * thing, unsigned long b);


#endif	/* GSM_H */

