#ifndef __LED_H__
#define __LED_H__

#include "stm32f10x.h"
#define LED_Pin  GPIO_Pin_6
#define LED_Port GPIOC
#define LED_CLK  RCC_APB2Periph_GPIOC

void LED_GPIO_Config(void);

#endif