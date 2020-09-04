
#include "stm32f10x.h"

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"

#include "led.h"
#include "delay.h"
#include "beep/beep.h"
#include "usart.h"

#define LED_Pin  GPIO_Pin_3
#define LED_Port GPIOC
#define LED_CLK  RCC_APB2Periph_GPIOC

int main(){
	
	delay_init();
			
	LED_GPIO_Init(LED_CLK,LED_Port,LED_Pin);
	//beepInit();
	
	uint8_t status=0;
  unsigned char TxBuf1[] = "Welcome to my STM32! Please press any key!";
  
  usart_init(115200,USART1);
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

void USART1_IRQHandler(void){
  if( USART_GetFlagStatus(USART1, USART_FLAG_RXNE)==SET){
    usart_sendData(USART1,USART_ReceiveData(USART1));
  }
}

/*
void SystemInit(void){

}
*/