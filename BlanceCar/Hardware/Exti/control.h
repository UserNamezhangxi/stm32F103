#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"

#define PI 3.14159265							//PI圆周率
#define Control_Frequency  200.0	//编码器读取频率
#define Diameter_67  67.0 				//轮子直径67mm 
#define EncoderMultiples   4.0 		//编码器倍频数
#define Encoder_precision  13.0 	//编码器精度 13线
#define Reduction_Ratio  30.0			//减速比30
#define Perimeter  210.4867 			//周长，单位mm

#define Middle_angle 0
int EXTI15_10_IRQHandler(void);
int Balance(float angle,float gyro);
int Velocity(int encoder_left,int encoder_right);
void Set_Pwm(int motor_left,int motor_right);
void Key(void);
int PWM_Limit(int IN,int max,int min);
u8 Turn_Off(float angle);
void Get_Angle(void);
int myabs(int a);
#endif
