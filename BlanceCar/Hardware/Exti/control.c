#include "control.h"
#include "inv_mpu.h"
#include "mpu6050.h"

float Pitch,Roll,Yaw; 

/**************************************************************************
Function: Control function
Input   : none
Output  : none
函数功能：所有的控制代码都在这里面
         5ms外部中断由MPU6050的INT引脚触发
         严格保证采样和数据处理的时间同步	
入口参数：无
返回  值：无				 
**************************************************************************/
void EXTI15_10_IRQHandler(void) 
{   

	int Encoder_Left,Encoder_Right;             					//左右编码器的脉冲计数
	int Balance_Pwm,Velocity_Pwm,Turn_Pwm;		  					//平衡环PWM变量，速度环PWM变量，转向环PWM变		
	   
    EXTI->PR=1<<12;                           					//清除中断标志位 

    Get_Angle(Way_Angle);                     					//更新姿态，5ms一次，更高的采样频率可以改善卡尔曼滤波和互补滤波的效果
    Encoder_Left=-Read_Encoder(2);            					//读取左轮编码器的值，前进为正，后退为负
    Encoder_Right=-Read_Encoder(4);    
//    printf("\r\nEncoder_Left = %d\r\n",Encoder_Left);
//    printf("Encoder_Right = %d\r\n",Encoder_Right);

    Balance_Pwm=Balance(Angle_Balance,Gyro_Balance);    //平衡PID控制 Gyro_Balance平衡角速度极性：前倾为正，后倾为负
    Velocity_Pwm=Velocity(Encoder_Left,Encoder_Right);  //速度环PID控制	记住，速度反馈是正反馈，就是小车快的时候要慢下来就需要再跑快一点
    Turn_Pwm=Turn(Gyro_Turn);														//转向环PID控制     
    
    Motor_Left=Balance_Pwm+Velocity_Pwm+Turn_Pwm;       //计算左轮电机最终PWM
    Motor_Right=Balance_Pwm+Velocity_Pwm-Turn_Pwm;      //计算右轮电机最终PWM
                                                                                                            //PWM值正数使小车前进，负数使小车后退
    Motor_Left=PWM_Limit(Motor_Left,6900,-6900);
    Motor_Right=PWM_Limit(Motor_Right,6900,-6900);			//PWM限幅
    
    printf("\r\nMotor_Left = %d  Motor_Right = %d \r\n",Motor_Left,Motor_Right);
    
//    if(Pick_Up(Acceleration_Z,Angle_Balance,Encoder_Left,Encoder_Right))//检查是否小车被拿起
//        Flag_Stop=1;	                           					//如果被拿起就关闭电机
//    if(Put_Down(Angle_Balance,Encoder_Left,Encoder_Right))//检查是否小车被放下
//        Flag_Stop=0;	                           					//如果被放下就启动电机
//    Choose(Encoder_Left,Encoder_Right);									//转动右轮选择小车模式
    if(Turn_Off(Angle_Balance)==0)     					//如果不存在异常
        Set_Pwm(Motor_Left,Motor_Right);         					//赋值给PWM寄存器  	  
} 

/**************************************************************************
Function: Vertical PD control
Input   : Angle:angle；Gyro：angular velocity
Output  : balance：Vertical control PWM
函数功能：直立PD控制		
入口参数：Angle:角度；Gyro：角速度
返回  值：balance：直立控制PWM
**************************************************************************/	
int Balance(float Angle,float Gyro)
{  
   float Angle_bias,Gyro_bias;
	 int balance;
	 Angle_bias=Middle_angle-Angle;                       				//求出平衡的角度中值 和机械相关
	 Gyro_bias=0-Gyro; 
	 balance=-Balance_Kp/100*Angle_bias-Gyro_bias*Balance_Kd/100; //计算平衡控制的电机PWM  PD控制   kp是P系数 kd是D系数 
	 return balance;
}


