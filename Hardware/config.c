#include "config.h"



unsigned int Number_Down[Down_Task];     //延时-- 数组
/*******************************************************************************
* 函数功能 : 任务延时
* 函数说明 : 中断1ms调用一次
*******************************************************************************/
void TaskDelay()
{
    unsigned char i;

    for(i = 0; i < Down_Task; i++)
    {
        if(Number_Down[i])//不为0就--
        {
            Number_Down[i]--; //不为0就--
        }
    }
}

void delay_us(u32 nus)
{
 u32 temp;
 SysTick->LOAD = 9*nus;
 SysTick->VAL=0X00;//清空计数器
 SysTick->CTRL=0X01;//使能，减到零是无动作，采用外部时钟源
 do
 {
  temp=SysTick->CTRL;//读取当前倒计数值
 }while((temp&0x01)&&(!(temp&(1<<16))));//等待时间到达
     SysTick->CTRL=0x00; //关闭计数器
    SysTick->VAL =0X00; //清空计数器
}
void delay_ms1(u16 nms)
{
 u32 temp;
 SysTick->LOAD = 9000*nms;
 SysTick->VAL=0X00;//清空计数器
 SysTick->CTRL=0X01;//使能，减到零是无动作，采用外部时钟源
 do
 {
  temp=SysTick->CTRL;//读取当前倒计数值
 }while((temp&0x01)&&(!(temp&(1<<16))));//等待时间到达
    SysTick->CTRL=0x00; //关闭计数器
    SysTick->VAL =0X00; //清空计数器
}



/* 1/4微秒延时函数(含函数调用及返回时间共计耗时约1/4微妙@72MHz主频) */
void delay_qus(void)
{
	__ASM ("nop");
	__ASM ("nop");
	__ASM ("nop");
	__ASM ("nop");
	__ASM ("nop");
	__ASM ("nop");
	__ASM ("nop");
	__ASM ("nop");
}
