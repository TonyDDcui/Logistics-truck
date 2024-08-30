#include "board.h"


void nvic_init(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;        //子优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;       //子优先级0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;   //串口1中断通道
	NVIC_Init(&NVIC_InitStructure);
	//Usart2 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	//Usart3 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_Init(&NVIC_InitStructure);		
	//外部中断配置
	NVIC_InitStructure.NVIC_IRQChannel=EXTI4_IRQn;//外部中断4
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//使能外部中断4
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;//响应优先级28
	NVIC_Init(&NVIC_InitStructure);		
}


void clock_init(void)
{	
	// 使能 GPIOA GPIOB 外设时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB,ENABLE);

	// 使能 USART1 USART2 USART3 外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);	
	
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10复用为USART1
	
	//串口2对应引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA2复用为USART2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA3复用为USART2
	
	//串口3对应引脚复用映射
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOB10复用为USART3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOB11复用为USART3		
}


void usart_init(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	//USART1端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10 ; //GPIOA9 与 GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA9，PA10
	//USART2端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3 ; //GPIOA2 与 GPIOA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA2，PA3
	//USART3端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11 ; //GPIOB10 与 GPIOB11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure); //初始化PB10，PB11
	
	USART_InitTypeDef USART_InitStructure;
   //USART 初始化设置
	USART_InitStructure.USART_BaudRate = 115200;   //波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;    //字长为8位数据格式
	USART_InitStructure.USART_Parity = USART_Parity_No;      //无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   //无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;    //收发模式
	USART_Init(USART1, &USART_InitStructure);    //初始化串口1
	USART_Init(USART2, &USART_InitStructure);    //初始化串口2
	USART_Init(USART3, &USART_InitStructure);    //初始化串口3
	
	//USART 寄存器配置
	USART1->SR; USART1->DR;
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);

	USART2->SR; USART2->DR;
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	
	USART3->SR; USART3->DR;
	USART_ClearITPendingBit(USART3, USART_IT_RXNE);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);   //开启相关中断
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);   //开启相关中断
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);    //开启相关中断
	//USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);    //开启相关中断
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);    //开启相关中断
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);    //开启相关中断

	USART_Cmd(USART1, ENABLE);     //使能串口1 
	USART_Cmd(USART2, ENABLE);     //使能串口2
	USART_Cmd(USART3, ENABLE);     //使能串口3
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
