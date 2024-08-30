#include "stm32f4xx.h"                  // Device header

#include "esp8266.h"


void ESP8266_Init(void)   //����AT�����ʼ��ESP8266ģ�顣
{
	// ����AT�����ʼ��ESP8266
	USART2_SendString("AT\r\n");
	// ���������ʱ�ͽ�����Ӧ�Ĵ���
	delay_ms(1000);
}

void ESP8266_APCreateWiFi(const char *ssid, const char *password)  //����ESP8266ΪAPģʽ���Լ�����WIFI���硣
{
	// ����WiFiģʽΪAPģʽ���Լ�����WIFI���磩
	USART2_SendString("AT+CWMODE=2\r\n");
	delay_ms(1000);
	ESP8266_Rst();
	// ����APģʽ������WiFi������˺ź�����
	char cmd[128]; //����һ����СΪ128�ֽڵ��ַ����� cmd�����ڴ洢��ʽ�����AT�����ַ�����
	sprintf(cmd, "AT+CWSAP=\"%s\",\"%s\",5,3\r\n", ssid, password); //ʹ�� sprintf ��������ʽ�����ַ���д�� cmd �����С�����ַ�����һ��AT���%s ��ʽ˵�������� ssid �� password ��ֵ�滻��
	USART2_SendString(cmd);  //ͨ��USART2���ڷ��͸�ʽ�����AT�����ַ��� cmd ��ESP8266ģ�顣��
	// ���������ʱ�ͽ�����Ӧ�Ĵ���
	delay_ms(3000);
}

void ESP8266_StartTCPServer(int port) //����ͨ��������ESP8266ģ�鷢��AT���������һ��TCP������������ָ���Ķ˿�
{
	char cmd[64]; //����һ���ַ����� cmd����СΪ64�ֽڣ����ڴ洢��Ҫ���͵�AT�����ַ���
	USART2_SendString("AT+CIPAP=\"192.168.4.1\"\r\n");
	delay_ms(1000);		
	USART2_SendString("AT+CIPMUX=1\r\n");
	delay_ms(1000);		
	sprintf(cmd, "AT+CIPSERVER=1,%d\r\n", port); //��ʽ���ַ��� "AT+CIPSERVER=1,%d\r\n" ����һ��AT���� AT+CIPSERVER������ 1 ��ʾ������������%d ��һ��ռλ��������ʵ�ʵĶ˿ں��滻��
	USART2_SendString(cmd);                      //\r\n �ǻس����з������ڱ�ʾAT����Ľ�����
	delay_ms(2000);
}

void ESP8266_ReceiveData(void) //���ڽ������ݲ����͸�����
{
    char buffer[256];  //�洢���յ������ݡ�
    int length = 0;    //��¼���յ������ݳ��ȡ�

    // �ȴ���������
    while (1)
    {
        // ����Ƿ������ݿɶ�
        if (USART2_DataAvailable())
        {
            length = USART2_ReceiveData(buffer, sizeof(buffer) - 1); //��USART2�������ݣ��������ݴ洢��buffer�С�sizeof(buffer) - 1ȷ�����ᳬ������߽�
            buffer[length] = '\0'; // ȷ���ַ�����NULL��β

            // ����Ƿ���յ�����
            if (length > 0)
            {
                // �����յ������ݷ��͵�����
				SendDataToUSART(USART2, buffer, length);
            }
        }
    }
}

void ESP8266_SendHexData(const char *hexData) //����ͨ��ESP8266ģ�鷢��16��������,������һ��ָ���ַ�������ָ�� hexData����ʾҪ���͵�16�������ݡ�
{
    char cmd[128];
    int dataLength = strlen(hexData) / 2;  //ʹ�� strlen �������� hexData �ַ����ĳ��ȡ����� hexData ��16�����ַ�����ÿ�����ַ���ʾһ���ֽڣ���˽����ȳ���2�õ�ʵ�ʵ����ݳ���

    // �������ݳ���
    sprintf(cmd, "AT+CIPSEND=%d\r\n", dataLength); //��ʽ���ַ��� "AT+CIPSEND=%d\r\n" ����һ��AT���� AT+CIPSEND������ %d ��һ��ռλ��������ʵ�ʵ����ݳ����滻��
    USART2_SendString(cmd);   
    delay_ms(1000);

    // ����16��������
    USART2_SendString(hexData); //���ڷ��� hexData �����е�16���������ַ�����ESP8266ģ�顣
    delay_ms(1000);
}

void ESP8266_Rst(void)
{
	USART2_SendString("AT+RST\r\n");
	// ���������ʱ�ͽ�����Ӧ�Ĵ���
	delay_ms(1000);
}

