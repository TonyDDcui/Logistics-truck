#include "oled.h"

void I2C_Configuration(void)
{
	I2C_InitTypeDef  I2C_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure2; 

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

	/*STM32F103C8T6оƬ��Ӳ��I2C: PB6 -- SCL; PB7 -- SDA */
	GPIO_InitStructure2.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_AF;//I2C���뿪©���
	GPIO_Init(GPIOB, &GPIO_InitStructure2);

	I2C_DeInit(I2C1);//ʹ��I2C1
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = 0x30;//������I2C��ַ,���д��
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 400000;//400K

	I2C_Cmd(I2C1, ENABLE);
	I2C_Init(I2C1, &I2C_InitStructure);
}

void I2C_WriteByte(uint8_t addr,uint8_t data)
{
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	
	I2C_GenerateSTART(I2C1, ENABLE);//����I2C1
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,��ģʽ*/

	I2C_Send7bitAddress(I2C1, OLED_ADDRESS, I2C_Direction_Transmitter);//������ַ -- Ĭ��0x78
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2C1, addr);//�Ĵ�����ַ
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2C1, data);//��������
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_GenerateSTOP(I2C1, ENABLE);//�ر�I2C1����
}

void WriteCmd(unsigned char I2C_Command)//д����
{
	I2C_WriteByte(0x00, I2C_Command);
}

void WriteDat(unsigned char I2C_Data)//д����
{
	I2C_WriteByte(0x40, I2C_Data);
}

