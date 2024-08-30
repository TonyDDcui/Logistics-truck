#ifndef __USART_H
#define __USART_H

#include "board.h"
#include "fifo.h"
#include "stdbool.h"

/**********************************************************
***	Emm_V5.0步进闭环控制
**********************************************************/

extern __IO bool rxFrameFlag;
extern __IO uint8_t rxCmd[FIFO_SIZE];
extern __IO uint8_t rxCount;

extern char openmv_receive[64],host_command[7];
extern int rx_count;
extern bool rx_flag;
extern int rx_num;
extern bool host_rx_flag;

void usart_SendCmd(__IO uint8_t *cmd, uint8_t len);
void usart_SendByte(uint16_t data);

void USART2_SendString(const char *str);  //发送文本消息
int USART2_DataAvailable(void);
int USART2_ReceiveData(char *buffer, int bufferSize);
void SendDataToUSART(USART_TypeDef *USARTx, char *buffer, int length);

#endif
