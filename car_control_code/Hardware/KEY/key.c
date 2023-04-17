#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "key.h"

void Key_Init(void)
{
	// PLAY right left car_mode
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_15; // play | right | left | car_mode | down
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//led buzz up
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15 | GPIO_Pin_5; // led | buzz | up
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
	{
		delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0);
		delay_ms(20);
		KeyNum = KEY_LED;
	}
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15) == 0)
	{
		delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15) == 0);
		delay_ms(20);
		KeyNum = KEY_BEEP;
	}
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) == 0)
	{
		delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) == 0);
		delay_ms(20);
		KeyNum = KEY_UP;
	}
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
	{
		delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0);
		delay_ms(20);
		KeyNum = KEY_PLAY_PAUSE;
	}
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) == 0)
	{
		delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) == 0);
		delay_ms(20);
		KeyNum = KEY_RIGHT;
	}

	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11) == 0)
	{
		delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11) == 0);
		delay_ms(20);
		KeyNum = KEY_LEFT;
	}
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == 0)
	{
		delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == 0);
		delay_ms(20);
		KeyNum = KEY_CAR_MODE;
	}
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) == 0)
	{
		delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) == 0);
		delay_ms(20);
		KeyNum = KEY_DOWN;
	}
	return KeyNum;
}
