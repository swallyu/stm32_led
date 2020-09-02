#include "delay.h"
#include "system_stm32f10x.h"

extern uint32_t SystemCoreClock;

/**
define 1us = x clicks
default SystemCoreClock 72000000 72MHz
**/
//#define fac_us (SystemCoreClock/1000000);

static u8  fac_us=0;           //延时微秒的频率
static u16 fac_ms=0;           //延时毫秒的频率

void delay_init()
{    
    fac_us=SystemCoreClock/8000000; // 72/8 延时1微秒9个时钟周期
    fac_ms=(u16)fac_us*1000;   // 延时1毫秒9000个Cystic时钟周期
	
		SysTick->LOAD=SysTick_LOAD_RELOAD_Msk;    // 设置最大时钟周期，SysTick时钟周期
    SysTick->VAL=0x00;                       // VAL初始化为0
		
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ; // 使能SysTick定时器
}

void delay_us(uint32_t us){
	uint32_t ticks;
	uint32_t told,tnow,tcnt=0;
	uint32_t reload=SysTick->LOAD; //
	ticks = us * fac_us;
	
	told = SysTick->VAL;           // 开始时计数器的值
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)
				tcnt+=told-tnow;	       //这里注意一下SYSTICK是一个递减的计数器就可以了.
			else 
				tcnt+=reload-tnow+told;	 //如果tnow比上次记录的要大，则说明计数器已经reload，
			
			told=tnow;
			if(tcnt>=ticks)break;			//时间超过/等于要延迟的时间,则退出.
		}  
	};
}

void delay_ms(uint32_t ms){
	uint32_t i;
	for(i=0;i<ms;i++) {
		delay_us(1000);
	}	
}