/**************************************************************************
Function: Speed PI control
Input   : encoder_left：Left wheel encoder reading；encoder_right：Right wheel encoder reading
Output  : Speed control PWM
函数功能：速度控制PWM		
入口参数：encoder_left：左轮编码器读数；encoder_right：右轮编码器读数
返回  值：速度控制PWM
**************************************************************************/
//修改前进后退速度，请修改Target_Velocity，比如，改成60就比较慢了
int Velocity(int encoder_left,int encoder_right)
{  
    static float velocity,Encoder_Least,Encoder_bias,Movement;
	static float Encoder_Integral /*,Target_Velocity*/;

		
   //================速度PI控制器=====================//	
		Encoder_Least =0-(encoder_left+encoder_right);                    //获取最新速度偏差=目标速度（此处为零）-测量速度（左右编码器之和） 
		Encoder_bias *= 0.84;		                                          //一阶低通滤波器       
		Encoder_bias += Encoder_Least*0.16;	                              //一阶低通滤波器，减缓速度变化 
		Encoder_Integral +=Encoder_bias;                                  //积分出位移 积分时间：10ms
		Encoder_Integral=Encoder_Integral+Movement;                       //接收遥控器数据，控制前进后退
		if(Encoder_Integral>10000)  	Encoder_Integral=10000;             //积分限幅
		if(Encoder_Integral<-10000)	  Encoder_Integral=-10000;            //积分限幅	
		velocity=-Encoder_bias*Velocity_Kp/100-Encoder_Integral*Velocity_Ki/100;     //速度控制	
		if(Turn_Off(Angle_Balance)==1||Flag_Stop==1) Encoder_Integral=0;//电机关闭后清除积分
	  return velocity;
}

/**************************************************************************
Function: Turn control
Input   : Z-axis angular velocity
Output  : Turn control PWM
函数功能：转向控制 
入口参数：Z轴陀螺仪
返回  值：转向控制PWM
作    者：轮趣科技（东莞）有限公司
**************************************************************************/
int Turn(float gyro)
{

	 static float Turn_Target/*,Turn_Amplitude=54*/;
	 float Kp=Turn_Kp,Kd;			//修改转向速度，请修改Turn_Amplitude即可
//	//===================遥控左右旋转部分=================//
//	 if(1==Flag_Left)	        Turn_Target=-Turn_Amplitude/Flag_velocity;
//	 else if(1==Flag_Right)	  Turn_Target=Turn_Amplitude/Flag_velocity; 
//	 else Turn_Target=0;
//	 if(1==Flag_front||1==Flag_back)  Kd=Turn_Kd;        
//	 else Kd=0;   //转向的时候取消陀螺仪的纠正 有点模糊PID的思想
  //===================转向PD控制器=================//
	 return Turn_Target*Kp/100+gyro*Kd/100;//结合Z轴陀螺仪进行PD控制
							 				 //转向环PWM右转为正，左转为负
}


