
#include "key.h"
/**************************************************************************
Function: Key initialization
Input   : none
Output  : none
�������ܣ�������ʼ��
��ڲ�������
����  ֵ���� 
**************************************************************************/
void KEY_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //ʹ��PA�˿�ʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	            //�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOA 
} 
/**************************************************************************
Function: Key scan
Input   : none
Output  : 0��No action��1��click��
�������ܣ�����ɨ��
��ڲ�������
����  ֵ������״̬ 0���޶��� 1������ 
**************************************************************************/
u8 click(void)
{
		static u8 flag_key=1;//�����ɿ���־
		if(flag_key&&KEY==0) //��⵽��������
		{
			flag_key=0;
			return 1;	//��������
		}
		else if(1==KEY)			flag_key=1;
		return 0;//�ް�������
}
