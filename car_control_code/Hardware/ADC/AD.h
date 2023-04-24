#ifndef __AD_H
#define __AD_H

extern uint16_t AD_Value[2];

#define LEFT_1 1
#define LEFT_2 2
#define RIGHT_1 3
#define RIGHT_2 4
#define UP_1 5
#define UP_2 6
#define DOWN_1 7
#define DOWN_2 8
#define CENTER 0

void AD_Init(void);
int Vertical(void);
int Horizontal(void);
#endif
