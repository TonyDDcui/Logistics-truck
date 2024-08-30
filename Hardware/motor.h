#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "Emm_V5.h"
#include "delay.h"
#include "fifo.h"
#include "stdbool.h"

extern bool run_flag;
extern bool stop_flag;
extern int vel_user;

typedef struct
{
	int user_task_num;
	float motor_cycles;
	int motor_vel;
	uint16_t Servo1;
	uint16_t Servo2;
	uint16_t Servo3;
	uint16_t Servo4;
}User_Task;

#define arr_user 196

void forward(float pulse,int vel_user);
void left(float pulse,int vel_user);
void left_turn(float pulse,int vel_user);
void right(float pulse,int vel_user);
void left(float pulse,int vel_user);
void right_turn(float pulse,int vel_user);
void back(float pulse,int vel_user);
void stop_confirm(void);
void confirm(uint8_t num_wheel);

void learn_forward(void);
void learn_back(void);
void learn_left(void);
void learn_right(void);
void learn_stop(void);

#endif
