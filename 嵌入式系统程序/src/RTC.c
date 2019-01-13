#include "../inc/reg2410.h"
#include "../inc/macro.h"

//#include "../inc/lib.h"

#include "../inc/isr.h"
#include "../inc/rtc.h"

#include <stdio.h>
#include <string.h>

#include "led.h"

#define rUTRSTAT0	(*(volatile unsigned *)0x50000010)		//���崮��0��״̬�Ĵ�������
#define rUTRSTAT1	(*(volatile unsigned *)0x50004010)
#define WrUTXH0(ch)	(*(volatile unsigned char *)0x50000020)=(unsigned char)(ch)		//���崮��0�ķ���
#define WrUTXH1(ch)	(*(volatile unsigned char *)0x50004020)=(unsigned char)(ch)
#define RdURXH0()	(*(volatile unsigned char *)0x50000024)							//���崮��0�Ľ���
#define RdURXH1()	(*(volatile unsigned char *)0x50004024)

#define IRQ_NUM		IRQ_TICK

void Uart_SendByten(int,U8);
char Uart_Getchn(char* Revdata, int Uartnum);

static void RTC_TICK_ISR(int vector, void* data)
{  
     
     U8 data1;
     U8 Y,MO,D,W,H,MI,S;
     int i;
	          //   0    1   2    3    4    5    6    7    8    9    a    b    c    d    e    f    -    .    0ff
	 int num[19]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xbf,0x7f,0xff};
     	   
     rRTCCON = (U8)(rRTCCON |0x01);
     //��ȡ�����գ�ʱ���������
     Y = rBCDYEAR;
     MO = rBCDMON;
     D = rBCDDATE;
     W = rBCDDAY;
     H = rBCDHOUR;
     MI = rBCDMIN;
     S = rBCDSEC;
     
     rRTCCON = (U8)(rRTCCON &0xfe);
     //����������Ϣ��ʾ��2λLED��ʾ����
     i=(S & 0xf0)/16;
     lednum1con=num[i];			//��ʾ��ĸ�λ��	
     i=(S & 0x0f);
     lednum2con=num[i];			//��ʾ��ĵ�λ��
     //������ʱ����Ϣͨ�����ڷ���
     data1 = H;
     Uart_SendByten(0,data1);
     data1 = MI;
     Uart_SendByten(0,data1);
     data1 = S;
     Uart_SendByten(0,data1);
     //data1=0xa;    				//����
     //Uart_SendByten(0,data1);
     //data1=0xd;    				//�س�
     //Uart_SendByten(0,data1);    

}

void RTC_init(void)
{
	
	//��ʼ��������ʱ����ؼĴ���
	rRTCCON = (rRTCCON|0x01);
	rRTCALM = 0x00;
	rRTCRST = 0x00;
	rTICINT = 0x00;
	rRTCCON = (rRTCCON&0xfe);
	
}

void RTC_start(void)
{
	
	//����RTC��ؼĴ������������ж�
	rRTCCON = (rRTCCON|0x01);
	rRTCALM = 0x00;
	rRTCRST = 0x00;
	rTICINT = 0xff;
	rRTCCON = (rRTCCON&0xfe);
	
    INTS_OFF();
	SetISR_Interrupt(IRQ_NUM, RTC_TICK_ISR, NULL);  //�����жϷ���������
    INTS_ON();   //��ʼ��CPSR�Ĵ������жϿ���λ

}

void RTC_stop(void)
{
	
	//�ر�RTC�ж�
	rRTCCON = (rRTCCON|0x01);
	rRTCALM = 0x00;
	rRTCRST = 0x00;
	rTICINT = 0x00;
	rRTCCON = (rRTCCON&0xfe);
	
}

