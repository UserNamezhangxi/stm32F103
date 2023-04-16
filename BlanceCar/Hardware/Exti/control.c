
#include "control.h"


int EXTI15_10_IRQHandler(void) 
{    
	 static u8 Flag_Target;						//¿ØÖÆº¯ÊýÏà¹Ø±äÁ¿£¬Ìá¹©10ms»ù×¼
   int Balance_Pwm,Velocity_Pwm;		//Æ½ºâ»·PWM±äÁ¿£¬ËÙ¶È»·PWM±äÁ¿
	 int Motor_Left,Motor_Right;      //µç»úPWM±äÁ¿ Ó¦ÊÇMotorµÄ ÏòMotoÖÂ¾´	
	 if(INT==0)		
	 {   
			EXTI->PR=1<<12;                         //Çå³ýÖÐ¶Ï±êÖ¾Î»   
			Flag_Target=!Flag_Target;
			Get_Angle();                            //¸üÐÂ×ËÌ¬	5ms¶ÁÈ¡Ò»´Î
			Encoder_Left=-Read_Encoder(2);          //¶ÁÈ¡×óÂÖ±àÂëÆ÷µÄÖµ£¬Ç°½øÎªÕý£¬ºóÍËÎª¸º
			Encoder_Right=-Read_Encoder(4);         //¶ÁÈ¡ÓÒÂÖ±àÂëÆ÷µÄÖµ£¬Ç°½øÎªÕý£¬ºóÍËÎª¸º
																							//×óÂÖAÏà½ÓTIM2_CH1,ÓÒÂÖAÏà½ÓTIM4_CH2,¹ÊÕâÀïÁ½¸ö±àÂëÆ÷µÄ¼«ÐÔÏàÍ¬
			if(Flag_Target==1)                      //Êµ¼ÊÉÏ10ms¿ØÖÆÒ»´Î
				return 0;	                                               
			Key();                                  //É¨Ãè°´¼ü×´Ì¬ µ¥»÷¿ÉÆôÍ£µç»ú
			
			Balance_Pwm =Balance(Angle_Balance,Gyro_Balance); //Æ½ºâPID¿ØÖÆ	  Gyro_BalanceÆ½ºâ½ÇËÙ¶È¼«ÐÔ£ºÇ°ÇãÎªÕý£¬ºóÇãÎª¸º
			Velocity_Pwm=Velocity(Encoder_Left,Encoder_Right);//ËÙ¶È»·PID¿ØÖÆ	 ¼Ç×¡£¬ËÙ¶È·´À¡ÊÇÕý·´À¡£¬¾ÍÊÇÐ¡³µ¿ìµÄÊ±ºòÒªÂýÏÂÀ´¾ÍÐèÒªÔÙÅÜ¿ìÒ»µã
			
			Motor_Left=Balance_Pwm+Velocity_Pwm;              //¼ÆËã×óÂÖµç»ú×îÖÕPWM
			Motor_Right=Balance_Pwm+Velocity_Pwm;             //¼ÆËãÓÒÂÖµç»ú×îÖÕPWM
			
			Motor_Left=PWM_Limit(Motor_Left,6900,-6900);
			Motor_Right=PWM_Limit(Motor_Right,6900,-6900);		//PWMÏÞ·ù

			if(Turn_Off(Angle_Balance)==0)                    //Èç¹û²»´æÔÚÒì³£
				Set_Pwm(Motor_Left,Motor_Right);                //¸³Öµ¸øPWM¼Ä´æÆ÷  
	 }       	
	 return 0;	  
} 

/**************************************************************************
Function: Vertical PD control
Input   : Angle:angle£»Gyro£ºangular velocity
Output  : none
º¯Êý¹¦ÄÜ£ºÖ±Á¢PD¿ØÖÆ		
Èë¿Ú²ÎÊý£ºAngle:½Ç¶È£»Gyro£º½ÇËÙ¶È
·µ»Ø  Öµ£ºÎÞ
**************************************************************************/	
int Balance(float Angle,float Gyro)
{  
	 float Balance_Kp=225,Balance_Kd=1.08;//Ö±Á¢»·PD²ÎÊý
   float Angle_bias,Gyro_bias;
	 int balance;
	 Angle_bias=Middle_angle-Angle;                       //Çó³öÆ½ºâµÄ½Ç¶ÈÖÐÖµ ºÍ»úÐµÏà¹Ø
	 Gyro_bias=0-Gyro;
	 balance=-Balance_Kp*Angle_bias-Gyro_bias*Balance_Kd;   		//¼ÆËãÆ½ºâ¿ØÖÆµÄµç»úPWM  PD¿ØÖÆ   kpÊÇPÏµÊý kdÊÇDÏµÊý 
	 return balance;
}

