#include "stm32f10x.h"
#include "sys.h"

u8 Flag_Stop =1 ;                 	//µç»úÍ£Ö¹±êÖ¾Î» Ä¬ÈÏÍ£Ö¹
float Angle_Balance,Gyro_Balance; //Æ½ºâÇã½Ç Æ½ºâÍÓÂÝÒÇ
int Encoder_Left,Encoder_Right;   //×óÓÒ±àÂëÆ÷µÄÂö³å¼ÆÊý


void APP_Show(void)
{    

}

void mpu6050show() {
		short temp;					//ÎÂ¶È	
//-------------------pitch------------------------------------	
		OLED_ShowString(2,1,"pitch");				
		temp=Pitch*10;
		if(temp<0)
		{
			OLED_ShowString(2,8,"-");
			temp=-temp;		//×ªÎªÕýÊý
		}
		else {
			OLED_ShowString(2,8," ");
		}
		
		OLED_ShowNum(2,9,temp/10,1);		//ÏÔÊ¾ÕûÊý²¿·Ö
		OLED_ShowChar(2,10,'.');		//ÏÔÊ¾ÕûÊý²¿·Ö					
		OLED_ShowNum(2,11,temp%10,1);		//ÏÔÊ¾ÕûÊý²¿·Ö	 
				
//--------------------roll-----------------------------------				
				OLED_ShowString(3,1,"roll");				
				temp=Roll*10;
				if(temp<0)
				{
					OLED_ShowString(3,8,"-");
					temp=-temp;		//×ªÎªÕýÊý
				}else {
					OLED_ShowString(3,8," ");
				}
				
				OLED_ShowNum(3,9,temp/10,1);		//ÏÔÊ¾ÕûÊý²¿·Ö
				OLED_ShowChar(3,10,'.');		//ÏÔÊ¾ÕûÊý²¿·Ö					
				OLED_ShowNum(3,11,temp%10,1);		//ÏÔÊ¾ÕûÊý²¿·Ö	 
				
//--------------------yaw-----------------------------------
				OLED_ShowString(4,1,"yaw");
				temp=Yaw*10;
				if(temp<0)
				{
					OLED_ShowString(4,8,"-");
					temp=-temp;		//×ªÎªÕýÊý
				}else {
					OLED_ShowString(4,8," ");
				}
				OLED_ShowNum(4,9,temp/10,1);		//ÏÔÊ¾ÕûÊý²¿·Ö
				OLED_ShowChar(4,10,'.');		//ÏÔÊ¾ÕûÊý²¿·Ö					
				OLED_ShowNum(4,11,temp%10,1);		//ÏÔÊ¾ÕûÊý²¿·Ö	 
}


int main(void)
{	
	  u16 res;
		MY_NVIC_PriorityGroupConfig(2);	
    delay_init();
    uart_init(115200);	 //串口初始化为115200
    uart3_init(9600);             	//串口3初始化，用于蓝牙模块
    Adc_Init();
    LED_Init();
    IIC_Init();			
	  OLED_Init();
    Encoder_Init_TIM2();
    Encoder_Init_TIM4();
    Balance_PWM_Init(7200,1); //初始化PWM 10KHZ与电机硬件接口，用于驱动电机
    MPU_Init();
		while(mpu_dmp_init())
		{
			OLED_ShowString(1,1,"MPU6050 Error");
			delay_ms(200);
			OLED_ShowString(1,1,"             ");
			delay_ms(200);
		}  

		OLED_ShowString(1,1,"MPU6050 OK");
		delay_ms(1000);
		OLED_ShowString(1,1,"          ");
    MPU6050_EXTI_Init(); // 初始化由MPU6050中断引脚提供的中断信号
		
     
    while (1)
	  { 
      res = Get_battery_volt();
		 	OLED_ShowNum(1, 1, res, 5);
      mpu6050show();
			
		}
}

