#ifndef __IIC_H
#define __IIC_H	 
#include "sys.h"

#define IIC_SDA_IN()  {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=8<<4;}
#define IIC_SDA_OUT() {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=3<<4;}

//IO²Ù×÷º¯Êý	 
#define IIC_SCL    PBout(8) 		//SCL
#define IIC_SDA    PBout(9) 		//SDA	 
#define IIC_READ_SDA   PBin(9) 		//ÊäÈëSDA 

void IIC_Init(void);
void IIC_Stop(void);
void IIC_Start(void);
void IIC_Delay(void);
u8 IIC_Wait_Ack(void);
void IIC_Ack(void);
void IIC_NAck(void);




#endif

