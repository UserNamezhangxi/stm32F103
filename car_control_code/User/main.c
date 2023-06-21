#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "nrf24l01.h"
#include "oled.h"
#include "key.h"
#include "AD.h"
#include "Encoder.h"
#include "usart.h"

u8 mode = 1;

int main(void)
{
	u8 key = 0, key_status, key_value;
	u8 tmp_buf[33];
	NRF24L01_Init(); // 初始化NRF24L01
	Key_Init();
	delay_init();
	LED_Init();
	AD_Init();
	OLED_Init();
	OLED_ColorTurn(0);	 // 0正常显示，1 反色显示
	OLED_DisplayTurn(0); // 0正常显示 1 屏幕翻转显示
	Encoder_Init();
	uart_init(115200);
	while (NRF24L01_Check())
	{
		OLED_ShowString(0, 0, "NRF24L01 Error", 8, 1);
		LED = 0;
		delay_ms(200);
		OLED_Clear();
		delay_ms(200);
		LED = 1;
	}

	OLED_ShowString(0, 0, "NRF CHECK OK!", 8, 1);
	delay_ms(1000);

	while (1)
	{
		//	NRF2401 模式控制（收发）
		if (mode == 1)
		{
			NRF24L01_TX_Mode();
			OLED_ShowString(0, 0, "NRF24L01 TX_Mode", 8, 1);
			while (1)
			{
				key = Key_GetNum(&key_status, &key_value);
				if (key != NO_KEY)
				{
					tmp_buf[0] = key_status;
					tmp_buf[1] = key_value;
					printf("key_status = %d key_value = %d\r\n", key_status, key_value);
					if (NRF24L01_TxPacket(tmp_buf) == TX_OK)
					{
						OLED_ShowString(0, 9, "Sended DATA:", 8, 1);
						OLED_ShowString(0, 18, "             ", 8, 1);
						OLED_ShowNum(0, 18, tmp_buf[0], 2, 8, 1);
						OLED_ShowNum(20, 18, tmp_buf[1], 2, 8, 1);
					}
					else
					{
						OLED_ShowString(0, 2, "             ", 8, 1);
						OLED_ShowString(0, 18, "Send Failed ", 8, 1);
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
				OLED_ShowString(0, 8, "Receive DATA:", 8, 1);
				if (NRF24L01_RxPacket(tmp_buf) == 0) // 一旦接收到信息,则显示出来.
				{
					OLED_ShowChar(0, 19, tmp_buf[0] + 0X30, 8, 1);
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
