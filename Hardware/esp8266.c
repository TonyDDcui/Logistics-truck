#include "stm32f4xx.h"                  // Device header

#include "esp8266.h"


void ESP8266_Init(void)   //发送AT命令初始化ESP8266模块。
{
	// 发送AT命令初始化ESP8266
	USART2_SendString("AT\r\n");
	// 可以添加延时和接收响应的代码
	delay_ms(1000);
}

void ESP8266_APCreateWiFi(const char *ssid, const char *password)  //设置ESP8266为AP模式，自己创建WIFI网络。
{
	// 设置WiFi模式为AP模式（自己创建WIFI网络）
	USART2_SendString("AT+CWMODE=2\r\n");
	delay_ms(1000);
	ESP8266_Rst();
	// 设置AP模式创建的WiFi网络的账号和密码
	char cmd[128]; //声明一个大小为128字节的字符数组 cmd，用于存储格式化后的AT命令字符串。
	sprintf(cmd, "AT+CWSAP=\"%s\",\"%s\",5,3\r\n", ssid, password); //使用 sprintf 函数将格式化的字符串写入 cmd 数组中。这个字符串是一个AT命令，%s 格式说明符将被 ssid 和 password 的值替换。
	USART2_SendString(cmd);  //通过USART2串口发送格式化后的AT命令字符串 cmd 到ESP8266模块。。
	// 可以添加延时和接收响应的代码
	delay_ms(3000);
}

void ESP8266_StartTCPServer(int port) //用于通过串口向ESP8266模块发送AT命令，以启动一个TCP服务器并监听指定的端口
{
	char cmd[64]; //定义一个字符数组 cmd，大小为64字节，用于存储将要发送的AT命令字符串
	USART2_SendString("AT+CIPAP=\"192.168.4.1\"\r\n");
	delay_ms(1000);		
	USART2_SendString("AT+CIPMUX=1\r\n");
	delay_ms(1000);		
	sprintf(cmd, "AT+CIPSERVER=1,%d\r\n", port); //格式化字符串 "AT+CIPSERVER=1,%d\r\n" 包含一个AT命令 AT+CIPSERVER，参数 1 表示启动服务器，%d 是一个占位符，将被实际的端口号替换。
	USART2_SendString(cmd);                      //\r\n 是回车换行符，用于表示AT命令的结束。
	delay_ms(2000);
}

void ESP8266_ReceiveData(void) //用于接收数据并发送给串口
{
    char buffer[256];  //存储接收到的数据。
    int length = 0;    //记录接收到的数据长度。

    // 等待接收数据
    while (1)
    {
        // 检查是否有数据可读
        if (USART2_DataAvailable())
        {
            length = USART2_ReceiveData(buffer, sizeof(buffer) - 1); //从USART2接收数据，并将数据存储到buffer中。sizeof(buffer) - 1确保不会超出数组边界
            buffer[length] = '\0'; // 确保字符串以NULL结尾

            // 检查是否接收到数据
            if (length > 0)
            {
                // 将接收到的数据发送到串口
				SendDataToUSART(USART2, buffer, length);
            }
        }
    }
}

void ESP8266_SendHexData(const char *hexData) //用于通过ESP8266模块发送16进制数据,它接受一个指向字符常量的指针 hexData，表示要发送的16进制数据。
{
    char cmd[128];
    int dataLength = strlen(hexData) / 2;  //使用 strlen 函数计算 hexData 字符串的长度。由于 hexData 是16进制字符串，每两个字符表示一个字节，因此将长度除以2得到实际的数据长度

    // 发送数据长度
    sprintf(cmd, "AT+CIPSEND=%d\r\n", dataLength); //格式化字符串 "AT+CIPSEND=%d\r\n" 包含一个AT命令 AT+CIPSEND，参数 %d 是一个占位符，将被实际的数据长度替换。
    USART2_SendString(cmd);   
    delay_ms(1000);

    // 发送16进制数据
    USART2_SendString(hexData); //串口发送 hexData 数组中的16进制数据字符串到ESP8266模块。
    delay_ms(1000);
}

void ESP8266_Rst(void)
{
	USART2_SendString("AT+RST\r\n");
	// 可以添加延时和接收响应的代码
	delay_ms(1000);
}

