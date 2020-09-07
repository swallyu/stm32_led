
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "misc.h"

#include "it.h"

uint8_t PinSourceFromGPIO_PIN(uint16_t GPIO_Pin);
uint8_t PortSourceFromGPIOx(GPIO_TypeDef* GPIOx);
uint32_t EXTI_LineFromGPIO_PIN(uint16_t GPIO_Pin);
void NVIC_EXTI_Enable(uint32_t EXTI_Line);

void NVIC_Configuration(uint8_t NVIC_IRQChannel,uint8_t preemptionPriority,uint8_t subPriority )
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* 配置中断源：按键1 */
    NVIC_InitStructure.NVIC_IRQChannel = NVIC_IRQChannel;  //配置为EXTI0通道
    /* 配置抢占优先级 */
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = preemptionPriority;
    /* 配置子优先级 */
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = subPriority;
    /* 使能中断通道 */
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); //将上述配置参数传入中断初始化函数
}

void GPIO_IT_init(uint32_t RCC_GPIOx,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin,EXTITrigger_TypeDef EXTI_Trigger,GPIOMode_TypeDef GPIO_Mode) {

    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;

    /*开启GPIO口的时钟*/
    RCC_APB2PeriphClockCmd(RCC_GPIOx|RCC_APB2Periph_AFIO,ENABLE);

    /* 选择用到的GPIO */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
    /* 配置为浮空输入 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode;
    GPIO_Init(GPIOx, &GPIO_InitStructure);

    /* 选择EXTI的信号源 */
    GPIO_EXTILineConfig(PortSourceFromGPIOx(GPIOx), PinSourceFromGPIO_PIN(GPIO_Pin));
    EXTI_InitStructure.EXTI_Line = EXTI_LineFromGPIO_PIN(GPIO_Pin);

    /* EXTI为中断模式 */
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    /* 上升沿中断 */
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger;
    /* 使能中断 */
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_EXTI_Enable(EXTI_InitStructure.EXTI_Line);
}

void GPIO_IT_init_ExtiLine(uint32_t RCC_GPIOx,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin,EXTITrigger_TypeDef EXTI_Trigger,GPIOMode_TypeDef GPIO_Mode,
                           uint8_t preemptionPriority,uint8_t subPriority) {
    GPIO_IT_init(RCC_GPIOx,GPIOx,GPIO_Pin,EXTI_Trigger,GPIO_Mode);
    uint32_t extiLine =  EXTI_LineFromGPIO_PIN(GPIO_Pin);
    NVIC_EXTI_Enable(extiLine);
}

void NVIC_EXTI_Enable(uint32_t EXTI_Line) {
    switch(EXTI_Line) {
    case EXTI_Line0:
        NVIC_Configuration(EXTI0_IRQn,3,3);
        break;
    case EXTI_Line1:
        NVIC_Configuration(EXTI1_IRQn,3,3);
        break;
    case EXTI_Line2:
        NVIC_Configuration(EXTI2_IRQn,3,3);
        break;
    case EXTI_Line3:
        NVIC_Configuration(EXTI3_IRQn,3,3);
        break;
    case EXTI_Line4:
        NVIC_Configuration(EXTI4_IRQn,3,3);
        break;
    case EXTI_Line5:
    case EXTI_Line6:
    case EXTI_Line7:
    case EXTI_Line8:
    case EXTI_Line9:
        NVIC_Configuration(EXTI9_5_IRQn,3,3);
        break;
    case EXTI_Line10:
    case EXTI_Line11:
    case EXTI_Line12:
    case EXTI_Line13:
    case EXTI_Line14:
    case EXTI_Line15:
        NVIC_Configuration(EXTI15_10_IRQn,3,3);
        break;
    }
}

uint8_t PortSourceFromGPIOx(GPIO_TypeDef* GPIOx) {
    if(GPIOx==GPIOA) {
        return GPIO_PortSourceGPIOA;
    }
    if(GPIOx==GPIOB) {
        return GPIO_PortSourceGPIOB;
    }
    if(GPIOx==GPIOC) {
        return GPIO_PortSourceGPIOC;
    }
    if(GPIOx==GPIOD) {
        return GPIO_PortSourceGPIOD;
    }
    if(GPIOx==GPIOE) {
        return GPIO_PortSourceGPIOE;
    }
    if(GPIOx==GPIOF) {
        return GPIO_PortSourceGPIOF;
    }
    if(GPIOx==GPIOG) {
        return GPIO_PortSourceGPIOG;
    }
    return 99;
}

uint8_t PinSourceFromGPIO_PIN(uint16_t GPIO_Pin) {
    switch(GPIO_Pin) {
    case GPIO_Pin_0:
        return GPIO_PinSource0;
    case GPIO_Pin_1:
        return GPIO_PinSource1;
    case GPIO_Pin_2:
        return GPIO_PinSource2;
    case GPIO_Pin_3:
        return GPIO_PinSource3;
    case GPIO_Pin_4:
        return GPIO_PinSource4;
    case GPIO_Pin_5:
        return GPIO_PinSource5;
    case GPIO_Pin_6:
        return GPIO_PinSource6;
    case GPIO_Pin_7:
        return GPIO_PinSource7;
    case GPIO_Pin_8:
        return GPIO_PinSource8;
    case GPIO_Pin_9:
        return GPIO_PinSource9;
    case GPIO_Pin_10:
        return GPIO_PinSource10;
    case GPIO_Pin_11:
        return GPIO_PinSource11;
    case GPIO_Pin_12:
        return GPIO_PinSource12;
    case GPIO_Pin_13:
        return GPIO_PinSource13;
    case GPIO_Pin_14:
        return GPIO_PinSource14;
    case GPIO_Pin_15:
        return GPIO_PinSource15;
    }
    return 99;
}

uint32_t EXTI_LineFromGPIO_PIN(uint16_t GPIO_Pin) {
    switch(GPIO_Pin) {
    case GPIO_Pin_0:
        return EXTI_Line0;
    case GPIO_Pin_1:
        return EXTI_Line1;
    case GPIO_Pin_2:
        return EXTI_Line2;
    case GPIO_Pin_3:
        return EXTI_Line3;
    case GPIO_Pin_4:
        return EXTI_Line4;
    case GPIO_Pin_5:
        return EXTI_Line5;
    case GPIO_Pin_6:
        return EXTI_Line6;
    case GPIO_Pin_7:
        return EXTI_Line7;
    case GPIO_Pin_8:
        return EXTI_Line8;
    case GPIO_Pin_9:
        return EXTI_Line9;
    case GPIO_Pin_10:
        return EXTI_Line10;
    case GPIO_Pin_11:
        return EXTI_Line11;
    case GPIO_Pin_12:
        return EXTI_Line12;
    case GPIO_Pin_13:
        return EXTI_Line13;
    case GPIO_Pin_14:
        return EXTI_Line14;
    case GPIO_Pin_15:
        return EXTI_Line15;
    }
    return 99;
}
