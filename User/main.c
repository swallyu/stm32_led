
#include "stm32f10x.h"
#include "led.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define LED_Pin  GPIO_Pin_4
#define LED_Port GPIOC
#define LED_CLK  RCC_APB2Periph_GPIOC


int main(){
	
	LED_GPIO_Init(LED_CLK,LED_Port,LED_Pin);
	
	while(1)
	{
		LED_ON(LED_Port,LED_Pin);
	}
}
/*
void SystemInit(void){

}
*/