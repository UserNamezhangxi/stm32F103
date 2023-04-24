#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "nrf24l01.h"
#include "oled.h"
#include "key.h"
#include "AD.h"
#include "Encoder.h"

u8 mode = 1;

int main(void)
{
	u8 key = 0;
	u8 tmp_buf[33];
	NRF24L01_Init(); //��ʼ��NRF24L01
	Key_Init();
	delay_init();
	LED_Init();
	AD_Init();
	OLED_Init();
	OLED_ColorTurn(0);	 // 0������ʾ��1 ��ɫ��ʾ
	OLED_DisplayTurn(0); // 0������ʾ 1 ��Ļ��ת��ʾ
	Encoder_Init();
	//	while (NRF24L01_Check())
	//	{
	//		OLED_ShowString(0, 0, "NRF24L01 Error", 8);
	//		LED = 0;
	//		delay_ms(200);
	//		OLED_ShowString(0, 0, "           ", 8);
	//		delay_ms(200);
	//		LED = 1;
	//	}

	//	OLED_ShowString(0,0,"NRF CHECK OK!",8);
	//	delay_ms(1000);

	OLED_ShowString(0, 0, "ADC Init OK!", 8, 1);
	delay_ms(1000);
	OLED_Clear();

	while (1)
	{
		// �����
		// OLED_ShowNum(0,1,Vertical(), 4, 8);
		// OLED_ShowNum(0,2,Horizontal(), 4, 8);

		// ��������
		int volume = Encoder_Get() / 4 + 20; // ���������� ���Գ���4 �õ�ÿתһ�εļǴ�
		if (volume < 0)
		{
			volume = 0;
		}
		else if (volume > 30)
		{
			volume = 30;
		}
		OLED_ShowNum(0, 0, volume, 2, 8, 1);

		//		NRF2401 ģʽ���ƣ��շ���
		//		if(mode == 0) {
		//			NRF24L01_TX_Mode();
		//			OLED_ShowString(0, 0, "NRF24L01 TX_Mode", 8);
		//			while (1)
		//			{
		//				key = Key_GetNum();
		//				if (key != NO_KEY)
		//				{
		//					tmp_buf[0] = key;
		//					if (NRF24L01_TxPacket(tmp_buf) == TX_OK)
		//					{
		//						OLED_ShowString(0, 1, "Sended DATA:", 8);
		//						OLED_ShowChar(0, 2, tmp_buf[0]+0X30, 8);
		//					}
		//					else
		//					{
		//						//OLED_ShowString(0, 2, "             ", 8);
		//						//�����ʾ
		//						OLED_ShowString(0, 2, "Send Failed ", 8);
		//					}
		//					LED = !LED;
		//				}
		//			}
		//		}
		//		else
		//		{
		//			NRF24L01_RX_Mode();
		//			OLED_ShowString(0, 0, "NRF24L01 RX_Mode", 8);
		//
		//			while(1) {
		//				OLED_ShowString(0, 1, "Receive DATA:", 8);
		//				if(NRF24L01_RxPacket(tmp_buf)==0)//һ�����յ���Ϣ,����ʾ����.
		//				{
		//					OLED_ShowChar(0,2,tmp_buf[0]+0X30, 8);
		//					LED=!LED;
		//					delay_ms(300);
		//					LED=!LED;
		//					delay_ms(300);
		//				}
		//				else
		//			  {
		//					delay_us(100);
		//				}
		//			}
		//		}
	}
}
