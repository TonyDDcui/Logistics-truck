#include "user_task.h"
#include "delay.h"
#include "oled.h"
#include "usart.h"
#include "motor.h"

unsigned char line_x=0;
int order_list[10];
int catch_count=0;
bool tx_flag = 0;
int ang_list[]={220,180,135};

void catch_task()
{
	if(!tx_flag) 
	{
		USART_SendData(USART3,0xA2);
		tx_flag = 1;
	}
	while(!rx_flag);
	delay_ms(5);
	if(order_list[0] == openmv_receive[10])
	{
		delay_ms(10);
		setServoAngle(0,30,60,0);
		delay_ms(1000);
		for(int i = 30;i>=0;i--)
		{
			setServoAngle(0,i,60,0);
			delay_ms(10);
		}
		delay_ms(1000);
		for(int i = 60;i<=125;i++)
		{
			setServoAngle(0,0,i,0);
			delay_ms(10);
		}
		delay_ms(1000);
		setServoAngle(0,0,125,180);
		delay_ms(2000);
		for(int i = 125;i>=60;i--)
		{
			setServoAngle(0,0,i,180);
			delay_ms(10);
		}
		for(int i = 0;i<=30;i++)
		{
			setServoAngle(0,i,60,180);
			delay_ms(10);
		}
		delay_ms(1000);
		setServoAngle(220,30,60,180);
		delay_ms(3000);
		setServoAngle(220,30,60,0);
		delay_ms(1000);		
		setServoAngle(0,30,60,0);
		
		catch_count +=1;
		rx_flag = 0;
	}
	
	if(order_list[1] == openmv_receive[10] && catch_count == 1)
	{
		delay_ms(10);
		setServoAngle(0,30,60,0);
		delay_ms(1000);
		for(int i = 30;i>=0;i--)
		{
			setServoAngle(0,i,60,0);
			delay_ms(10);
		}
		delay_ms(1000);
		for(int i = 60;i<=125;i++)
		{
			setServoAngle(0,0,i,0);
			delay_ms(10);
		}
		delay_ms(1000);
		setServoAngle(0,0,125,180);
		delay_ms(2000);
		for(int i = 125;i>=60;i--)
		{
			setServoAngle(0,0,i,180);
			delay_ms(10);
		}
		for(int i = 0;i<=30;i++)
		{
			setServoAngle(0,i,60,180);
			delay_ms(10);
		}
		delay_ms(1000);
		setServoAngle(180,30,60,180);
		delay_ms(3000);
		setServoAngle(180,30,60,0);
		delay_ms(1000);		
		setServoAngle(0,30,60,0);
		catch_count +=1;
		rx_flag = 0;
	}	
	
	if(order_list[2] == openmv_receive[10] && catch_count == 2 )
	{
		delay_ms(10);
		setServoAngle(0,30,60,0);
		delay_ms(1000);
		for(int i = 30;i>=0;i--)
		{
			setServoAngle(0,i,60,0);
			delay_ms(10);
		}
		delay_ms(1000);
		for(int i = 60;i<=125;i++)
		{
			setServoAngle(0,0,i,0);
			delay_ms(10);
		}
		delay_ms(1000);
		setServoAngle(0,0,125,180);
		delay_ms(2000);
		for(int i = 125;i>=60;i--)
		{
			setServoAngle(0,0,i,180);
			delay_ms(10);
		}
		for(int i = 0;i<=30;i++)
		{
			setServoAngle(0,i,60,180);
			delay_ms(10);
		}
		delay_ms(1000);
		setServoAngle(135,30,60,180);
		delay_ms(3000);
		setServoAngle(135,30,60,0);
		delay_ms(1000);		
		setServoAngle(0,30,60,0);
		delay_ms(2000);
		catch_count +=1;
		rx_flag = 0;
	}	
}

void catch_task3()
{
	setServoAngle(0,30,60,0);
	while(catch_count != 3)
	{
		while(!rx_flag);
		delay_ms(5);
		int j = 0;
		setServoAngle(ang_list[j],30,60,0);
		if(order_list[3] == openmv_receive[10])
		{
			for(int i = 30;i>=0;i--)
			{
				setServoAngle(ang_list[j],i,60,0);
				delay_ms(10);
			}
			delay_ms(1000);
			for(int i = 60;i<=125;i++)
			{
				setServoAngle(ang_list[j],0,i,0);
				delay_ms(10);
			}
			delay_ms(1000);
			setServoAngle(ang_list[j],0,125,180);
			delay_ms(2000);
			for(int i = 125;i>=60;i--)
			{
				setServoAngle(ang_list[j],0,i,180);
				delay_ms(10);
			}
			for(int i = 0;i<=30;i++)
			{
				setServoAngle(ang_list[j],i,60,180);
				delay_ms(10);
			}
			delay_ms(1000);
			setServoAngle(0,30,60,180);
			delay_ms(2000);
			setServoAngle(0,30,60,0);
			delay_ms(1000);		
			setServoAngle(0,30,60,0);
			
			catch_count +=1;
			rx_flag = 0;
			j = 0;
		}
		else 
		{
			j+=1;
			if(j > 2)j = 0;
		}
		if(order_list[4] == openmv_receive[10] && catch_count == 1)
		{
			for(int i = 30;i>=0;i--)
			{
				setServoAngle(0,i,60,0);
				delay_ms(10);
			}
			delay_ms(1000);
			for(int i = 60;i<=125;i++)
			{
				setServoAngle(0,0,i,0);
				delay_ms(10);
			}
			delay_ms(1000);
			setServoAngle(0,0,125,180);
			delay_ms(2000);
			for(int i = 125;i>=60;i--)
			{
				setServoAngle(0,0,i,180);
				delay_ms(10);
			}
			for(int i = 0;i<=30;i++)
			{
				setServoAngle(0,i,60,180);
				delay_ms(10);
			}
			delay_ms(1000);
			setServoAngle(180,30,60,180);
			delay_ms(3000);
			setServoAngle(180,30,60,0);
			delay_ms(1000);		
			setServoAngle(0,30,60,0);
			catch_count +=1;
			rx_flag = 0;
			j = 0;
		}	
		
		if(order_list[5] == openmv_receive[10] && catch_count == 2 )
		{
			for(int i = 30;i>=0;i--)
			{
				setServoAngle(0,i,60,0);
				delay_ms(10);
			}
			delay_ms(1000);
			for(int i = 60;i<=125;i++)
			{
				setServoAngle(0,0,i,0);
				delay_ms(10);
			}
			delay_ms(1000);
			setServoAngle(0,0,125,180);
			delay_ms(2000);
			for(int i = 125;i>=60;i--)
			{
				setServoAngle(0,0,i,180);
				delay_ms(10);
			}
			for(int i = 0;i<=30;i++)
			{
				setServoAngle(0,i,60,180);
				delay_ms(10);
			}
			delay_ms(1000);
			setServoAngle(135,30,60,180);
			delay_ms(3000);
			setServoAngle(135,30,60,0);
			delay_ms(1000);		
			setServoAngle(0,30,60,0);
			delay_ms(2000);
			catch_count +=1;
			rx_flag = 0;
			j = 0;
		}
	}		
}


void display_fun()
{
	for(int i = 10;i<=rx_num-1;i++)
	{
		OledShowASCII(line_x,0,openmv_receive[i]);
		if(openmv_receive[i] != '+')
		{
			order_list[i-10] = openmv_receive[i];
		}
		line_x+=15;
	}
}
