#include "stm32f10x.h"
#include "sys.h"

u8 Way_Angle=1;                             //获取角度的算法，1：四元数  2：卡尔曼  3：互补滤波 
float Angle_Balance,Gyro_Balance,Gyro_Turn; //平衡倾角 平衡陀螺仪 转向陀螺仪
u8 delay_50,delay_flag,PID_Send; 						//延时和调参相关变量
float Acceleration_Z;                       //Z轴加速度计  
//float Balance_Kp=0,Balance_Kd=0,Velocity_Kp=16000,Velocity_Ki=80,Turn_Kp=0,Turn_Kd=0;//PID参数（放大100倍）

float Balance_Kp=15000,Balance_Kd=0,Velocity_Kp=0,Velocity_Ki=0,Turn_Kp=0,Turn_Kd=0;//PID参数（放大100倍）

int Motor_Left, Motor_Right;                 //电机PWM变量 应是Motor的 向Moto致敬	
u8 Flag_Stop=1;                 //电机停止标志位和显示标志位  默认停止 显示打开
int Temperature;                            //温度变量


void APP_Show(void)
{    
//  static u8 flag;
//	int Encoder_Left_Show,Encoder_Right_Show,Voltage_Show;
//	Voltage_Show=12;		if(Voltage_Show<0)Voltage_Show=0;if(Voltage_Show>100) Voltage_Show=100;   //对电压数据进行处理
//	Encoder_Right_Show=12; if(Encoder_Right_Show<0) Encoder_Right_Show=-Encoder_Right_Show;			  //对编码器数据就行数据处理便于图形化
//	Encoder_Left_Show=12;  if(Encoder_Left_Show<0) Encoder_Left_Show=-Encoder_Left_Show;
//	flag=!flag;
//	if(PID_Send==1)			//发送PID参数,在APP调参界面显示
//	{
//		printf("{C%d:%d:%d:%d:%d:%d:%d:%d:%d}$",(int)Balance_Kp,(int)Balance_Kd,(int)Velocity_Kp,(int)Velocity_Ki,(int)Turn_Kp,(int)Turn_Kd,0,0,0);//打印到APP上面	
//		PID_Send=0;	
//	}	
//   else	if(flag==0)		// 发送电池电压，速度，角度等参数，在APP首页显示
//		printf("{A%d:%d:%d:%d}$",(int)Encoder_Left_Show,(int)Encoder_Right_Show,(int)Voltage_Show,(int)Angle_Balance); //打印到APP上面
//	 else								//发送小车姿态角，在波形界面显示
//	  printf("{B%d:%d:%d}$",(int)Pitch,(int)Roll,(int)Yaw); //x，y，z轴角度 在APP上面显示波形
																													//可按格式自行增加显示波形，最多可显示五个
}


int main(void)
{	
    u8 res;
    delay_init();
    uart_init(115200);	 //串口初始化为115200
    uart3_init(9600);             	//串口3初始化，用于蓝牙模块
    
    LED_Init();
    LED=1;
    
    Encoder_Init_TIM2();
    Encoder_Init_TIM4();
    Balance_PWM_Init(7200,1); //初始化PWM 10KHZ与电机硬件接口，用于驱动电机
    
    mpu_dmp_init();
    MPU6050_EXTI_Init(); // 初始化由MPU6050中断引脚提供的中断信号

     
    while (1)
	  { 
        Led_Flash(200);
   
		
			 APP_Show();								//发送数据给APP
			 
		
		
		
	}
}
