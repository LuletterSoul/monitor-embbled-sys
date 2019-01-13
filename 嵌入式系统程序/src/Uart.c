
#define TRUE 	1
#define FALSE 	0
#define rUTRSTAT0	(*(volatile unsigned *)0x50000010)
#define rUTRSTAT1	(*(volatile unsigned *)0x50004010)
#define WrUTXH0(ch)	(*(volatile unsigned char *)0x50000020)=(unsigned char)(ch)
#define WrUTXH1(ch)	(*(volatile unsigned char *)0x50004020)=(unsigned char)(ch)
#define RdURXH0()	(*(volatile unsigned char *)0x50000024)
#define RdURXH1()	(*(volatile unsigned char *)0x50004024)
#include "inc/macro.h"
#include "inc/lib.h"
void Uart_SendByten(int Uartnum, U8 data)//ok eric rong
{   //int i;
	if(Uartnum==0)
    {
		while(!(rUTRSTAT0 & 0x4)); //Wait until THR is empty.
		
		hudelay(10);
		WrUTXH0(data);
   	}
	else
    {
		while(!(rUTRSTAT1 & 0x4));  //Wait until THR is empty.
		
		hudelay(10);
		WrUTXH1(data);
    }	
}		

   char Uart_Getchn(char* Revdata, int Uartnum, int timeout)
{
	
	if(Uartnum==0){
		while(!(rUTRSTAT0 & 0x1)); //Receive data read
		*Revdata=RdURXH0();
		return TRUE;
	}
	else{
		while(!(rUTRSTAT1 & 0x1));//Receive data read
		*Revdata=RdURXH1();
		return TRUE;
	}
}	
