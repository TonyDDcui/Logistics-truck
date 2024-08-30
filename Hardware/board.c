#include "board.h"


void nvic_init(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;        //�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;       //�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;   //����1�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);
	//Usart2 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	//Usart3 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_Init(&NVIC_InitStructure);		
	//�ⲿ�ж�����
	NVIC_InitStructure.NVIC_IRQChannel=EXTI4_IRQn;//�ⲿ�ж�4
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//ʹ���ⲿ�ж�4
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;//��Ӧ���ȼ�28
	NVIC_Init(&NVIC_InitStructure);		
}


void clock_init(void)
{	
	// ʹ�� GPIOA GPIOB ����ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB,ENABLE);

	// ʹ�� USART1 USART2 USART3 ����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);	
	
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10����ΪUSART1
	
	//����2��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA2����ΪUSART2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA3����ΪUSART2
	
	//����3��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOB10����ΪUSART3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOB11����ΪUSART3		
}


void usart_init(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	//USART1�˿�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10 ; //GPIOA9 �� GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA9��PA10
	//USART2�˿�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3 ; //GPIOA2 �� GPIOA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA2��PA3
	//USART3�˿�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11 ; //GPIOB10 �� GPIOB11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOB,&GPIO_InitStructure); //��ʼ��PB10��PB11
	
	USART_InitTypeDef USART_InitStructure;
   //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = 115200;   //����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;    //�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_Parity = USART_Parity_No;      //����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   //��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;    //�շ�ģʽ
	USART_Init(USART1, &USART_InitStructure);    //��ʼ������1
	USART_Init(USART2, &USART_InitStructure);    //��ʼ������2
	USART_Init(USART3, &USART_InitStructure);    //��ʼ������3
	
	//USART �Ĵ�������
	USART1->SR; USART1->DR;
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);

	USART2->SR; USART2->DR;
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	
	USART3->SR; USART3->DR;
	USART_ClearITPendingBit(USART3, USART_IT_RXNE);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);   //��������ж�
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);   //��������ж�
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);    //��������ж�
	//USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);    //��������ж�
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);    //��������ж�
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);    //��������ж�

	USART_Cmd(USART1, ENABLE);     //ʹ�ܴ���1 
	USART_Cmd(USART2, ENABLE);     //ʹ�ܴ���2
	USART_Cmd(USART3, ENABLE);     //ʹ�ܴ���3
}

void Key_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource4);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
}

void LED_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	
	GPIO_Init(GPIOD,&GPIO_InitStructure);
}
	
void board_init(void)
{
	nvic_init();
	clock_init();
	usart_init();
	Key_init();
	LED_Init();
}
