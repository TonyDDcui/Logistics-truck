#include "usart.h"
#include <string.h>
#include "delay.h"

__IO bool rxFrameFlag = false;
__IO uint8_t rxCmd[FIFO_SIZE] = {0};
__IO uint8_t rxCount = 0;

int rx_count=0,rx_count_old=0;
char openmv_receive[64],openmv_fifo[64];
int rx_num=0;
char standard[]="QRconfirm";
char standard_ts2[]="WLconfirm";
bool rx_flag=0;
size_t n = 9;

/**
	* @brief   USART1�жϺ���
	* @param   ��
	* @retval  ��
	*/
void USART1_IRQHandler(void)
{
	__IO uint16_t i = 0;

/**********************************************************
***	���ڽ����ж�
**********************************************************/
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		// δ���һ֡���ݽ��գ����ݽ��뻺�����
		fifo_enQueue((uint8_t)USART1->DR);

		// ������ڽ����ж�
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}

/**********************************************************
***	���ڿ����ж�
**********************************************************/
	else if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
	{
		// �ȶ�SR�ٶ�DR�����IDLE�ж�
		USART1->SR; USART1->DR;

		// ��ȡһ֡��������
		rxCount = fifo_queueLength(); for(i=0; i < rxCount; i++) { rxCmd[i] = fifo_deQueue(); }

		// һ֡���ݽ�����ɣ���λ֡��־λ
		rxFrameFlag = true;
	}
}

void USART3_IRQHandler()
{
	int i = 0;
	if(USART_GetITStatus(USART3,USART_IT_RXNE))
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
				for(i=0;i<=rx_count;i++)
				{
					openmv_receive[i] = openmv_fifo[i];
				}
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
	int i =0;
	if(USART_GetITStatus(USART2,USART_IT_RXNE))
	{
		openmv_fifo[rx_count] = USART2->DR;
		++rx_count;
		if(!strcmp(openmv_fifo,standard) || !strcmp(openmv_fifo,standard_ts2)) rx_count_old = rx_count;
		USART_ClearFlag(USART2,USART_IT_RXNE);
	}
	else if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)
	{
		USART2->SR; USART2->DR;
		if(!strncmp(openmv_fifo,standard,n))
		{
			if((rx_count - rx_count_old-1) == ((int)openmv_fifo[9]-0x30))
			{
				for(i=0;i<=rx_count;i++) 
				{
					openmv_receive[i] = openmv_fifo[i];
				}
				rx_flag = 1;
				rx_num = rx_count;
			}
		}
		memset(openmv_fifo,0,sizeof(openmv_fifo));
		rx_count = 0;
	}
}

/**
	* @brief   USART���Ͷ���ֽ�
	* @param   ��
	* @retval  ��
	*/
void usart_SendCmd(__IO uint8_t *cmd, uint8_t len)
{
	__IO uint8_t i = 0;
	
	for(i=0; i < len; i++) { usart_SendByte(cmd[i]); }
}

/**
	* @brief   USART����һ���ֽ�
	* @param   ��
	* @retval  ��
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


