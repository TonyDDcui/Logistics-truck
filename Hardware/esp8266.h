#ifndef __ESP8266_H
#define __ESP8266_H

#include <stdio.h>
#include <string.h>
#include "usart.h"
#include "delay.h"


///////////////////////////////////////////////////////////////////////////
//使用AT命令控制ESP8266连接到WiFi网络 并作为TCP服务器  用于通过ESP8266模块发送16进制数据
void ESP8266_Init(void);
void ESP8266_Rst(void);
void ESP8266_APCreateWiFi(const char *ssid, const char *password);  //设置ESP8266为Station模式，并连接到指定的WiFi网络。
void ESP8266_StartTCPServer(int port); //用于通过串口向ESP8266模块发送AT命令，以启动一个TCP服务器并监听指定的端口
void ESP8266_ReceiveData(void);
void ESP8266_SendHexData(const char *hexData); 
///////////////////////////////////////////////////////////////////////////

#endif
