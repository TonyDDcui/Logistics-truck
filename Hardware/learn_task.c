#include "learn_task.h"

int fifo_task_num = 0,fifo_task_num_last = 0,Cmotor_receive = 0;
bool lock_Server_Step = 1;
bool Start_Set_Servo = 0;										//保证舵机4次在一个task中，防止松开按键后learn_step++
int learn_step = 0;
float Cmotor_Cycles = 0;
char host_run_command[7] = {0};

int Receive_Task(char *learn_task)
{
	switch(learn_task[1])
	{
		case 0x41:
			if(Start_Set_Servo) return 0;					//舵机状态下失效代码
			learn_forward();    //直行
		return 1;
		
		case 0x42:
			if(Start_Set_Servo) return 0;					//舵机状态下失效代码
			learn_back();       //后退
		return 4;
		
		case 0x43:
			if(Start_Set_Servo) return 0;					//舵机状态下失效代码
			learn_left();       //左转
		return 2;
		
		case 0x44:
			if(Start_Set_Servo) return 0;					//舵机状态下失效代码
			learn_right();      //右转
		return 3;
		
		case 0x45:
			learn_stop();       //停止
		return 5;
		
		case 0x46:
			Add_or_Reduce = 0;
			Rec_Set_Angle(Seted_Angle);
		return 6;
		
		case 0x47:
			Add_or_Reduce = 1;
			Rec_Set_Angle(Seted_Angle);
		return 6;
		
		case 0x48:
			if(lock_Server_Step) 											//防止出现不断累加的情况
			{
				Servo_Step++;
				lock_Server_Step = 0;
			}
		return 8;
		
		default:
			return 0;
	}
}

bool Write_Task(User_Task *write_task)
{
	Receive_Task(host_run_command);
	if(Refresh_Host()) fifo_task_num = Receive_Task(host_run_command);
	
	if(fifo_task_num != 0 && fifo_task_num != 5 && fifo_task_num != 8) 
	{
		write_task->user_task_num = fifo_task_num;
		if(fifo_task_num == 6) Start_Set_Servo = 1;
		fifo_task_num = 0;
		return 1;
	}
	else if(fifo_task_num == 5)
	{
		lock_Server_Step = 1;
		fifo_task_num = 0;
		if(Start_Set_Servo) 
		{
			if(Servo_Step >= 4)	
			{
				Servo_Step = 0;
				Start_Set_Servo = 0;
				learn_step += 1;
			}
			Emm_V5_Reset_CurPos_To_Zero(1);
			delay_ms(1);
			return 0;
		}
		ensure:
			Emm_V5_Read_Sys_Params(1,S_CPOS);
			delay_ms(1);
			while(!rxFrameFlag);
			if(rxCmd[0] == 0x01 && rxCmd[1] == 0x36 && rxCmd[7] == 0x6B)
			{
				Cmotor_receive = rxCmd[3] << 24 | rxCmd[4]<<16 | rxCmd[5]<<8 | rxCmd[6];
				Cmotor_Cycles = Cmotor_receive / 65536.0f;
				//if(rxCmd[2] == 0x01) Cmotor_Cycles = -Cmotor_Cycles;
				write_task->motor_cycles = Cmotor_Cycles;
				Emm_V5_Reset_CurPos_To_Zero(1);
				delay_ms(1);
				learn_step++;
				return 1;
			}
			else
			{
				goto ensure;
			}
	}
	
	else if(fifo_task_num == 8)
	{
		fifo_task_num = 0;
		
		if(write_task->user_task_num == 0)	
		{
			write_task->user_task_num = 6;
			Start_Set_Servo = 1;
		}
		
		switch(Servo_Step)
		{
			case 1:
				write_task->Servo1 = Seted_Angle[0];
			break;
			
			case 2:
				write_task->Servo2 = Seted_Angle[1];
			break;
			
			case 3:
				write_task->Servo3 = Seted_Angle[2];
			break;
			
			case 4:
				write_task->Servo4 = Seted_Angle[3];
			break;
		}
		return 0;
	}
	else return 0;
}

bool Refresh_Host(void)
{
	if(host_rx_flag)
	{
		for(int i = 0;i<7;i++)
		{
			host_run_command[i] = host_command[i];
		}
		host_rx_flag = 0;
		USART_Cmd(USART2,ENABLE);
		return 1;
	}
	else return 0;
}
