#include "config.h"



unsigned int Number_Down[Down_Task];     //��ʱ-- ����
/*******************************************************************************
* �������� : ������ʱ
* ����˵�� : �ж�1ms����һ��
*******************************************************************************/
void TaskDelay()
{
    unsigned char i;

    for(i = 0; i < Down_Task; i++)
    {
        if(Number_Down[i])//��Ϊ0��--
        {
            Number_Down[i]--; //��Ϊ0��--
        }
    }
}

void delay_us(u32 nus)
{
 u32 temp;
 SysTick->LOAD = 9*nus;
 SysTick->VAL=0X00;//��ռ�����
 SysTick->CTRL=0X01;//ʹ�ܣ����������޶����������ⲿʱ��Դ
 do
 {
  temp=SysTick->CTRL;//��ȡ��ǰ������ֵ
 }while((temp&0x01)&&(!(temp&(1<<16))));//�ȴ�ʱ�䵽��
     SysTick->CTRL=0x00; //�رռ�����
    SysTick->VAL =0X00; //��ռ�����
}
void delay_ms1(u16 nms)
{
 u32 temp;
 SysTick->LOAD = 9000*nms;
 SysTick->VAL=0X00;//��ռ�����
 SysTick->CTRL=0X01;//ʹ�ܣ����������޶����������ⲿʱ��Դ
 do
 {
  temp=SysTick->CTRL;//��ȡ��ǰ������ֵ
 }while((temp&0x01)&&(!(temp&(1<<16))));//�ȴ�ʱ�䵽��
    SysTick->CTRL=0x00; //�رռ�����
    SysTick->VAL =0X00; //��ռ�����
}



/* 1/4΢����ʱ����(���������ü�����ʱ�乲�ƺ�ʱԼ1/4΢��@72MHz��Ƶ) */
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
