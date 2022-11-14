#include "reg.h"
#include "delay.h"
#include "key.h"
#include "typedef.h"
#include "beep.h"
#include "led.h"
#include "sys.h"

void key_init(void) {
		
	unsigned short interrupt_channel = EXTI4_IRQn;
	unsigned char group = 3;
	unsigned char priority = 0x7;
	volatile unsigned int temp;
	// 1.���ö�Ӧ����
	GPIOE_CRL &= ~(0XF << 16);
	GPIOE_CRL |= 0x8 << 16;// ����PE4 ����������ģʽ 2MHZ
  GPIOE->ODR|=1<<4;	   	//PE4 ����
	
	// 2.ʹ�ܶ�Ӧ����ʱ��
	RCC->APB2ENR |= 1<<6; // ʹ��APB2����ʱ��
	RCC->APB2ENR|=0x01;//ʹ��io����ʱ��	
	// 3.����PE4 IO ���ж�֮���ӳ���ϵ
	AFIO->EXTICR[1] &= 0xfff0; 
	AFIO->EXTICR[1] |= 0xfff4; // PE4 ����Ϊ�ⲿ�ж�4
	
	// 4.��ʼ�������жϣ����ô�������
	EXTI->IMR |= 1<<4; // �ſ�������4�ϵ��ж�
	EXTI->FTSR |= 1<<4; // ������4���½��ش����ж�
	
  // �������EXIT4�жϡ�����ICER[channel/32] |= 1<<(channel%32) �Ĵ�����д���Ӧλ1;
	// ��ARIC ��������ռ���ȼ�����Ӧ���ȼ� 
	temp = SCB->AIRCR; // ��ȡ��ǰ��ֵ
	temp &= 0X0000F8FF;  // ��ո�λ������BIT[10��8] ��0
  temp |= (0X05FA<<16 | (7 - group) << 8);  // ������Կ���������ȼ����÷���3
	SCB->AIRCR = temp;
	
  // 5.�����жϷ���(nvic) ��ʹ���ж�
	// NVIC_ISERx  channel = 9 �����ⲿ�ж�4
	//NVIC->ISER[interrupt_channel/32] |= (1<<(interrupt_channel%32)); // ʹ��EXIT4 �ж�λ
  //NVIC->IP[interrupt_channel] = priority << 4;  //IPn[7:4] ��ʾ���ȼ��� ��ǰ�ж����ȼ�0111  ��ʾ ��ռ3����Ӧ1
}

//�ⲿ�ж�4�������
void EXTI4_IRQHandler(void)
{
	unsigned char i = 0;
	delay_ms(10);	//����
	if(KEY0==0)	 	//����KEY0
	{
		for(;i<5;i++) {
			BEEP=1;
			LED_GRREN = ~LED_GRREN;
			delay_ms(200);
			BEEP=0;
			LED_GRREN = ~LED_GRREN;
			delay_ms(200);
		}
	}		 
	EXIT1->PR=1<<4;  //���LINE4�ϵ��жϱ�־λ  
}		


unsigned int key_scan(void) 
{
  static unsigned char key_flag = 1; // ����״̬ 1��ʾ̸̾��0��ʾ���� 
	if ((key_flag == 1) && (KEY0 == 0 || KEY1== 0)) {
		delay_ms(10);
		if (KEY0 == 0 || KEY1 == 0) {
			key_flag = 0;
			if (KEY0 == 0) {
				return KEY0_PRES;
			} 
			if (KEY1 == 0) {
				return KEY1_PRES;
			} 
		}
	}
	
	if ((key_flag == 0) && KEY0 == 1 && KEY1== 1) {
		delay_ms(10);
		if(KEY0 == 1 && KEY1== 1) {
		  key_flag = 1;
		}	
	}

  return NO_KEYPRESS;

}