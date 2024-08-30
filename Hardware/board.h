#ifndef __BOARD_H
#define __BOARD_H

#include "stm32f4xx.h"

/**********************************************************
***	Emm_V5.0步进闭环控制
**********************************************************/

void nvic_init(void);
void clock_init(void);
void usart_init(void);
void Key_init(void);
void LED_Init(void);
void board_init(void);

#endif
