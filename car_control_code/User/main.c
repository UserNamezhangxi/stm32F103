#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "nrf24l01.h"
#include "oled.h"
#include "key.h"
#include "AD.h"
#include "Encoder.h"

u8 mode = 0;

int main(void)
{
	u8 key = 0;
	u8 tmp_buf[33];
	NRF24L01_Init(); // 初始化NRF24L01
	Key_Init();
	delay_init();
	LED_Init();
	// AD_Init();
	OLED_Init();
	OLED_ColorTurn(0);	 // 0正常显示，1 反色显示
	OLED_DisplayTurn(0); // 0正常显示 1 屏幕翻转显示
 // Encoder_Init();
	while (NRF24L01_Check())
	{
		OLED_ShowString(0, 0, "NRF24L01 Error", 8, 1);
		LED = 0;
		delay_ms(200);
		OLED_ShowString(0, 0, "           ", 8, 1);
		delay_ms(200);
		LED = 1;
	}

	OLED_ShowString(0, 0, "NRF CHECK OK!", 8, 1);
	delay_ms(1000);

	//	OLED_ShowString(0, 0, "ADC Init OK!", 8, 1);
	//	delay_ms(1000);
	//	OLED_Clear();

	while (1)
	{
		// 方向键
		// OLED_ShowNum(0,1,Vertical(), 4, 8);
		// OLED_ShowNum(0,2,Horizontal(), 4, 8);

		// 音量控制
		//		int volume = Encoder_Get() / 4 + 20; // 编码器四线 所以除以4 得到每转一次的记次
		//		if (volume < 0)
		//		{
		//			volume = 0;
		//		}
		//		else if (volume > 30)
		//		{
		//			volume = 30;
		//		}
		//		OLED_ShowNum(0, 0, volume, 2, 8, 1);

		//		NRF2401 模式控制（收发）
		if (mode == 1)
		{
			NRF24L01_TX_Mode();
			OLED_ShowString(0, 0, "NRF24L01 TX_Mode", 8, 1);
			while (1)
			{
				key = Key_GetNum();
				if (key != NO_KEY)
				{
					tmp_buf[0] = key;
					if (NRF24L01_TxPacket(tmp_buf) == TX_OK)
					{
						OLED_ShowString(0, 1, "Sended DATA:", 8, 1);
						OLED_ShowChar(0, 2, tmp_buf[0] + 0X30, 8, 1);
					}
					else
					{
						// OLED_ShowString(0, 2, "             ", 8,1);
						// 清空显示
						OLED_ShowString(0, 2, "Send Failed ", 8, 1);
					}
					LED = !LED;
				}
			}
		}
		else
		{
			NRF24L01_RX_Mode();
			OLED_ShowString(0, 0, "NRF24L01 RX_Mode", 8, 1);

			while (1)
			{
				OLED_ShowString(0, 1, "Receive DATA:", 8, 1);
				if (NRF24L01_RxPacket(tmp_buf) == 0) // 一旦接收到信息,则显示出来.
				{
					OLED_ShowChar(0, 2, tmp_buf[0] + 0X30, 8, 1);
					LED = !LED;
					delay_ms(300);
					LED = !LED;
					delay_ms(300);
				}
				else
				{
					delay_us(100);
				}
			}
		}
	}
}
