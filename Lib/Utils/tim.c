

#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "tim.h"

void TIM_SetTIM3Compare1(uint32_t compare)
{
    TIM3->CCR1=compare;
}

void TIM3_PWM_Init(uint16_t arr,uint16_t psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //①使能定时器 3 时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|
                           RCC_APB2Periph_AFIO, ENABLE); //①使能 GPIO 和 AFIO 复用功能时钟

    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //②重映射 TIM3_CH1->PC6
    //设置该引脚为复用输出功能,输出 TIM3 CH2 的 PWM 脉冲波形 GPIOB.5
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM_CH2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure); //①初始化 GPIO

//初始化 TIM3
    TIM_TimeBaseStructure.TIM_Period = arr; //设置在自动重装载周期值
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM 向上计数模式
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //③初始化 TIMx

//初始化 TIM3 Channel1 PWM 模式
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择 PWM 模式 2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性高
    TIM_OCInitStructure.TIM_Pulse=arr/2;
    TIM_OC1Init(TIM3, &TIM_OCInitStructure); //④初始化外设 TIM3 OC1
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable); //使能预装载寄存器
    TIM_Cmd(TIM3, ENABLE); //⑤使能 TIM3
}