#ifndef __LED_H__
#define __LED_H__

#include "stm32f10x.h"


void LED_GPIO_Init(uint32_t RCC_GPIO,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);

void LED_ON(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);

void LED_OFF(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);

void LED_Toggle(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
#endif