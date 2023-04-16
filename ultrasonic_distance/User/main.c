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


u32 Distance;                               //超声波测距

int main(void)
{
  u8 tmp_buf[33], mode=0,num=0x30;	
	u16 t=0;
	float pitch,roll,yaw; 		//欧拉角
	short aacx,aacy,aacz;		//加速度传感器原始数据
	short gyrox,gyroy,gyroz;	//陀螺仪原始数据
	short temp;					//温度	
	
	delay_init();	    	 //延时函数初始化	  
	delay_ms(100);
	TIM3_Cap_Init(0XFFFF,72-1);	    //超声波初始化
  IIC_Init();			
	OLED_Init();
//  MPU_Init();					//初始化MPU6050
	LED_Init();		  			//初始化与LED
	LED=1;
	BEEP=0;
	NRF24L01_Init();    		//初始化NRF24L01 
	
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
		if(mode==0)//RX模式
	  {
//			OLED_ShowString(1,1,"NRF24L01 RX_Mode");	
//			OLED_ShowString(2,1,"Received DATA:");	
//			NRF24L01_RX_Mode();		  
//			while(1)
//			{	  		    		    				 
//				if(NRF24L01_RxPacket(tmp_buf)==0)//一旦接收到信息,则显示出来.
//				{
//					OLED_ShowChar(3,1,tmp_buf[0]);
//				}
//				else 
//			  {
//					delay_us(100);	   
//				}
//				t++;
//				if(t==10000)//大约1s钟改变一次状态
//				{
//					t=0;
//					LED=!LED;
//				} 				    
//			};	
//	  }
//		else//TX模式
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
//					OLED_ShowString(3,1," "); 	   ;     //清空显示			   
//					OLED_ShowString(4,1,"Send Failed "); 
//				};
//				LED=!LED;
//				
//				delay_ms(500);				    
//			};
//		} 				    

		
		
//		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
//		{ 
//			temp=MPU_Get_Temperature();	//得到温度值
//			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
//			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据
//			
//			if((t%10)==0)
//			{ 
////-----------------温度--------------------------------------				
//				OLED_ShowString(1,1,"Temp");
//				
//				if(temp<0)
//				{
//					OLED_ShowString(1,8,"-");
//					temp=-temp;		//转为正数
//				}
//				else {
//          OLED_ShowString(1,8," ");
//				}
//                
//				OLED_ShowNum(1,9,temp/100,2);		//显示整数部分
//				OLED_ShowChar(1,11,'.');		//显示整数部分					
//				OLED_ShowNum(1,12,temp%10,1);		//显示整数部分	
//				
////-------------------pitch------------------------------------	
//				OLED_ShowString(2,1,"pitch");				
//				temp=pitch*10;
//				if(temp<0)
//				{
//					OLED_ShowString(2,8,"-");
//					temp=-temp;		//转为正数
//				}
//				else {
//					OLED_ShowString(2,8," ");
//				}
//				
//        OLED_ShowNum(2,9,temp/10,1);		//显示整数部分
//				OLED_ShowChar(2,10,'.');		//显示整数部分					
//				OLED_ShowNum(2,11,temp%10,1);		//显示整数部分	    
//				
////--------------------roll-----------------------------------				
//				OLED_ShowString(3,1,"roll");				
//				temp=roll*10;
//				if(temp<0)
//				{
//					OLED_ShowString(3,8,"-");
//					temp=-temp;		//转为正数
//				}else {
//					OLED_ShowString(3,8," ");
//				}
//				
//				OLED_ShowNum(3,9,temp/10,1);		//显示整数部分
//				OLED_ShowChar(3,10,'.');		//显示整数部分					
//				OLED_ShowNum(3,11,temp%10,1);		//显示整数部分	 
//				
////--------------------yaw-----------------------------------
//				OLED_ShowString(4,1,"yaw");
//				temp=yaw*10;
//				if(temp<0)
//				{
//					OLED_ShowString(4,8,"-");
//					temp=-temp;		//转为正数
//				}else {
//					OLED_ShowString(4,8," ");
//				}
//				OLED_ShowNum(4,9,temp/10,1);		//显示整数部分
//				OLED_ShowChar(4,10,'.');		//显示整数部分					
//				OLED_ShowNum(4,11,temp%10,1);		//显示整数部分	 
//				
//				t=0;
//				LED=!LED;//LED闪烁
//			}
		}
//		t++;
	}
}
