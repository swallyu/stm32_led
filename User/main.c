
#include "stm32f10x.h"

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"

#include "led.h"
#include "delay.h"
#include "beep/beep.h"
#include "usart.h"
#include "it.h"

#define LED_Pin  GPIO_Pin_3
#define LED_Port GPIOC
#define LED_CLK  RCC_APB2Periph_GPIOC
#define LED7_Pin  GPIO_Pin_7
#define LED6_Pin  GPIO_Pin_6

int main(){
	
	delay_init();
			
	LED_GPIO_Init(LED_CLK,LED_Port,LED_Pin|LED7_Pin|LED6_Pin);
  //LED_GPIO_Init(RCC_APB2Periph_GPIOD,GPIOD,GPIO_Pin_2);
	//beepInit();
	
	uint8_t status=0;
  unsigned char TxBuf1[] = "Welcome to my STM32! Please press any key!";
  
  usart_init(115200,USART1);
  //中断线0
  NVIC_Configuration(EXTI9_5_IRQn,3,3);
  NVIC_Configuration(EXTI2_IRQn,3,3);
  //PC8,下降沿触发
  
  GPIO_IT_init(RCC_APB2Periph_GPIOC,GPIOC,GPIO_Pin_8,EXTI_Trigger_Falling,GPIO_Mode_IPU);
  
  GPIO_IT_init_ExtiLine(RCC_APB2Periph_GPIOD,GPIOD,GPIO_Pin_2,EXTI_Trigger_Falling,GPIO_Mode_IPU,3,3);
  
  //GPIO_IT_init(RCC_APB2Periph_GPIOD,GPIOD,GPIO_Pin_2,EXTI_Trigger_Falling);

  GPIO_IT_init_ExtiLine(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_0,EXTI_Trigger_Rising,GPIO_Mode_IPD,3,3);
    
	while(1)
	{
		LED_Toggle(LED_Port,LED_Pin);
		
		//beepToggle();
		/**
		if(status==0){
			LED_ON(LED_Port,LED_Pin);
			status=1;
		}else{
			LED_OFF(LED_Port,LED_Pin);		
			status=0;			
		}**/
    int i;
    for( i=0;TxBuf1[i]!='\0';i++)
    {
       usart_sendData(USART1,TxBuf1[i]);
       GPIO_SetBits(GPIOB,GPIO_Pin_5);
    }
		
		delay_ms(1000);
	}
}
void EXTI0_IRQHandler(void){
  if(EXTI_GetITStatus(EXTI_Line0) != RESET) 
	{
		/******/
         //LED闪烁相关代码
    LED_Toggle(LED_Port,LED6_Pin);
		/******/
    //清除中断标志位		
	}
  EXTI_ClearITPendingBit(EXTI_Line0);   
}
void EXTI1_IRQHandler(void){}
void EXTI2_IRQHandler(void){
  if(EXTI_GetITStatus(EXTI_Line2) != RESET) 
	{
		/******/
         //LED闪烁相关代码
    LED_Toggle(LED_Port,LED6_Pin);
		/******/
    //清除中断标志位		
	}
  EXTI_ClearITPendingBit(EXTI_Line2);     
  
}
void EXTI3_IRQHandler(void){}
void EXTI4_IRQHandler(void){}
void EXTI15_10_IRQHandler(void){}
void EXTI9_5_IRQHandler(void){
  if(EXTI_GetITStatus(EXTI_Line8) != RESET) 
	{
		/******/
         //LED闪烁相关代码
    LED_Toggle(LED_Port,LED7_Pin);
		/******/
    //清除中断标志位
		EXTI_ClearITPendingBit(EXTI_Line8);     
	}else if(EXTI_GetITStatus(EXTI_Line9) != RESET) 
	{
		/******/
         //LED闪烁相关代码
    LED_Toggle(LED_Port,LED6_Pin);
		/******/
    //清除中断标志位
		EXTI_ClearITPendingBit(EXTI_Line9);     
	}  
}

void USART1_IRQHandler(void){
  if( USART_GetFlagStatus(USART1, USART_FLAG_RXNE)==SET){
    usart_sendData(USART1,USART_ReceiveData(USART1));
  }
}

/*
void SystemInit(void){

}
*/