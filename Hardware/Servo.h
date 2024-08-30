#ifndef __Servo_H
#define __Servo_H

#include "stm32f4xx.h" 
#include "stdbool.h"

// ������Ŷ��壬����ʵ�ʽ��߽����޸�
#define SERVO_PIN_1 GPIO_Pin_6       //PC6->TIM3_CH1
#define SERVO_PIN_2 GPIO_Pin_7       //PC7->TIM3_CH2
#define SERVO_PIN_3 GPIO_Pin_8      //PC8->TIM3_CH3
#define SERVO_PIN_4 GPIO_Pin_9      //PC9->TIM3_CH4

// �������ں������ȶ��壬���ݶ���ͺź�ʵ��Ҫ������޸�
#define PULSE_PERIOD 20000 // 20ms��һ������������Ϊ20ms
#define PULSE_WIDTH_MIN 1000 // ��С������
#define PULSE_WIDTH_MAX_270 2000 // 270�ȶ�����������
#define PULSE_WIDTH_MAX_180 1500 // 180�ȶ�����������

#define add_step 1

extern uint16_t Seted_Angle[4];
extern bool Add_or_Reduce;
extern uint8_t Servo_Step;
	
void setServoAngle(uint16_t angle1, uint16_t angle2, uint16_t angle3, uint16_t angle4);
void PWM(void);
void Rec_Set_Angle(uint16_t *Set_Angle);

#endif
