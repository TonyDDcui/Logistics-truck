#ifndef _LEARN_TASK_H_
#define _LEARN_TASK_H_

#include "motor.h"
#include "usart.h"
#include "Servo.h"

extern int learn_step;

int Receive_Task(char *learn_task);
bool Write_Task(User_Task *write_task);
bool Refresh_Host(void);
#endif
