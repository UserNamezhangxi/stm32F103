#include "reg.h"
#include "delay.h"
#include "typedef.h"
#include "usart.h"
#include "timer.h"
#include "iic.h"
#include "led.h"

void Rcc_init(void);

int main()
{ 
	u8 data = 1;
	u8 i=0;
	Rcc_init();
	delay_init();
	led_init();
  usart_init(72,115200);
  IIC_Init();
	
	LED_RED = 0;
	//delay_ms(1000);
//	for(i=0;i<=255;i++) {
//	    send_write_byte(i,i+1);
//		  printf("write data = %d\r\n",i);
//  		delay_ms(10);
//		if(i==255) {
//		   break;
//		}
//  }
	
	for(i=0;i<=255;i++) {
	  data = send_read_byte(i); 
		printf("read data = %d\r\n",data);
		LED_RED = data & 0x01; // 用led 指示数据读取中
		delay_ms(100);
		if(i==255) {
		   break;
		}
  }

	delay_ms(1000);
	while(1)
	{ 
		LED_RED = 1;
		delay_ms(3000);
	}
}


void Rcc_init(void) 
{
	// 1.RCC 寄存器打开内部时钟
	RCC1->CR |= 1<<0;
	// 2. 关闭RCC_CIR 中断，避免中断干扰时钟设置
  RCC1->CIR = 0;
  // 3. 设置HSE 的信号源外部晶振不旁路，启动HSE 	
	RCC1->CR &= ~(1<<18);
	// 4. 开启HSE
	RCC1->CR |= 1<<16;
	// 5. 等待HSE 就绪
	while((RCC->CR & (1<<17)) == 0);
	// 6. 配置 AHP APB1 APB2分频倍频系数
	RCC1->CFGR &= ~(1<<7); // AHB=DIV1;   
	RCC1->CFGR |= 4<<8;    // APB1=DIV2 
	RCC1->CFGR &= ~(1<<13); // APB2=DIV1;
	// 7. 关闭PLL
	RCC1->CR &= ~(1<<24);  // 关闭PLL
	// 8. 配置PLL 分频倍频
	RCC1->CFGR |= 0xf<<18; // 16 倍频
	RCC1->CFGR |= 1<<16; // PLLSRC时钟源选择
	RCC1->CFGR |= 1<<17; //PLLXTPRE 分频选择
  FLASH_ACR |=0x32; //FLASH 2个延时周期
  // 9. 使能PLL
	RCC1->CR |= (1<<24); // 开启PLL
	// 10. 等待PLL 使能OK
	while((RCC1->CR & (1<<25)) == 0); 
	// 11. 选择主PLL 作为时钟
	RCC1->CFGR &= ~(3<<0); // 清零
	RCC1->CFGR |= 2<<0;
	// 12.等待主PLL稳定
	while((RCC1->CFGR & (3<<2)) != (2<<2));	

}


