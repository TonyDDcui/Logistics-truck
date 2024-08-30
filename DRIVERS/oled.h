#ifndef _OLED_H_
#define	_OLED_H_

#include "main.h"


#define OLED_ADDRESS	0x78 //通过调整0R电阻,屏可以0x78和0x7A两个地址 -- 默认0x78

void I2C_Configuration(void);
void OLED_Init(void);
void OLED_CLS(void);//清屏;
//void OLED_ShowCN(unsigned char x, unsigned char y, unsigned int N);//显示16*16汉字
void OledShowASCII(unsigned char x, unsigned char y, unsigned char chr);//OLED显示10*40数字                                                                                                                                  
void OledShowASCIIString(u16 x, u16 y, char *addr);//显示ASCII字符串函数
void OledShowNum(u16 x, u16 y, s8 num);//数字显示函数
#endif