/**************************************************************************
Function: Assign to PWM register
Input   : motor_left：Left wheel PWM；motor_right：Right wheel PWM
Output  : none
函数功能：赋值给PWM寄存器
入口参数：左轮PWM、右轮PWM
返回  值：无
**************************************************************************/
void Set_Pwm(int motor_left,int motor_right)
{
    if(motor_left>0) 
    {    
        BIN1=1;
        BIN2=0; //前进 
    }
	else 
    {       
        BIN1=0;
		BIN2=1; //后退
    }
    PWMB=myabs(motor_left);	
    
    if(motor_right>0) 
    {	
        AIN2=1;
        AIN1=0;	//前进
    }
	else 	        
    {
        AIN2=0;
		AIN1=1; //后退
    }
	PWMA=myabs(motor_right);
}
/**************************************************************************
Function: PWM limiting range
Input   : IN：Input  max：Maximum value  min：Minimum value
Output  : Output
函数功能：限制PWM赋值 
入口参数：IN：输入参数  max：限幅最大值  min：限幅最小值
返回  值：限幅后的值
**************************************************************************/
int PWM_Limit(int IN,int max,int min)
{
	int OUT = IN;
	if(OUT>max) OUT = max;
	if(OUT<min) OUT = min;
	return OUT;
}

	
/**************************************************************************
Function: Get angle
Input   : way：The algorithm of getting angle 1：DMP  2：kalman  3：Complementary filtering
Output  : none
函数功能：获取角度	
入口参数：way：获取角度的算法 1：DMP  2：卡尔曼 3：互补滤波
返回  值：无
**************************************************************************/	
void Get_Angle(u8 way)
{ 
	float Accel_Y,Accel_Z,Accel_X,Accel_Angle_x,Accel_Angle_y,Gyro_X,Gyro_Z,Gyro_Y;
	Temperature = MPU_Get_Temperature();      //读取MPU6050内置温度传感器数据，近似表示主板温度。
	if(way==1)                           //DMP的读取在数据采集中断读取，严格遵循时序要求
	{	
		  mpu_dmp_get_data(&Pitch,&Roll,&Yaw);                      	 //读取加速度、角速度、倾角
      printf("Pitch = %f  Roll = %f  Yaw = %f \r\n", Pitch,Roll,Yaw);
		  Angle_Balance=Pitch;             	 //更新平衡倾角,前倾为正，后倾为负
		  Gyro_Balance=gyro[0];              //更新平衡角速度,前倾为正，后倾为负
		  Gyro_Turn=gyro[2];                 //更新转向角速度
		  Acceleration_Z=accel[2];           //更新Z轴加速度计
	}			
	else
	{
		Gyro_X=(MPU_Read_Byte(MPU_GYRO_XOUTH_REG)<<8)+MPU_Read_Byte(MPU_GYRO_XOUTL_REG);    //读取X轴陀螺仪
		Gyro_Y=(MPU_Read_Byte(MPU_GYRO_YOUTH_REG)<<8)+MPU_Read_Byte(MPU_GYRO_YOUTL_REG);    //读取Y轴陀螺仪
		Gyro_Z=(MPU_Read_Byte(MPU_GYRO_ZOUTH_REG)<<8)+MPU_Read_Byte(MPU_GYRO_ZOUTL_REG);    //读取Z轴陀螺仪
		Accel_X=(MPU_Read_Byte(MPU_ACCEL_XOUTH_REG)<<8)+MPU_Read_Byte(MPU_ACCEL_XOUTL_REG); //读取X轴加速度计
		Accel_Y=(MPU_Read_Byte(MPU_ACCEL_YOUTH_REG)<<8)+MPU_Read_Byte(MPU_ACCEL_YOUTL_REG); //读取X轴加速度计
		Accel_Z=(MPU_Read_Byte(MPU_ACCEL_ZOUTH_REG)<<8)+MPU_Read_Byte(MPU_ACCEL_ZOUTL_REG); //读取Z轴加速度计
		if(Gyro_X>32768)  Gyro_X-=65536;                 //数据类型转换  也可通过short强制类型转换
		if(Gyro_Y>32768)  Gyro_Y-=65536;                 //数据类型转换  也可通过short强制类型转换
		if(Gyro_Z>32768)  Gyro_Z-=65536;                 //数据类型转换
		if(Accel_X>32768) Accel_X-=65536;                //数据类型转换
		if(Accel_Y>32768) Accel_Y-=65536;                //数据类型转换
		if(Accel_Z>32768) Accel_Z-=65536;                //数据类型转换
		Gyro_Balance=-Gyro_X;                            //更新平衡角速度
		Accel_Angle_x=atan2(Accel_Y,Accel_Z)*180/PI;     //计算倾角，转换单位为度	
		Accel_Angle_y=atan2(Accel_X,Accel_Z)*180/PI;     //计算倾角，转换单位为度
		Gyro_X=Gyro_X/16.4;                              //陀螺仪量程转换，量程±2000°/s对应灵敏度16.4，可查手册
		Gyro_Y=Gyro_Y/16.4;                              //陀螺仪量程转换	
		if(Way_Angle==2)		  	
		{
			 Pitch = -Kalman_Filter_x(Accel_Angle_x,Gyro_X);//卡尔曼滤波
			 Roll = -Kalman_Filter_y(Accel_Angle_y,Gyro_Y);
            
             printf("Pitch = %f  Roll = %f  Yaw = %f \r\n", Pitch,Roll,Yaw);
		}
		else if(Way_Angle==3) 
		{  
			 Pitch = -Complementary_Filter_x(Accel_Angle_x,Gyro_X);//互补滤波
			 Roll = -Complementary_Filter_y(Accel_Angle_y,Gyro_Y);
            printf("Pitch = %f  Roll = %f  Yaw = %f \r\n", Pitch,Roll,Yaw);
		}
		Angle_Balance=Pitch;                              //更新平衡倾角
		Gyro_Turn=Gyro_Z;                                 //更新转向角速度
		Acceleration_Z=Accel_Z;                           //更新Z轴加速度计	
	}
}
/**************************************************************************
Function: Absolute value function
Input   : a：Number to be converted
Output  : unsigned int
函数功能：绝对值函数
入口参数：a：需要计算绝对值的数
返回  值：无符号整型
**************************************************************************/	
int myabs(int a)
{ 		   
	int temp;
	if(a<0)  temp=-a;  
	else temp=a;
	return temp;
}
/**************************************************************************
Function: Check whether the car is picked up
Input   : Acceleration：Z-axis acceleration；Angle：The angle of balance；encoder_left：Left encoder count；encoder_right：Right encoder count
Output  : 1：picked up  0：No action
函数功能：检测小车是否被拿起
入口参数：Acceleration：z轴加速度；Angle：平衡的角度；encoder_left：左编码器计数；encoder_right：右编码器计数
返回  值：1:小车被拿起  0：小车未被拿起
**************************************************************************/
int Pick_Up(float Acceleration,float Angle,int encoder_left,int encoder_right)
{ 		   
	 static u16 flag,count0,count1,count2;
	 if(flag==0)                                                      //第一步
	 {
			if(myabs(encoder_left)+myabs(encoder_right)<30)               //条件1，小车接近静止
			count0++;
			else 
			count0=0;		
			if(count0>10)				
			flag=1,count0=0; 
	 } 
	 if(flag==1)                                                      //进入第二步
	 {
			if(++count1>200)       count1=0,flag=0;                       //超时不再等待2000ms，返回第一步
			if(Acceleration>26000&&(Angle>(-20+Middle_angle))&&(Angle<(20+Middle_angle)))   //条件2，小车是在0度附近被拿起
			flag=2; 
	 } 
	 if(flag==2)                                                       //第三步
	 {
		  if(++count2>100)       count2=0,flag=0;                        //超时不再等待1000ms
	    if(myabs(encoder_left+encoder_right)>70)                       //条件3，小车的轮胎因为正反馈达到最大的转速   
      {
				flag=0;                                                                                     
				return 1;                                                    //检测到小车被拿起
			}
	 }
	return 0;
}

