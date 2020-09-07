
#ifndef __it_h__
#define __it_h__

#include "stm32f10x.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"

void GPIO_IT_init(uint32_t RCC_GPIOx,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin,EXTITrigger_TypeDef EXTI_Trigger,GPIOMode_TypeDef GPIO_Mode);

//初始化中断，并开启对应的中断线
void GPIO_IT_init_ExtiLine(uint32_t RCC_GPIOx,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin,EXTITrigger_TypeDef EXTI_Trigger,GPIOMode_TypeDef GPIO_Mode,
                           uint8_t preemptionPriority,uint8_t subPriority);

void NVIC_Configuration(uint8_t NVIC_IRQChannel,uint8_t preemptionPriority ,uint8_t subPriority );

#endif