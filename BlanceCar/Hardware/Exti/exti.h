#ifndef __EXTI_H
#define __EXTI_H	 
#include "sys.h"
#define INT PAin(12)   //PA12连接到MPU6050的中断引脚
void MPU6050_EXTI_Init(void);	//外部中断初始化		 					    
#endif

