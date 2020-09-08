
#ifndef __pwm_h__
#define __pwm_h__
#include "stm32f10x.h"

void TIM3_PWM_Init(uint16_t arr,uint16_t psc);

void TIM_SetTIM3Compare1(uint32_t compare);

#endif