/**************************************************************************
Function: Speed PI control
Input   : encoder_left£ºLeft wheel encoder reading£»encoder_right£ºRight wheel encoder reading
Output  : Speed control PWM
º¯Êý¹¦ÄÜ£ºËÙ¶È¿ØÖÆPWM		
Èë¿Ú²ÎÊý£ºencoder_left£º×óÂÖ±àÂëÆ÷¶ÁÊý£»encoder_right£ºÓÒÂÖ±àÂëÆ÷¶ÁÊý
·µ»Ø  Öµ£ºËÙ¶È¿ØÖÆPWM
**************************************************************************/
int Velocity(int encoder_left,int encoder_right)
{  
	  float Velocity_Kp=160,Velocity_Ki=0.8;//ËÙ¶È»·PI²ÎÊý
    static float velocity,Encoder_Least,Encoder_bias;
	  static float Encoder_Integral;
   //=============ËÙ¶ÈPI¿ØÖÆÆ÷=======================//	
		Encoder_Least =0-(encoder_left+encoder_right);                    //»ñÈ¡×îÐÂËÙ¶ÈÆ«²î==²âÁ¿ËÙ¶È£¨×óÓÒ±àÂëÆ÷Ö®ºÍ£©-Ä¿±êËÙ¶È£¨´Ë´¦ÎªÁã£© 
		Encoder_bias *= 0.8;		                                          //Ò»½×µÍÍ¨ÂË²¨Æ÷       
		Encoder_bias += Encoder_Least*0.2;	                              //Ò»½×µÍÍ¨ÂË²¨Æ÷  
																																			//Ïàµ±ÓÚÉÏ´ÎÆ«²îµÄ0.8 + ±¾´ÎÆ«²îµÄ0.2£¬¼õ»ºËÙ¶È²îÖµ£¬¼õÉÙ¶ÔÖ±Á¢µÄ¸ÉÈÅ  
		Encoder_Integral +=Encoder_bias;                                  //»ý·Ö³öÎ»ÒÆ »ý·ÖÊ±¼ä£º10ms
		if(Encoder_Integral>10000)  	Encoder_Integral=10000;             //»ý·ÖÏÞ·ù
		if(Encoder_Integral<-10000)	  Encoder_Integral=-10000;            //»ý·ÖÏÞ·ù	
		velocity=-Encoder_bias*Velocity_Kp-Encoder_Integral*Velocity_Ki;        //ËÙ¶È¿ØÖÆ	
		if(Turn_Off(Angle_Balance)==1||Flag_Stop==1)   Encoder_Integral=0;      //µç»ú¹Ø±ÕºóÇå³ý»ý·Ö
	  return velocity;
}


void Set_Pwm(int motor_left,int motor_right)
{
  if(motor_left>0)	    BIN1=1,			BIN2=0; 
	else           			  BIN1=0,			BIN2=1; 
	PWMB=myabs(motor_left);	
  if(motor_right>0)			AIN2=1,			AIN1=0;	
	else 	        			  AIN2=0,			AIN1=1; 
	PWMA=myabs(motor_right);
}


int PWM_Limit(int IN,int max,int min)
{
	int OUT = IN;
	if(OUT>max) OUT = max;
	if(OUT<min) OUT = min;
	return OUT;
}


void Key(void)
{	
	u8 tmp;
	tmp=click(); 
	if(tmp==1) Flag_Stop=!Flag_Stop;	//µ¥»÷¿ØÖÆÐ¡³µµÄÆôÍ£
}


u8 Turn_Off(float angle)
{
	u8 temp;
	if(angle<-40||angle>40||1==Flag_Stop)
	{	                                        
		temp=1;                                         
		AIN1=0;                                            
		AIN2=0;
		BIN1=0;
		BIN2=0;
	}
	else
		temp=0;
	return temp;			
}
	

void Get_Angle(void)
{ 
	mpu_dmp_get_data(&Pitch,&Roll,&Yaw);;                      	 //¶ÁÈ¡¼ÓËÙ¶È¡¢½ÇËÙ¶È¡¢Çã½Ç
	Angle_Balance=Pitch;             	 //¸üÐÂÆ½ºâÇã½Ç,Ç°ÇãÎªÕý£¬ºóÇãÎª¸º
	Gyro_Balance=gyro[0];              //¸üÐÂÆ½ºâ½ÇËÙ¶È,Ç°ÇãÎªÕý£¬ºóÇãÎª¸º
}

int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
