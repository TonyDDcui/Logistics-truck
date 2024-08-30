#include "motor.h"

bool run_flag = 0;
bool stop_flag = 0;
int pos = 0;
double Set_ang = 0.0f;
int vel_user = 200;

void left(double pulse)
{
	Set_ang = pulse*360/1.8*16;
	pos = (uint32_t)Set_ang;
	
	Emm_V5_Pos_Control(1,1,vel_user,arr_user,pos,0,1);
	delay_ms(1);
	
	Emm_V5_Pos_Control(2,1,vel_user,arr_user,pos,0,1);
	delay_ms(1);
	
	Emm_V5_Pos_Control(3,0,vel_user,arr_user,pos,0,1);
	delay_ms(1);
	
	Emm_V5_Pos_Control(4,0,vel_user,arr_user,pos,0,1);
	delay_ms(1);
		
	Emm_V5_Synchronous_motion(0);
	delay_ms(1);
	
	run_flag = 1;
}

void right(double pulse)
{
	Set_ang = pulse*360/1.8*16;
	pos = (uint32_t)Set_ang;
	
	Emm_V5_Pos_Control(1,0,vel_user,arr_user,pos,0,1);
	delay_ms(1);
	
	Emm_V5_Pos_Control(2,0,vel_user,arr_user,pos,0,1);
	delay_ms(1);
	
	Emm_V5_Pos_Control(3,1,vel_user,arr_user,pos,0,1);
	delay_ms(1);
	
	Emm_V5_Pos_Control(4,1,vel_user,arr_user,pos,0,1);
	delay_ms(1);
		
	Emm_V5_Synchronous_motion(0);
	
	run_flag = 1;
	
	delay_ms(1);
}


void forward(double pulse)
{
	Set_ang = pulse*360/1.8*16;
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

void back(double pulse)
{
	Set_ang = pulse*360/1.8*16;
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

void left_turn(double pulse)
{
	Set_ang = pulse*360/1.8*16;
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

void right_turn(double pulse)
{
	Set_ang = pulse*360.0/1.8*16.0;
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
	int i = 1;
	for(i = 1;i<=4;i++)
	{
		delay_ms(20);
		confirm(i);
	}
}
