/***********************************************
公司：轮趣科技（东莞）有限公司
品牌：WHEELTEC
官网：wheeltec.net
淘宝店铺：shop114407458.taobao.com
速卖通: https://minibalance.aliexpress.com/store/4455017
版本：5.7
修改时间：2021-04-29


Brand: WHEELTEC
Website: wheeltec.net
Taobao shop: shop114407458.taobao.com
Aliexpress: https://minibalance.aliexpress.com/store/4455017
Version:5.7
Update：2021-04-29

All rights reserved
***********************************************/
#include "stm32f10x.h"
#include "sys.h"
u8 Way_Angle = 2;													// 获取角度的算法，1：四元数  2：卡尔曼  3：互补滤波
u8 Flag_front, Flag_back, Flag_Left, Flag_Right, Flag_velocity = 2; // 蓝牙遥控相关的变量
u8 Flag_Stop = 1, Flag_Show = 0;									// 电机停止标志位和显示标志位  默认停止 显示打开
int Motor_Left, Motor_Right;										// 电机PWM变量 应是Motor的 向Moto致敬
int Temperature;													// 温度变量
int Voltage;														// 电池电压采样相关的变量
float Angle_Balance, Gyro_Balance, Gyro_Turn;						// 平衡倾角 平衡陀螺仪 转向陀螺仪
u32 Distance;														// 超声波测距
u8 delay_50, delay_flag, PID_Send;									// 延时和调参相关变量
u8 Flag_follow = 0, Flag_avoid = 0;									// 超声波跟随、超声波壁障标志位
float Acceleration_Z;												// Z轴加速度计
// float Balance_Kp=540,Balance_Kd=1.5,Velocity_Kp=220,Velocity_Ki=1.1,Turn_Kp=42,Turn_Kd=-1;//PID参数（放大100倍）
// float Balance_Kp=780*0.6,Balance_Kd=2.3*0.6,Velocity_Kp=1200,Velocity_Ki=6,Turn_Kp=0,Turn_Kd=0;//PID参数（放大100倍）
float Balance_Kp = 600, Balance_Kd = 1.44, Velocity_Kp = 200, Velocity_Ki = 1, Turn_Kp = 0, Turn_Kd = 1; // PID参数（放大100倍）
u8 tmp_buf[33], mode = 0;
u8 temp_val;
u8 play_pause;

// 执行遥控器发过来的命令
void do_action(u8 action, u8 val)
{
	if (action == KEY_1)
	{
		switch (val)
		{
		case LEFT:

			break;
		case LEFT_UP:

			break;
		case UP:

			break;
		case RIGHT_UP:

			break;
		case RIGHT:

			break;
		case RIGHT_DOWN:

			break;
		case DOWN:

			break;
		case LEFT_DOWN:

			break;
		default:
			break;
		}
	}
	else if (action == KEY_2)
	{
		switch (val)
		{
		case KEY_LED:
			LED = !LED;
			break;
		case KEY_BEEP:
			BEEP = !BEEP;
			break;
		case KEY_NEXT:
			USART3_Send(MUSIC_NEXT);
			break;
		case KEY_PRE:
			USART3_Send(MUSIC_PRE);
			break;
		case KEY_UP:
			break;
		case KEY_LEFT:
			break;
		case KEY_RIGHT:
			break;
		case KEY_DOWN:
			break;
		case KEY_CAR_MODE:
			break;
		case KEY_PLAY_PAUSE:
			if (play_pause == 1)
			{
				play_pause = 0;
				USART3_Send(MUSIC_PAUSE);
			}
			else
			{
				play_pause = 1;
				USART3_Send(MUSIC_PLAY);
			}
			break;
		}
	}
	else if (action == KEY_3)
	{
		if (temp_val < val)
		{
			USART3_Send(MUSIC_VOLUME_ADD);
		}
		else if (temp_val > val)
		{
			USART3_Send(MUSIC_VOLUME_SUB);
		}
		temp_val = val;
	}
}

int main(void)
{
	MY_NVIC_PriorityGroupConfig(2); // 设置中断分组
	delay_init();					// 延时函数初始化
	//	JTAG_Set(JTAG_SWD_DISABLE);		// 关闭JTAG接口
	//	JTAG_Set(SWD_ENABLE);			// 打开SWD接口 可以利用主板的SWD接口调试
	LED_Init(); // 初始化与 LED 连接的硬件接口
	//	KEY_Init();						// 按键初始化
	//	MiniBalance_PWM_Init(7199, 0);	// 初始化PWM 10KHZ与电机硬件接口，用于驱动电机
	uart_init(115200); // 串口1初始化
	uart3_init(9600);  // 串口3初始化，用于蓝牙模块
	//	Encoder_Init_TIM2();			// 编码器接口
	//	Encoder_Init_TIM4();			// 初始化编码器4
	//	Adc_Init();						// adc初始化
	IIC_Init();	 // IIC初始化
	OLED_Init(); // OLED初始化
	//	MPU6050_initialize();			// MPU6050初始化
	//	DMP_Init();						// 初始化DMP
	// TIM3_Cap_Init(0XFFFF,72-1);	    //超声波初始化

	NRF24L01_Init(); // 初始化NRF24L01

	while (NRF24L01_Check())
	{
		OLED_ShowString(0, 0, "NRF24L01 Error", 8, 1);
		delay_ms(200);
		OLED_ShowString(0, 0, "             ", 8, 1);
		delay_ms(200);
	}
	OLED_ShowString(0, 0, "           ", 8, 1);

	// 音乐模块初始化
	delay_ms(1000);
	USART3_Send(MUSIC_PLAY);
	delay_ms(100);
	// MiniBalance_EXTI_Init(); // MPU6050 5ms定时中断初始化，节省定时器资源，减少cpu负担

		NRF24L01_RX_Mode();
		OLED_ShowString(0, 0, "NRF24L01 RX_Mode", 8, 1);

		while (1)
		{
			OLED_ShowString(0, 8, "Receive DATA:", 8, 1);
			if (NRF24L01_RxPacket(tmp_buf) == 0) // 一旦接收到信息,则显示出来.
			{
				OLED_ShowNumber(0, 16, tmp_buf[0], 8, 2, 1);
				OLED_ShowNumber(10, 16, tmp_buf[1], 8, 2, 1);
				do_action(tmp_buf[0], tmp_buf[1]);
			}

	}
}
