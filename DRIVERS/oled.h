#ifndef _OLED_H_
#define	_OLED_H_

#include "main.h"


#define OLED_ADDRESS	0x78 //ͨ������0R����,������0x78��0x7A������ַ -- Ĭ��0x78

void I2C_Configuration(void);
void OLED_Init(void);
void OLED_CLS(void);//����;
//void OLED_ShowCN(unsigned char x, unsigned char y, unsigned int N);//��ʾ16*16����
void OledShowASCII(unsigned char x, unsigned char y, unsigned char chr);//OLED��ʾ10*40����                                                                                                                                  
void OledShowASCIIString(u16 x, u16 y, char *addr);//��ʾASCII�ַ�������
void OledShowNum(u16 x, u16 y, s8 num);//������ʾ����
#endif
