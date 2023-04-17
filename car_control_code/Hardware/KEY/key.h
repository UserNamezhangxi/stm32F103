#ifndef __KEY_H
#define __KEY_H

#include "sys.h"

#define NO_KEY 0

#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_LEFT 3
#define KEY_RIGHT 4

/************* “Ù¿÷øÿ÷∆ ***********/
#define KEY_PRE 5
#define KEY_NEXT 6
#define KEY_PLAY_PAUSE 7
#define KEY_LED 8
#define KEY_BEEP 9

#define KEY_CAR_MODE 10

void Key_Init(void);
u8 Key_GetNum(void);

#endif
