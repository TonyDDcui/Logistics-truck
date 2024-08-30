#include "stm32f4xx.h"
#include "stdio.h"
#include "board.h"
#include "delay.h"
#include "usart.h"
#include "Emm_V5.h"                 
#include "motor.h"
#include "user_task.h"
#include "oled.h"
#include <string.h>
#include "Servo.h"
#include "learn_task.h"
#include "esp8266.h"


int step_flag = 0;
int Recover_Step = 0;
bool learn_flag = 1;
bool wait_flag = 1;
User_Task task_volume[64];

void Init_task(User_Task *user_task);
bool Analyse_task(User_Task *user_task);

/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
int main()
{
	step_flag = 0;
	board_init();
	PWM();
	setServoAngle(45,90,0,180);
	for(int i = 0;i<9;i++)
	{
		Init_task(&task_volume[i]);
	}
	
	ESP8266_Init();
	ESP8266_APCreateWiFi("CAR","123456789");
	ESP8266_StartTCPServer(8080);
	delay_ms(1500);	
	
	Emm_V5_Reset_CurPos_To_Zero(1);
	delay_ms(1);
	
	while(1)
	{
		if(learn_flag)
		{
			GPIO_ResetBits(GPIOD, GPIO_Pin_3);
			while(Recover_Step < 64)
			{
				Init_task(&task_volume[Recover_Step]);
				Recover_Step++;
				delay_ms(10);
			}
			GPIO_SetBits(GPIOD, GPIO_Pin_5);
			Write_Task(&task_volume[learn_step]);
		}
		
		else{
			GPIO_ResetBits(GPIOD, GPIO_Pin_5);
			if(wait_flag)
			{
				setServoAngle(45,90,0,180);
				delay_ms(1500);
				wait_flag = 0;
			}
			GPIO_SetBits(GPIOD, GPIO_Pin_3);
			if(Analyse_task(&task_volume[step_flag])) step_flag++;
			else step_flag = 0;
		}
	}
}

void Init_task(User_Task *user_task)
{
	user_task->user_task_num = 0;
	user_task->motor_cycles = 0;
	user_task->motor_vel = 0;
	user_task->Servo1 = 0;
	user_task->Servo2 = 0;
	user_task->Servo3 = 0;
}

bool Analyse_task(User_Task *user_task)
{
	switch(user_task->user_task_num)
	{
		case 1:
			if(user_task->motor_cycles < 0) user_task->motor_cycles *= -1;
			forward(user_task->motor_cycles, 200);
			while(!stop_flag) stop_confirm();
			stop_flag = 0;
			return 1;
			
		case 2:
			if(user_task->motor_cycles < 0) user_task->motor_cycles *= -1;
			left(user_task->motor_cycles,200);
			while(!stop_flag) stop_confirm();
			stop_flag = 0;
			return 1;
			
		case 3:
			if(user_task->motor_cycles < 0) user_task->motor_cycles *= -1;
			right(user_task->motor_cycles,200);
			while(!stop_flag) stop_confirm();				
			stop_flag = 0;
			return 1;
			
		case 4:
			if(user_task->motor_cycles < 0) user_task->motor_cycles *= -1;
			back(user_task->motor_cycles,200);
			while(!stop_flag) stop_confirm();				
			stop_flag = 0;
			return 1;
			
		case 6:
			setServoAngle(user_task->Servo1,user_task->Servo2,user_task->Servo3,user_task->Servo4);
			delay_ms(1500);
			return 1;
			
		default:
			setServoAngle(45,90,0,180);
			delay_ms(1500);
			return 0;
	}
}

void EXTI4_IRQHandler(void)
{
	delay_ms(10);
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) == 0)
	{
		learn_flag = !learn_flag;
	}
	
	Emm_V5_Reset_CurPos_To_Zero(1);
	delay_ms(1);
	
	if(learn_flag == 1)
	{
		learn_stop();		
		
		step_flag = 0;
		wait_flag = 1;
	}
	else 
	{
		learn_step = 0;
		Recover_Step = 0;
	}
	setServoAngle(45,90,0,180);
	EXTI_ClearITPendingBit(EXTI_Line4);
}
