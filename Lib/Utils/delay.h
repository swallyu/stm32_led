

#ifndef SYS_H
#define SYS_H

#include "stm32f10x.h"

void delay_init();

/**
delay us
**/
void delay_us(uint32_t us);

/**
delay ms
**/
void delay_ms(uint32_t ms);


#endif
