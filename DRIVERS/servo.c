#include "main.h"

void setServoAngle(uint16_t angle1, uint16_t angle2, uint16_t angle3, uint16_t angle4) {
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
void PWM(void) {
  // 初始化GPIO和TIM定时器，设置为PWM输出模式
  GPIO_InitTypeDef gpio_init;
  TIM_TimeBaseInitTypeDef tim_init;
  TIM_OCInitTypeDef oc_init;

  // 使能GPIO和TIM时钟，根据具体情况修改
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA| RCC_AHB1Periph_GPIOB, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  // 配置舵机引脚为复用推挽输出
  gpio_init.GPIO_Pin = SERVO_PIN_1 | SERVO_PIN_2 | SERVO_PIN_3 | SERVO_PIN_4;
	gpio_init.GPIO_OType = GPIO_OType_PP;
	gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
  gpio_init.GPIO_Mode = GPIO_Mode_AF;
  gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	
  GPIO_Init(GPIOA, &gpio_init);
  GPIO_Init(GPIOB, &gpio_init);

  // 配置TIM基本参数
  tim_init.TIM_Period = PULSE_PERIOD - 1; // 设置脉冲周期 ARR
  tim_init.TIM_Prescaler = 72-1; // 设置预分频 PSC
  tim_init.TIM_ClockDivision = TIM_CKD_DIV1;
  tim_init.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, &tim_init);

  // 配置TIM通道为PWM输出模式
  oc_init.TIM_OCMode = TIM_OCMode_PWM1;
  oc_init.TIM_OutputState = TIM_OutputState_Enable;
  oc_init.TIM_Pulse = 0; // 初始脉冲宽度为0，舵机不转动
  oc_init.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC1Init(TIM3, &oc_init);
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

  oc_init.TIM_Pulse = 0; // 初始脉冲宽度为0，舵机不转动
  oc_init.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC2Init(TIM3, &oc_init);
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

  oc_init.TIM_Pulse = 0; // 初始脉冲宽度为0，舵机不转动
  oc_init.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC3Init(TIM3, &oc_init);
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

  oc_init.TIM_Pulse = 0; // 初始脉冲宽度为0，舵机不转动
  oc_init.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC4Init(TIM3, &oc_init);
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

  // 启动定时器
  TIM_Cmd(TIM3, ENABLE);
}
