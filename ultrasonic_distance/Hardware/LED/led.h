#ifndef __LED_H
#define __LED_H	 


#define LED PCout(13) // PC13

void LED_Init(void);

void LED_ON(void);
void LED_OFF(void);  

#endif
