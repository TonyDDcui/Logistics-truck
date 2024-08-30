#include "stm32f4xx_tim.h"
#include "Servo.h"
#include "delay.h"
#include "stdbool.h"

uint16_t Seted_Angle[4] = {45,90,0,180};
bool Add_or_Reduce = 0;										//0:+;1:-
uint8_t Servo_Step = 0;
uint16_t duty_latest = 0;
uint16_t duty_now = 0;

void setServoAngle(uint16_t angle1, uint16_t angle2, uint16_t angle3, uint16_t angle4) 
{
  // ���Ƕ�ת��Ϊ��Ӧ��������
  uint16_t pulse_width1 = (angle1 / 270.0 * 2000 + 500) ; // 270�ȶ��
  uint16_t pulse_width2 = (angle2 / 180.0 * 2000 + 500) ; // 180�ȶ��
  uint16_t pulse_width3 = (angle3 / 180.0 * 2000 + 500) ; // 180�ȶ��
  uint16_t pulse_width4 = (angle4 / 180.0 * 2000 + 500) ; // 180�ȶ��

  // ����PWM�����������
  TIM_SetCompare1(TIM3, pulse_width1);
  TIM_SetCompare2(TIM3, pulse_width2);
  TIM_SetCompare3(TIM3, pulse_width3);
  TIM_SetCompare4(TIM3, pulse_width4);
}

void PWM(void) 
{
  // ��ʼ��GPIO��TIM��ʱ��������ΪPWM���ģʽ
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;

  // ʹ��GPIO��TIMʱ�ӣ����ݾ�������޸�
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);   //ʹ�� GPIOC  ����ʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);    //ʹ��TIM3ʱ��
	
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3);  //���Ÿ���PC6->TIM3_CH1->SERVO_PIN_1
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3);  //���Ÿ���PC7->TIM3_CH2->SERVO_PIN_2
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM3);  //���Ÿ���PC8->TIM3_CH3->SERVO_PIN_3
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM3);  //���Ÿ���PC9->TIM3_CH4->SERVO_PIN_4

  // ���ö������Ϊ�����������
  GPIO_InitStructure.GPIO_Pin = SERVO_PIN_1 | SERVO_PIN_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;   //�������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //�������
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  //����
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = SERVO_PIN_3 | SERVO_PIN_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;   //�������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //�������
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  //����
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  // ����TIM��������
  TIM_TimeBaseInitStructure.TIM_Period = PULSE_PERIOD - 1;  // ������������ ARR
  TIM_TimeBaseInitStructure.TIM_Prescaler = 84-1;  // ����Ԥ��Ƶ PSC
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //�������ϼ���ģʽ
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

  // ����TIMͨ��ΪPWM���ģʽ
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0; // ��ʼ������Ϊ0�������ת��
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //����Ƚ�ͨ��1��ʼ��
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIMx�� CCR1 �ϵ�Ԥװ�ؼĴ���

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0; // ��ʼ������Ϊ0�������ת��
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0; // ��ʼ������Ϊ0�������ת��
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0; // ��ʼ������Ϊ0�������ת��
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

  // ������ʱ��
  TIM_Cmd(TIM3, ENABLE);
}

void Rec_Set_Angle(uint16_t *Set_Angle)
{
	if(Add_or_Reduce)	
	{
		*(Set_Angle+Servo_Step) -= add_step;
		if(*(Set_Angle+Servo_Step) < 5)	*(Set_Angle+Servo_Step) = 5;
	}
	
	else
	{
		*(Set_Angle+Servo_Step) += add_step;
		if(Servo_Step == 1 && *(Set_Angle+Servo_Step) >270) *(Set_Angle+Servo_Step) = 270;
		else if(*(Set_Angle+Servo_Step) >180) *(Set_Angle+Servo_Step) = 180;
	}
	
	setServoAngle(*Set_Angle,*(Set_Angle+1),*(Set_Angle+2),*(Set_Angle+3));
	delay_ms(10);
}
