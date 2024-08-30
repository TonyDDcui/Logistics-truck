#include "motor.h"

bool run_flag = 0;
bool stop_flag = 0;
int pos = 0;
float Set_ang = 0.0f;

//1-4;2-3

void left(float pulse,int vel_user)
{
	Set_ang = pulse*360/1.8f*16;
	pos = (uint32_t)Set_ang;
	
	Emm_V5_Pos_Control(1,1,vel_user,arr_user,pos,0,1);
	delay_ms(1);
	
	Emm_V5_Pos_Control(2,1,vel_user,arr_user,pos,0,1);
	delay_ms(1);
	
	Emm_V5_Pos_Control(3,1,vel_user,arr_user,pos,0,1);
	delay_ms(1);
	
	Emm_V5_Pos_Control(4,1,vel_user,arr_user,pos,0,1);
	delay_ms(1);
		
	Emm_V5_Synchronous_motion(0);
	delay_ms(1);
	
	run_flag = 1;
}

void right(float pulse,int vel_user)
{
	Set_ang = pulse*360/1.8f*16;
	pos = (uint32_t)Set_ang;
	
	Emm_V5_Pos_Control(1,0,vel_user,arr_user,pos,0,1);
	delay_ms(1);
	
	Emm_V5_Pos_Control(2,0,vel_user,arr_user,pos,0,1);
	delay_ms(1);
	
	Emm_V5_Pos_Control(3,0,vel_user,arr_user,pos,0,1);
	delay_ms(1);
	
	Emm_V5_Pos_Control(4,0,vel_user,arr_user,pos,0,1);
	delay_ms(1);
		
	Emm_V5_Synchronous_motion(0);
	
	run_flag = 1;
	
	delay_ms(1);
}


void forward(float pulse,int vel_user)
{
	Set_ang = pulse*360/1.8f*16;
	pos = (uint32_t)Set_ang;
	
	Emm_V5_Pos_Control(1,0,vel_user,arr_user,pos,0,1);
	delay_ms(1);
	
	Emm_V5_Pos_Control(2,1,vel_user,arr_user,pos,0,1);
	delay_ms(1);
	
	Emm_V5_Pos_Control(3,0,vel_user,arr_user,pos,0,1);
	delay_ms(1);
	
	Emm_V5_Pos_Control(4,1,vel_user,arr_user,pos,0,1);
	delay_ms(1);
	
	Emm_V5_Synchronous_motion(0);
	delay_ms(1);
	
	run_flag = 1;
	
	delay_ms(1);
}

void back(float pulse,int vel_user)
{
	Set_ang = pulse*360/1.8f*16;
	pos = (uint32_t)Set_ang;
	
	Emm_V5_Pos_Control(1,1,vel_user,arr_user,pos,0,1);
	delay_ms(1);
	
	Emm_V5_Pos_Control(2,0,vel_user,arr_user,pos,0,1);
	delay_ms(1);
	
	Emm_V5_Pos_Control(3,1,vel_user,arr_user,pos,0,1);
	delay_ms(1);
	
	Emm_V5_Pos_Control(4,0,vel_user,arr_user,pos,0,1);
	delay_ms(1);
	
	Emm_V5_Synchronous_motion(0);
	delay_ms(1);
	
	run_flag = 1;
	
	delay_ms(1);
}

void left_turn(float pulse,int vel_user)
{
	Set_ang = pulse*360/1.8f*16;
	pos = (uint32_t)Set_ang;
	
	Emm_V5_Pos_Control(1,1,vel_user,arr_user,pos,0,1);
	delay_ms(1);
	
	Emm_V5_Pos_Control(2,1,vel_user,arr_user,pos,0,1);
	delay_ms(1);
	
	Emm_V5_Pos_Control(3,1,vel_user,arr_user,pos,0,1);
	delay_ms(1);
	
	Emm_V5_Pos_Control(4,1,vel_user,arr_user,pos,0,1);
	delay_ms(1);
	
	Emm_V5_Synchronous_motion(0);
	delay_ms(1);
	
	run_flag = 1;
	
	delay_ms(1);
}

