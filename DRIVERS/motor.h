#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "main.h"
#include "stdbool.h"

//ע��1,3����������1ʱ�Ǻ��ˣ�0����ǰ
//ע��2,4����������1ʱ����ǰ��0�����

extern bool run_flag;
extern bool stop_flag;
extern int vel_user;

#define arr_user 196

void forward(double pulse);
void left(double pulse);
void left_turn(double pulse);
void right(double pulse);
void left(double pulse);
void right_turn(double pulse);
void stop_confirm(void);
void back(double pulse);
void confirm(uint8_t num_wheel);

#endif
