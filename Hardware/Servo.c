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
  // 将角度转换为对应的脉冲宽度
  uint16_t pulse_width1 = (angle1 / 270.0 * 2000 + 500) ; // 270度舵机
  uint16_t pulse_width2 = (angle2 / 180.0 * 2000 + 500) ; // 180度舵机
  uint16_t pulse_width3 = (angle3 / 180.0 * 2000 + 500) ; // 180度舵机
  uint16_t pulse_width4 = (angle4 / 180.0 * 2000 + 500) ; // 180度舵机

  // 设置PWM输出的脉冲宽度
  TIM_SetCompare1(TIM3, pulse_width1);
  TIM_SetCompare2(TIM3, pulse_width2);
  TIM_SetCompare3(TIM3, pulse_width3);
  TIM_SetCompare4(TIM3, pulse_width4);
}

void PWM(void) 
{
  // 初始化GPIO和TIM定时器，设置为PWM输出模式
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;

  // 使能GPIO和TIM时钟，根据具体情况修改
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);   //使能 GPIOC  外设时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);    //使能TIM3时钟
	
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3);  //引脚复用PC6->TIM3_CH1->SERVO_PIN_1
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3);  //引脚复用PC7->TIM3_CH2->SERVO_PIN_2
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM3);  //引脚复用PC8->TIM3_CH3->SERVO_PIN_3
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM3);  //引脚复用PC9->TIM3_CH4->SERVO_PIN_4

  // 配置舵机引脚为复用推挽输出
  GPIO_InitStructure.GPIO_Pin = SERVO_PIN_1 | SERVO_PIN_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;   //复用输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //推挽输出
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  //浮空
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = SERVO_PIN_3 | SERVO_PIN_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;   //复用输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //推挽输出
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  //浮空
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  // 配置TIM基本参数
  TIM_TimeBaseInitStructure.TIM_Period = PULSE_PERIOD - 1;  // 设置脉冲周期 ARR
  TIM_TimeBaseInitStructure.TIM_Prescaler = 84-1;  // 设置预分频 PSC
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //设置向上计数模式
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

  // 配置TIM通道为PWM输出模式
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0; // 初始脉冲宽度为0，舵机不转动
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //输出比较通道1初始化
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIMx在 CCR1 上的预装载寄存器

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0; // 初始脉冲宽度为0，舵机不转动
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0; // 初始脉冲宽度为0，舵机不转动
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0; // 初始脉冲宽度为0，舵机不转动
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

  // 启动定时器
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
