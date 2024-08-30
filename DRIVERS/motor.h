#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "main.h"
#include "stdbool.h"

//注：1,3两个轮子在1时是后退，0是向前
//注：2,4两个轮子在1时是向前，0是向后

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
