/***********************************************
��˾����Ȥ�Ƽ�����ݸ�����޹�˾
Ʒ�ƣ�WHEELTEC
������wheeltec.net
�Ա����̣�shop114407458.taobao.com 
����ͨ: https://minibalance.aliexpress.com/store/4455017
�汾��5.7
�޸�ʱ�䣺2021-04-29

 
Brand: WHEELTEC
Website: wheeltec.net
Taobao shop: shop114407458.taobao.com 
Aliexpress: https://minibalance.aliexpress.com/store/4455017
Version:5.7
Update��2021-04-29

All rights reserved
***********************************************/
#include "stm32f10x.h"
#include "sys.h"
u8 Way_Angle=2;                             //��ȡ�Ƕȵ��㷨��1����Ԫ��  2��������  3�������˲� 
u8 Flag_front,Flag_back,Flag_Left,Flag_Right,Flag_velocity=2; //����ң����صı���
u8 Flag_Stop=1,Flag_Show=0;                 //���ֹͣ��־λ����ʾ��־λ  Ĭ��ֹͣ ��ʾ��
int Motor_Left,Motor_Right;                 //���PWM���� Ӧ��Motor�� ��Moto�¾�	
int Temperature;                            //�¶ȱ���
int Voltage;                                //��ص�ѹ������صı���
float Angle_Balance,Gyro_Balance,Gyro_Turn; //ƽ����� ƽ�������� ת��������
u32 Distance;                               //���������
u8 delay_50,delay_flag,PID_Send; 						//��ʱ�͵�����ر���
u8 Flag_follow=0,Flag_avoid=0;							//���������桢���������ϱ�־λ
float Acceleration_Z;                       //Z����ٶȼ�  
float Balance_Kp=540,Balance_Kd=1.5,Velocity_Kp=220,Velocity_Ki=1.1,Turn_Kp=42,Turn_Kd=-1;//PID�������Ŵ�100����
//float Balance_Kp=780*0.6,Balance_Kd=2.3*0.6,Velocity_Kp=1200,Velocity_Ki=6,Turn_Kp=0,Turn_Kd=0;//PID�������Ŵ�100����
//float Balance_Kp=900,Balance_Kd=2.5,Velocity_Kp=0,Velocity_Ki=0,Turn_Kp=0,Turn_Kd=0;//PID�������Ŵ�100����
int main(void)
{ 
//  MY_NVIC_PriorityGroupConfig(2);	//�����жϷ���
	delay_init();	    	            //��ʱ������ʼ��	
	JTAG_Set(JTAG_SWD_DISABLE);     //�ر�JTAG�ӿ�
	JTAG_Set(SWD_ENABLE);           //��SWD�ӿ� �������������SWD�ӿڵ���
	LED_Init();                     //��ʼ���� LED ���ӵ�Ӳ���ӿ�
	KEY_Init();                     //������ʼ��
	MiniBalance_PWM_Init(7199,0);   //��ʼ��PWM 10KHZ����Ӳ���ӿڣ������������
	uart_init(115200);	            //����1��ʼ��
	uart3_init(9600);             	//����3��ʼ������������ģ��
	Encoder_Init_TIM2();            //�������ӿ�
	Encoder_Init_TIM4();            //��ʼ��������4
	Adc_Init();                     //adc��ʼ��
	IIC_Init();                     //IIC��ʼ��
	OLED_Init();                    //OLED��ʼ��	    
	MPU6050_initialize();           //MPU6050��ʼ��	
	DMP_Init();                     //��ʼ��DMP 
  TIM3_Cap_Init(0XFFFF,72-1);	    //��������ʼ��
	MiniBalance_EXTI_Init();        //MPU6050 5ms��ʱ�жϳ�ʼ������ʡ��ʱ����Դ������cpu����
	//OLED_ShowString(0,0,"NRF24L01 Error");
	while(1)
	{
//		if(Flag_Show==0)          		//ʹ��MiniBalance APP��OLED��ʾ��
//		{
//			 APP_Show();								//�������ݸ�APP
//			 oled_show();          			//��ʾ����
//		}
//		else                      		//ʹ��MiniBalance��λ�� ��λ��ʹ�õ�ʱ����Ҫ�ϸ��ʱ�򣬹ʴ�ʱ�ر�app��ز��ֺ�OLED��ʾ��
//		{
//			 DataScope();          			//����MiniBalance��λ��
//		}	
//		delay_flag=1;	
//		delay_50=0;
//		while(delay_flag);	     			//ʾ������Ҫ50ms	�߾�����ʱ��delay����������Ҫ�󣬹�ʹ��MPU6050�ж��ṩ50ms��ʱ
	}
}

