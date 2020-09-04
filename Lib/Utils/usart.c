
#include "usart.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "misc.h"

#define Usart1_GPIO GPIOA
#define Usart1_GPIO_TX_PIN GPIO_Pin_9
#define Usart1_GPIO_RX_PIN GPIO_Pin_10



void usart_init(uint32_t boundRate,USART_TypeDef* usartPort) {
    GPIO_InitTypeDef GPIO_InitStruct;

    uint32_t usartTxPin;
    uint32_t usartRxPin;
    
    if(usartPort == USART1) {
      //使能GPIOA，Usart1时钟，打开复用功能
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1|RCC_APB2Periph_AFIO,ENABLE);
        usartTxPin = Usart1_GPIO_TX_PIN;
        usartRxPin = Usart1_GPIO_RX_PIN;
    }
    //设置 GPIO
    GPIO_InitStruct.GPIO_Pin =Usart1_GPIO_TX_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;          //推挽复用输出
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(Usart1_GPIO,&GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin =Usart1_GPIO_RX_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;          //浮空输入
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(Usart1_GPIO,&GPIO_InitStruct);

    USART_InitTypeDef usartInitDef;
		USART_StructInit(&usartInitDef);
		usartInitDef.USART_BaudRate=boundRate;
		usartInitDef.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
		usartInitDef.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
		usartInitDef.USART_WordLength=USART_WordLength_8b;
		usartInitDef.USART_StopBits=USART_StopBits_1;
		usartInitDef.USART_Parity=USART_Parity_No;
		USART_Init(usartPort,&usartInitDef);
		
    USART_ClockInitTypeDef usartClockDef;		
		USART_ClockStructInit(&usartClockDef);
		USART_ClockInit(usartPort,&usartClockDef);
    
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;  //抢占优先级 3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;      //子优先级 3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;      //IRQ 通道使能
    NVIC_Init(&NVIC_InitStructure);        //中断优先级初始化
    //⑤开启中断
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  //开启中断
    
		USART_Cmd(usartPort,ENABLE);	  //启用串口	
}

void usart_deinit(USART_TypeDef* usartPort){
  USART_DeInit(usartPort);
}

uint32_t usartRead(USART_TypeDef* usartPort){
  
    return 0;  
}

void usart_sendData(USART_TypeDef* usartPort,uint16_t data){
  USART_SendData(usartPort,data);
  
  while((USART_GetFlagStatus(usartPort,USART_FLAG_TC))==RESET);  
}