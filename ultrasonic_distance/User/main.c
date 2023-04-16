#include "stm32f10x.h"                 
#include "delay.h"
#include "timer.h"
#include "usart.h"
#include "oled.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "led.h"
#include "nrf24l01.h"


u32 Distance;                               //���������

int main(void)
{
  u8 tmp_buf[33], mode=0,num=0x30;	
	u16 t=0;
	float pitch,roll,yaw; 		//ŷ����
	short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
	short gyrox,gyroy,gyroz;	//������ԭʼ����
	short temp;					//�¶�	
	
	delay_init();	    	 //��ʱ������ʼ��	  
	delay_ms(100);
	TIM3_Cap_Init(0XFFFF,72-1);	    //��������ʼ��
  IIC_Init();			
	OLED_Init();
//  MPU_Init();					//��ʼ��MPU6050
	LED_Init();		  			//��ʼ����LED
	LED=1;
	BEEP=0;
	NRF24L01_Init();    		//��ʼ��NRF24L01 
	
	while(NRF24L01_Check()) 
  {
	  OLED_ShowString(0,0,"NRF24L01 Error",8);
		delay_ms(200);
	  OLED_ShowString(0,0,"              ",8);
 		delay_ms(200);
	}
	OLED_ShowString(0,0,"NRF24L01 OK",8);
	delay_ms(1000);
	OLED_ShowString(1,1,"           ",8);
	
//	while(mpu_dmp_init())
// 	{
//		OLED_ShowString(1,1,"MPU6050 Error");
//		delay_ms(200);
//		OLED_ShowString(1,1,"             ");
// 		delay_ms(200);
//	}  
	 
//	OLED_ShowString(1,1,"MPU6050 OK");
//	delay_ms(1000);
//	OLED_ShowString(1,1,"          ");
	
	while (1)
	{
		if(mode==0)//RXģʽ
	  {
//			OLED_ShowString(1,1,"NRF24L01 RX_Mode");	
//			OLED_ShowString(2,1,"Received DATA:");	
//			NRF24L01_RX_Mode();		  
//			while(1)
//			{	  		    		    				 
//				if(NRF24L01_RxPacket(tmp_buf)==0)//һ�����յ���Ϣ,����ʾ����.
//				{
//					OLED_ShowChar(3,1,tmp_buf[0]);
//				}
//				else 
//			  {
//					delay_us(100);	   
//				}
//				t++;
//				if(t==10000)//��Լ1s�Ӹı�һ��״̬
//				{
//					t=0;
//					LED=!LED;
//				} 				    
//			};	
//	  }
//		else//TXģʽ
//		{							    
//			OLED_ShowString(1,1,"NRF24L01 TX_Mode");	
//			NRF24L01_TX_Mode();
//      tmp_buf[0]=num;
//			while(1)
//			{	  	
//				tmp_buf[0] = num++;
//				if(NRF24L01_TxPacket(tmp_buf)==TX_OK)
//				{
//					OLED_ShowString(2,1,"Sended DATA:");
//					OLED_ShowChar(3,1,tmp_buf[0]);
//				}
//				else
//				{										   	
//					OLED_ShowString(3,1," "); 	   ;     //�����ʾ			   
//					OLED_ShowString(4,1,"Send Failed "); 
//				};
//				LED=!LED;
//				
//				delay_ms(500);				    
//			};
//		} 				    

		
		
//		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
//		{ 
//			temp=MPU_Get_Temperature();	//�õ��¶�ֵ
//			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ���������
//			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�õ�����������
//			
//			if((t%10)==0)
//			{ 
////-----------------�¶�--------------------------------------				
//				OLED_ShowString(1,1,"Temp");
//				
//				if(temp<0)
//				{
//					OLED_ShowString(1,8,"-");
//					temp=-temp;		//תΪ����
//				}
//				else {
//          OLED_ShowString(1,8," ");
//				}
//                
//				OLED_ShowNum(1,9,temp/100,2);		//��ʾ��������
//				OLED_ShowChar(1,11,'.');		//��ʾ��������					
//				OLED_ShowNum(1,12,temp%10,1);		//��ʾ��������	
//				
////-------------------pitch------------------------------------	
//				OLED_ShowString(2,1,"pitch");				
//				temp=pitch*10;
//				if(temp<0)
//				{
//					OLED_ShowString(2,8,"-");
//					temp=-temp;		//תΪ����
//				}
//				else {
//					OLED_ShowString(2,8," ");
//				}
//				
//        OLED_ShowNum(2,9,temp/10,1);		//��ʾ��������
//				OLED_ShowChar(2,10,'.');		//��ʾ��������					
//				OLED_ShowNum(2,11,temp%10,1);		//��ʾ��������	    
//				
////--------------------roll-----------------------------------				
//				OLED_ShowString(3,1,"roll");				
//				temp=roll*10;
//				if(temp<0)
//				{
//					OLED_ShowString(3,8,"-");
//					temp=-temp;		//תΪ����
//				}else {
//					OLED_ShowString(3,8," ");
//				}
//				
//				OLED_ShowNum(3,9,temp/10,1);		//��ʾ��������
//				OLED_ShowChar(3,10,'.');		//��ʾ��������					
//				OLED_ShowNum(3,11,temp%10,1);		//��ʾ��������	 
//				
////--------------------yaw-----------------------------------
//				OLED_ShowString(4,1,"yaw");
//				temp=yaw*10;
//				if(temp<0)
//				{
//					OLED_ShowString(4,8,"-");
//					temp=-temp;		//תΪ����
//				}else {
//					OLED_ShowString(4,8," ");
//				}
//				OLED_ShowNum(4,9,temp/10,1);		//��ʾ��������
//				OLED_ShowChar(4,10,'.');		//��ʾ��������					
//				OLED_ShowNum(4,11,temp%10,1);		//��ʾ��������	 
//				
//				t=0;
//				LED=!LED;//LED��˸
//			}
		}
//		t++;
	}
}
