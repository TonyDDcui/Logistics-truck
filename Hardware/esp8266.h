#ifndef __ESP8266_H
#define __ESP8266_H

#include <stdio.h>
#include <string.h>
#include "usart.h"
#include "delay.h"


///////////////////////////////////////////////////////////////////////////
//ʹ��AT�������ESP8266���ӵ�WiFi���� ����ΪTCP������  ����ͨ��ESP8266ģ�鷢��16��������
void ESP8266_Init(void);
void ESP8266_Rst(void);
void ESP8266_APCreateWiFi(const char *ssid, const char *password);  //����ESP8266ΪStationģʽ�������ӵ�ָ����WiFi���硣
void ESP8266_StartTCPServer(int port); //����ͨ��������ESP8266ģ�鷢��AT���������һ��TCP������������ָ���Ķ˿�
void ESP8266_ReceiveData(void);
void ESP8266_SendHexData(const char *hexData); 
///////////////////////////////////////////////////////////////////////////

#endif
