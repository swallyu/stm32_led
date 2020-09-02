
#include "stm32f10x.h"

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#include "led.h"
#include "delay.h"

#define LED_Pin  GPIO_Pin_3
#define LED_Port GPIOC
#define LED_CLK  RCC_APB2Periph_GPIOC

int main(){
	
	delay_init();
			
	LED_GPIO_Init(LED_CLK,LED_Port,LED_Pin);
	
	uint8_t status=0;
	while(1)
	{
		LED_Toggle(LED_Port,LED_Pin);
		/**
		if(status==0){
			LED_ON(LED_Port,LED_Pin);
			status=1;
		}else{
			LED_OFF(LED_Port,LED_Pin);		
			status=0;			
		}**/
		
		delay_ms(1000);
	}
}
/*
void SystemInit(void){

}
*/