/**************************************************************************
Function: Check whether the car is lowered
Input   : The angle of balance；Left encoder count；Right encoder count
Output  : 1：put down  0：No action
函数功能：检测小车是否被放下
入口参数：平衡角度；左编码器读数；右编码器读数
返回  值：1：小车放下   0：小车未放下
**************************************************************************/
int Put_Down(float Angle,int encoder_left,int encoder_right)
{ 		   
	 static u16 flag,count;	 
	 if(Flag_Stop==0)                     //防止误检      
			return 0;	                 
	 if(flag==0)                                               
	 {
			if(Angle>(-10+Middle_angle)&&Angle<(10+Middle_angle)&&encoder_left==0&&encoder_right==0) //条件1，小车是在0度附近的
			flag=1; 
	 } 
	 if(flag==1)                                               
	 {
		  if(++count>50)                     //超时不再等待 500ms
		  {
				count=0;flag=0;
		  }
	    if(encoder_left>3&&encoder_right>3&&encoder_left<40&&encoder_right<40) //条件2，小车的轮胎在未上电的时候被人为转动  
      {
				flag=0;
				flag=0;
				return 1;                         //检测到小车被放下
			}
	 }
	return 0;
}

/**************************************************************************
Function: If abnormal, turn off the motor
Input   : angle：Car inclination；voltage：Voltage
Output  : 1：abnormal；0：normal
函数功能：异常关闭电机		
入口参数：angle：小车倾角；voltage：电压
返回  值：1：异常  0：正常
**************************************************************************/	
u8 Turn_Off(float angle/*, int voltage*/)
{
	u8 temp;
	if(angle<-40||angle>40/*||1==Flag_Stop||voltage<1110*/)//电池电压低于11.1V关闭电机
	{	                                                 //倾角大于40度关闭电机
		temp=1;                                          //Flag_Stop置1，即单击控制关闭电机
		AIN1=0;                                            
		AIN2=0;
		BIN1=0;
		BIN2=0;
	}
	else
		temp=0;
	return temp;			
}

/**************************************************************************
Function: Select car running mode
Input   : encoder_left：Left wheel encoder reading；encoder_right：Right wheel encoder reading
Output  : none
函数功能：选择小车运行模式
入口参数：encoder_left：左编码器读数  encoder_right：右编码器读数
返回  值：无
**************************************************************************/
void Choose(int encoder_left,int encoder_right)
{
	//TODO 
}