void right_turn(float pulse,int vel_user)
{
	Set_ang = pulse*360/1.8f*16;
	pos = (uint32_t)Set_ang;
	
	Emm_V5_Pos_Control(1,0,vel_user,arr_user,pos,0,1);
	delay_ms(1);
	
	Emm_V5_Pos_Control(2,0,vel_user,arr_user,pos,0,1);
	delay_ms(1);
	
	Emm_V5_Pos_Control(3,0,vel_user,arr_user,pos,0,1);
	delay_ms(1);
	
	Emm_V5_Pos_Control(4,0,vel_user,arr_user,pos,0,1);
	delay_ms(1);
	
	Emm_V5_Synchronous_motion(0);
	delay_ms(1);
	
	run_flag = 1;
	
	delay_ms(1);
}

void confirm(uint8_t num_wheel)
{
	Emm_V5_Read_Sys_Params(num_wheel,S_VEL);
	delay_ms(1);
	if(rxCmd[0] == num_wheel && rxCmd[1] == 0x35 && rxCount == 6)
	{
		if(rxCmd[2]==0&&rxCmd[3]==0&&rxCmd[4]==0) stop_flag = 1;
		else stop_flag = 0;
	}	
}

void stop_confirm()
{
	for(int i = 1;i<=4;i++)
	{
		delay_ms(20);
		confirm(i);
	}
}

void learn_forward(void)
{
	Emm_V5_Vel_Control(1,0,200,0,1);
	delay_ms(1);
	
	Emm_V5_Vel_Control(2,1,200,0,1);
	delay_ms(1);
	
	Emm_V5_Vel_Control(3,0,200,0,1);
	delay_ms(1);
	
	Emm_V5_Vel_Control(4,1,200,0,1);
	delay_ms(1);
	
	Emm_V5_Synchronous_motion(0);
	delay_ms(1);	
}

void learn_back(void)
{
	Emm_V5_Vel_Control(1,1,200,0,1);
	delay_ms(1);
	
	Emm_V5_Vel_Control(2,0,200,0,1);
	delay_ms(1);
	
	Emm_V5_Vel_Control(3,1,200,0,1);
	delay_ms(1);
	
	Emm_V5_Vel_Control(4,0,200,0,1);
	delay_ms(1);
	
	Emm_V5_Synchronous_motion(0);
	delay_ms(1);		
}

void learn_left(void)
{
	Emm_V5_Vel_Control(1,1,100,0,1);
	delay_ms(1);
	
	Emm_V5_Vel_Control(2,1,100,0,1);
	delay_ms(1);
	
	Emm_V5_Vel_Control(3,1,100,0,1);
	delay_ms(1);
	
	Emm_V5_Vel_Control(4,1,100,0,1);
	delay_ms(1);
	
	Emm_V5_Synchronous_motion(0);
	delay_ms(1);		
}

void learn_right(void)
{
	Emm_V5_Vel_Control(1,0,100,0,1);
	delay_ms(1);
	
	Emm_V5_Vel_Control(2,0,100,0,1);
	delay_ms(1);
	
	Emm_V5_Vel_Control(3,0,100,0,1);
	delay_ms(1);
	
	Emm_V5_Vel_Control(4,0,100,0,1);
	delay_ms(1);
	
	Emm_V5_Synchronous_motion(0);
	delay_ms(1);
}

void learn_stop(void)
{
	Emm_V5_Stop_Now(1,1);
	delay_ms(1);
	Emm_V5_Stop_Now(2,1);
	delay_ms(1);
	Emm_V5_Stop_Now(3,1);
	delay_ms(1);
	Emm_V5_Stop_Now(4,1);
	delay_ms(1);
	Emm_V5_Synchronous_motion(0);
	delay_ms(1);
}
