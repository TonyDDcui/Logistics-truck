#ifndef __Servo_H
#define __Servo_H

#include "main.h"

// 舵机引脚定义，根据实际接线进行修改
#define SERVO_PIN_1 GPIO_Pin_6
#define SERVO_PIN_2 GPIO_Pin_7
#define SERVO_PIN_3 GPIO_Pin_0
#define SERVO_PIN_4 GPIO_Pin_1

// 脉冲周期和脉冲宽度定义，根据舵机型号和实际要求进行修改
#define PULSE_PERIOD 20000 // 20ms，一般舵机脉冲周期为20ms
#define PULSE_WIDTH_MIN 1000 // 最小脉冲宽度
#define PULSE_WIDTH_MAX_270 2000 // 270度舵机最大脉冲宽度
#define PULSE_WIDTH_MAX_180 1500 // 180度舵机最大脉冲宽度

void setServoAngle(uint16_t angle1, uint16_t angle2, uint16_t angle3, uint16_t angle4);
void PWM(void);
#endif
