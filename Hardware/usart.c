#include "usart.h"
#include <string.h>
#include "delay.h"

__IO bool rxFrameFlag = false;
__IO uint8_t rxCmd[FIFO_SIZE] = {0};
__IO uint8_t rxCount = 0;

int rx_count=0,rx_count_old=0;
int host_step = 0;
char host_rx = 0x00;
char openmv_receive[64],openmv_fifo[64],host_command[7];
int rx_num=0;
char standard[]="QRconfirm";
char standard_ts2[]="WLconfirm";
bool rx_flag=0;
bool host_rx_flag = 0;
size_t n = 9;

/**
	* @brief   USART1中断函数
	* @param   无
	* @retval  无
	*/
void USART1_IRQHandler(void)
{
	__IO uint16_t i = 0;

/**********************************************************
***	串口接收中断
**********************************************************/
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		// 未完成一帧数据接收，数据进入缓冲队列
		fifo_enQueue((uint8_t)USART1->DR);

		// 清除串口接收中断
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}

/**********************************************************
***	串口空闲中断
**********************************************************/
	else if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
	{
		// 先读SR再读DR，清除IDLE中断
		USART1->SR; USART1->DR;

		// 提取一帧数据命令
		rxCount = fifo_queueLength(); for(i=0; i < rxCount; i++) { rxCmd[i] = fifo_deQueue(); }

		// 一帧数据接收完成，置位帧标志位
		rxFrameFlag = true;
	}
}

void USART3_IRQHandler()
{
	if(USART_GetITStatus(USART3,USART_IT_RXNE) != RESET)
	{
		openmv_fifo[rx_count] = USART3->DR;
		++rx_count;
		if(!strcmp(openmv_fifo,standard_ts2)) rx_count_old = rx_count;
		USART_ClearFlag(USART3,USART_IT_RXNE);
	}
	else if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)
	{
		USART3->SR; USART3->DR;
		if(!strncmp(openmv_fifo,standard_ts2,n))
		{
			if((rx_count - rx_count_old-1) == ((int)openmv_fifo[9]-0x30))
			{
				for(int i=0;i<=rx_count;i++) openmv_receive[i] = openmv_fifo[i];
				rx_flag = 1;
				rx_num = rx_count;
			}
		}
		memset(openmv_fifo,0,sizeof(openmv_fifo));
		rx_count = 0;
	}
}

void USART2_IRQHandler()
{
	if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET)
	{
		host_rx = USART_ReceiveData(USART2);
		switch(host_step)
		{
			case 0:
				 if(0x24==host_rx)
				 {
					 host_command[0]=host_rx;
					 host_step=0x01;
					 host_rx_flag=0;
				 }
				 else
				 {
					 host_command[0]=0x00;
					 host_command[1]=0x00;
					 host_command[2]=0x00;
					 host_command[3]=0x00;
					 host_command[4]=0x00;
					 host_command[5]=0x00;
					 host_command[6]=0x00;
					 
					 host_step=0x00;
					 host_rx_flag=0;
				 }
				 break;
				 
			 case 1:
			 {
         host_command[1]=host_rx;
				 host_step=0x02;
				 host_rx_flag=0;				 
				 break;
			 }
			case 2://05
			 {
         host_command[2]=host_rx;
				 host_step=0x03;
				 host_rx_flag=0;				 
				 break;
			 }

			 case 3://f1,f2,f3
			 {
				 host_command[3]=host_rx;
				 host_step=0x04;
				 host_rx_flag=0;
				 break;
			 }			 		
			 case 4:
			 {
				  if(0x40==host_rx)
				 {
					 host_command[4]=host_rx;
					 host_step=0x00;					
					 host_rx_flag=1;
					 USART_ClearFlag(USART2,USART_IT_RXNE);
					 USART_ClearITPendingBit(USART2,USART_IT_RXNE);
					 USART_Cmd(USART2,DISABLE);
				 }
				 else
				 {
					 host_command[0]=0x00;
					 host_command[1]=0x00;
					 host_command[2]=0x00;
					 host_command[3]=0x00;
					 host_command[4]=0x00;
					 host_command[5]=0x00;
					 host_command[6]=0x00;
					 
					 host_step=0x00;
					 host_rx_flag=0;							 
				 }
				 break;
			 }
			 default:
			 {

				 host_command[0]=0x00;
				 host_command[1]=0x00;
				 host_command[2]=0x00;
				 host_command[3]=0x00;
				 host_command[4]=0x00;
				 host_command[5]=0x00;
				 host_command[6]=0x00;
				 
				 host_step=0x00;
				 host_rx_flag=0;
			 }
		 }
		USART_ClearFlag(USART2,USART_IT_RXNE);
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	} 
		
}

/**
	* @brief   USART发送多个字节
	* @param   无
	* @retval  无
	*/
void usart_SendCmd(__IO uint8_t *cmd, uint8_t len)
{
	__IO uint8_t i = 0;
	
	for(i=0; i < len; i++) { usart_SendByte(cmd[i]); }
}

/**
	* @brief   USART发送一个字节
	* @param   无
	* @retval  无
	*/
void usart_SendByte(uint16_t data)
{
	__IO uint16_t t0 = 0;
	
	USART1->DR = (data & (uint16_t)0x01FF);

	while(!(USART1->SR & USART_FLAG_TXE))
	{
		++t0; if(t0 > 8000)	{	return; }
	}
}

void USART2_SendString(const char *str)  //发送文本消息
{
  while(*str) 
	{
		while (!(USART2->SR & USART_SR_TXE));
		USART_SendData(USART2, (uint16_t)(*str++));
  }
}

//函数检查 USART2 是否有数据可读，通过检查 USART_FLAG_RXNE 标志来实现。
int USART2_DataAvailable(void)
{
    return USART_GetFlagStatus(USART2, USART_FLAG_RXNE) != RESET;
}

// 函数从 USART2 接收数据
int USART2_ReceiveData(char *buffer, int bufferSize)
{
    int length = 0;
    while (USART2_DataAvailable() && length < bufferSize)
    {
        buffer[length++] = USART_ReceiveData(USART2);
    }
    return length;
}

void SendDataToUSART(USART_TypeDef *USARTx, char *buffer, int length)
{
    for (int i = 0; i < length; i++)
    {
        while (!(USARTx->SR & USART_SR_TXE)); // 等待发送缓冲区为空
        USARTx->DR = buffer[i]; // 发送一个字节的数据
    }
}
