#ifndef _CONFIG_H
#define _CONFIG_H
#include "stm32f4xx.h"




enum //延时任务枚举  最后参数不要加，
{
	 FLAG1S_delay,
    Time_Delay

};
#define Down_Task  (Time_Delay+1)//向下减数组长度
extern unsigned int Number_Down[Down_Task];     //延时-- 数组

//位带操作 
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 


#define GPIOA_ODR_Addr    (GPIOA_BASE+12) 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12)  
#define GPIOC_ODR_Addr    (GPIOC_BASE+12)  
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12)   
#define GPIOG_ODR_Addr    (GPIOG_BASE+12)     

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8)  
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8)  
 

#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)   
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n) 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)   

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n) 

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)   
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  





void delay_us(u32 nus);
void delay_ms1(u16 nms);

void TaskDelay(void);					//任务延时，中断调用
void delay_qus(void);





#endif
