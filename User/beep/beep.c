

#include "beep.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void beepInit(){
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStruct.GPIO_Pin =GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
}

void beepOn(){
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
}

void beepOff(){
	GPIO_SetBits(GPIOB,GPIO_Pin_8);
}

void beepToggle(){
	uint32_t status = GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_8);
	
	if(status==1){    //高电平停止响
		beepOn();       //所以需要调用设置为低电平响
	}else{
		beepOff(); 
	}
}
