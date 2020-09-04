#include "led.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void LED_GPIO_Init(uint32_t RCC_GPIOx,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin){
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_GPIOx,ENABLE);
	GPIO_InitStruct.GPIO_Pin =GPIO_Pin;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOx,&GPIO_InitStruct);
}

/**

**/
void LED_ON(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin){
	GPIO_ResetBits(GPIOx,GPIO_Pin);
}

/**
**/
void LED_OFF(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin){
	GPIO_SetBits(GPIOx,GPIO_Pin);
}

void LED_Toggle(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin){
	uint8_t status = GPIO_ReadOutputDataBit(GPIOx,GPIO_Pin);
	if(status){                 //高电平时，LED熄灭
		LED_ON(GPIOx,GPIO_Pin);
	}else{
		LED_OFF(GPIOx,GPIO_Pin);
	}
}