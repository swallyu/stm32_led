
#include "stm32f10x.h"
#include "led.h"
#include "stm32f10x_gpio.h"

int main(){
	LED_GPIO_Config();
	while(1)
	{
		GPIO_ResetBits(GPIOC, LED_Pin);
	}
}
/*
void SystemInit(void){

}
*/