void OLED_Init(void)
{
	delay_ms1(100); //�������ʱ����Ҫ
	
	WriteCmd(0xAE); //display off
	WriteCmd(0x20);	//Set Memory Addressing Mode	
	WriteCmd(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	WriteCmd(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	WriteCmd(0xc8);	//Set COM Output Scan Direction
	WriteCmd(0x00); //---set low column address
	WriteCmd(0x10); //---set high column address
	WriteCmd(0x40); //--set start line address
	WriteCmd(0x81); //--set contrast control register
	WriteCmd(0xff); //���ȵ��� 0x00~0xff
	WriteCmd(0xa1); //--set segment re-map 0 to 127
	WriteCmd(0xa6); //--set normal display
	WriteCmd(0xa8); //--set multiplex ratio(1 to 64)
	WriteCmd(0x3F); //
	WriteCmd(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	WriteCmd(0xd3); //-set display offset
	WriteCmd(0x00); //-not offset
	WriteCmd(0xd5); //--set display clock divide ratio/oscillator frequency
	WriteCmd(0xf0); //--set divide ratio
	WriteCmd(0xd9); //--set pre-charge period
	WriteCmd(0x22); //
	WriteCmd(0xda); //--set com pins hardware configuration
	WriteCmd(0x12);
	WriteCmd(0xdb); //--set vcomh
	WriteCmd(0x20); //0x20,0.77xVcc
	WriteCmd(0x8d); //--set DC-DC enable
	WriteCmd(0x14); //
	WriteCmd(0xaf); //--turn on oled panel
}

void OLED_SetPos(unsigned char x, unsigned char y) //������ʼ������
{ 
	WriteCmd(0xb0+y);
	WriteCmd(((x&0xf0)>>4)|0x10);
	WriteCmd((x&0x0f)|0x01);
}

void OLED_Fill(unsigned char fill_Data)//ȫ�����
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		WriteCmd(0xb0+m);		//page0-page1
		WriteCmd(0x00);		//low column start address
		WriteCmd(0x10);		//high column start address
		for(n=0;n<128;n++)
			{
				WriteDat(fill_Data);
			}
	}
}

void OLED_CLS(void)//����
{
	OLED_Fill(0x00);
}

//--------------------------------------------------------------
// Prototype      : void OLED_ON(void)
// Calls          : 
// Parameters     : none
// Description    : ��OLED�������л���
//--------------------------------------------------------------
void OLED_ON(void)
{
	WriteCmd(0X8D);  //���õ�ɱ�
	WriteCmd(0X14);  //������ɱ�
	WriteCmd(0XAF);  //OLED����
}

//--------------------------------------------------------------
// Prototype      : void OLED_OFF(void)
// Calls          : 
// Parameters     : none
// Description    : ��OLED���� -- ����ģʽ��,OLED���Ĳ���10uA
//--------------------------------------------------------------
void OLED_OFF(void)
{
	WriteCmd(0X8D);  //���õ�ɱ�
	WriteCmd(0X10);  //�رյ�ɱ�
	WriteCmd(0XAE);  //OLED����
}



//--------------------------------------------------------------
// Prototype      : void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
// Calls          : 
// Parameters     : x,y -- ��ʼ������(x:0~127, y:0~7); N:������codetab.h�е�����
// Description    : ��ʾcodetab.h�еĺ���,16*16����
//--------------------------------------------------------------
/*
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned int N)
{
	unsigned char wm=0;
	unsigned int  adder=N;
	OLED_SetPos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		WriteDat(F16x16[adder][wm]);
		
	}
	OLED_SetPos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		WriteDat(F16x16[adder][wm+16]);
    }
}
*/

void OledShowASCII(unsigned char x, unsigned char y, unsigned char chr)//OLED��ʾ10*40����
{
	unsigned char wm=0;

	
    if(chr<' ' || chr>'~')
    {    
        chr = 95;      
    }
    else
    {
        chr -= ' ';               //ASCII�ֿ��Ǵӿո�ʼȡģ
    }

    
	OLED_SetPos(x , y);
	for(wm = 0;wm <15;wm++)  //             
	{
		WriteDat(ASCII_6015[chr][wm]);	
	}  
    
	OLED_SetPos(x,y + 1); 
	for(wm = 0;wm < 15;wm++) //         
	{
		WriteDat(ASCII_6015[chr][wm+15]);
	}

	OLED_SetPos(x,y + 2); 
	for(wm = 0;wm < 15;wm++) //         
	{
		WriteDat(ASCII_6015[chr][wm+30]);
	}

	OLED_SetPos(x,y + 3); 
	for(wm = 0;wm < 15;wm++) //         
	{
		WriteDat(ASCII_6015[chr][wm+45]);
	}

	OLED_SetPos(x,y + 4); 
	for(wm = 0;wm < 15;wm++) //         
	{
		WriteDat(ASCII_6015[chr][wm+60]);
	}    

	OLED_SetPos(x,y + 5); 
	for(wm = 0;wm < 15;wm++) //         
	{
		WriteDat(ASCII_6015[chr][wm+75]);
	}

	OLED_SetPos(x,y + 6); 
	for(wm = 0;wm < 15;wm++) //         
	{
		WriteDat(ASCII_6015[chr][wm+90]);
	}

	OLED_SetPos(x,y + 7); 
	for(wm = 0;wm < 15;wm++) //         
	{
		WriteDat(ASCII_6015[chr][wm+105]);
	}    
}



/*��ʾASCII�ַ�������; x,y-��ʾλ������;*addr-�ַ�����ʼ��ַ;
                  */
void OledShowASCIIString(u16 x, u16 y, char *addr)//��ʾASCII�ַ�������
{
    while (*addr != '\0')//�жϵ�ַ�ǿ�
    {
        OledShowASCII(x, y, *addr);
        x += 15;
        addr++;
    }
}

/* ������ʾ������x,y-��ʾλ������; num-Ҫ��ʾ����ֵ
                        */
void OledShowNum(u16 x, u16 y, s8 num)//������ʾ����
{
    u8 i = 0;
    u8 sta = 0;
    u8 buf[5];
       
    if (num < 0)  //���Ϊ����������ȡ����ֵ������ָ������Ӹ���
    {
        num = -num;
        sta = 1;               
    }
    
    do {          //��ת��Ϊ��λ��ǰ��ʮ��������
        buf[i++] = num % 10 + '0';
        num /= 10;
    } while (num > 0);
    
    if(sta == 1)
    {
        buf[i++] = '-';
    }

    while (i--) //������ʾbuf�е�ÿ��Ԫ��
    {
        OledShowASCII(x, y, buf[i]);
        x += 15;
    }   
}

