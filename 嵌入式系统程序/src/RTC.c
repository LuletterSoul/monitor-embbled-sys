#include "../inc/reg2410.h"
#include "../inc/macro.h"

//#include "../inc/lib.h"

#include "../inc/isr.h"
#include "../inc/rtc.h"

#include <stdio.h>
#include <string.h>

#include "led.h"

#define rUTRSTAT0	(*(volatile unsigned *)0x50000010)		//定义串口0的状态寄存器变量
#define rUTRSTAT1	(*(volatile unsigned *)0x50004010)
#define WrUTXH0(ch)	(*(volatile unsigned char *)0x50000020)=(unsigned char)(ch)		//定义串口0的发送
#define WrUTXH1(ch)	(*(volatile unsigned char *)0x50004020)=(unsigned char)(ch)
#define RdURXH0()	(*(volatile unsigned char *)0x50000024)							//定义串口0的接收
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
     //读取年月日，时分秒的数据
     Y = rBCDYEAR;
     MO = rBCDMON;
     D = rBCDDATE;
     W = rBCDDAY;
     H = rBCDHOUR;
     MI = rBCDMIN;
     S = rBCDSEC;
     
     rRTCCON = (U8)(rRTCCON &0xfe);
     //读到的秒信息显示在2位LED显示器上
     i=(S & 0xf0)/16;
     lednum1con=num[i];			//显示秒的高位数	
     i=(S & 0x0f);
     lednum2con=num[i];			//显示秒的低位数
     //读到的时间信息通过串口发送
     data1 = H;
     Uart_SendByten(0,data1);
     data1 = MI;
     Uart_SendByten(0,data1);
     data1 = S;
     Uart_SendByten(0,data1);
     //data1=0xa;    				//换行
     //Uart_SendByten(0,data1);
     //data1=0xd;    				//回车
     //Uart_SendByten(0,data1);    

}

void RTC_init(void)
{
	
	//初始设置日期时间相关寄存器
	rRTCCON = (rRTCCON|0x01);
	rRTCALM = 0x00;
	rRTCRST = 0x00;
	rTICINT = 0x00;
	rRTCCON = (rRTCCON&0xfe);
	
}

void RTC_start(void)
{
	
	//启动RTC相关寄存器，并启动中断
	rRTCCON = (rRTCCON|0x01);
	rRTCALM = 0x00;
	rRTCRST = 0x00;
	rTICINT = 0xff;
	rRTCCON = (rRTCCON&0xfe);
	
    INTS_OFF();
	SetISR_Interrupt(IRQ_NUM, RTC_TICK_ISR, NULL);  //设置中断服务程序入口
    INTS_ON();   //初始化CPSR寄存器的中断开放位

}

void RTC_stop(void)
{
	
	//关闭RTC中断
	rRTCCON = (rRTCCON|0x01);
	rRTCALM = 0x00;
	rRTCRST = 0x00;
	rTICINT = 0x00;
	rRTCCON = (rRTCCON&0xfe);
	
}

