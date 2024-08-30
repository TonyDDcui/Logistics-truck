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

void USART2_SendString(const char *str)  //�����ı���Ϣ
{
  while(*str) 
	{
		while (!(USART2->SR & USART_SR_TXE));
		USART_SendData(USART2, (uint16_t)(*str++));
  }
}

//������� USART2 �Ƿ������ݿɶ���ͨ����� USART_FLAG_RXNE ��־��ʵ�֡�
int USART2_DataAvailable(void)
{
    return USART_GetFlagStatus(USART2, USART_FLAG_RXNE) != RESET;
}

// ������ USART2 ��������
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
        while (!(USARTx->SR & USART_SR_TXE)); // �ȴ����ͻ�����Ϊ��
        USARTx->DR = buffer[i]; // ����һ���ֽڵ�����
    }
}
