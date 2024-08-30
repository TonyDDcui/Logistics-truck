#ifndef _USER_TASK_H
#define _USER_TASK_H

#include "usart.h"
#include "Servo.h"

void display_fun(void);
void catch_task(void);
extern int catch_count;
extern int order_list[10];
#endif
