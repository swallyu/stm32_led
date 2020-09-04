
#ifndef __usart_h__
#define __usart_h__
#include "stm32f10x.h"

void usart_init(uint32_t boundRate,USART_TypeDef* usartPort);

void usart_deinit(USART_TypeDef* usartPort);

void usart_sendData(USART_TypeDef* usartPort,uint16_t data);

#endif