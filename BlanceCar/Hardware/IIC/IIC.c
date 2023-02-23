#include "stm32f10x.h"
#include "IIC.h"
#include "delay.h"

void IIC_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//��ʹ������IO PORTBʱ�� 
		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;	 // �˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 		 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIO 
	
  GPIO_SetBits(GPIOB,GPIO_Pin_8|GPIO_Pin_9);						 //PB10,PB11 �����	

}

void IIC_Delay(void)
{
	delay_us(2);
}

//����IIC��ʼ�ź�
void IIC_Start(void)
{
	IIC_SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
  IIC_Delay();
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
  IIC_Delay();
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
	IIC_Delay();
}	  

//����IICֹͣ�ź�
void IIC_Stop(void)
{
	IIC_SDA_OUT();//sda�����
	IIC_SDA=0; //STOP:when CLK is high DATA change form low to high
	IIC_SCL=1; 
	IIC_Delay();
	IIC_SDA=1;//����I2C���߽����ź�
						   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	IIC_SDA_IN();      //SDA����Ϊ����  
	IIC_SDA=1;
	IIC_Delay();	   
	IIC_SCL=1;
	IIC_Delay();	 
	while(IIC_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 

//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL=0;
	IIC_SDA_OUT();
	IIC_SDA=0;
	IIC_Delay();
	IIC_SCL=1;
	IIC_Delay();
	IIC_SCL=0;
}

//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	IIC_SDA_OUT();
	IIC_SDA=1;
	IIC_Delay();
	IIC_SCL=1;
	IIC_Delay();
	IIC_SCL=0;
}		
