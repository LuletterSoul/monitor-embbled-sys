/***************************************************************************\
	ʵ��8��Ŀ�ģ�ʹѧ���˽��ж�ϵͳ�Ĵ������̣��˽�RTC��ʱ���Ĺ���ԭ���ͳ�ʼ
	             ����̣�ѧϰ�жϿ���ģʽ�µ�RTC��ʱ����̷�����	              
	ʵ��8��Ҫ��ѧϰ������ʵ��ʵ���е��жϿ��Ƴ������̣����RTC��ʱ�����ж�
	             ��ʼ����̣����RTC���жϷ�������̡�
\***************************************************************************/
	
#include <string.h>
#include <stdio.h>
#include "inc/macro.h"
#include "inc/reg2410.h"
#include "inc/uhal.h"
#include "../inc/rtc.h"
#include "../inc/isr.h"


#include "led.h"

#pragma import(__use_no_semihosting_swi)  // ensure no functions that use semihosting 

extern U32 LCDBufferII2[480][640];

#define PCLK	50.7*1000000

#define rULCON0		(*(volatile unsigned *)0x50000000)		//���崮��0����·���ƼĴ�������
#define rUBRDIV0	(*(volatile unsigned *)0x50000028)		//���崮��0�ĳ����Ĵ�������
#define rUCON0		(*(volatile unsigned *)0x50000004)		//���崮��0�Ŀ��ƼĴ�������
#define rUFCON0		(*(volatile unsigned *)0x50000008)		//���崮��0��FIFO���ƼĴ�������

#define rULCON1		(*(volatile unsigned *)0x50004000)		//���崮��1����·���ƼĴ�������
#define rUBRDIV1	(*(volatile unsigned *)0x50004028)		//���崮��1�ĳ����Ĵ�������
#define rUCON1		(*(volatile unsigned *)0x50004004)		//���崮��1�Ŀ��ƼĴ�������
#define rUFCON1		(*(volatile unsigned *)0x50004008)		//���崮��1��FIFO���ƼĴ�������

#define rUTRSTAT0	(*(volatile unsigned *)0x50000010)		//���崮��0��״̬�Ĵ�������
#define rUTRSTAT1	(*(volatile unsigned *)0x50004010)
#define WrUTXH0(ch)	(*(volatile unsigned char *)0x50000020)=(unsigned char)(ch)		//���崮��0�ķ���
#define WrUTXH1(ch)	(*(volatile unsigned char *)0x50004020)=(unsigned char)(ch)
#define RdURXH0()	(*(volatile unsigned char *)0x50000024)							//���崮��0�Ľ���
#define RdURXH1()	(*(volatile unsigned char *)0x50004024)

#define MOTOR_SEVER_FRE			1000		//20kHz                 

#define MOTOR_CONT				(PCLK/2/2/MOTOR_SEVER_FRE)
#define MOTOR_MID				(MOTOR_CONT/2)


#define START_FLAG 0x30
#define END_FLAG 0x60
#define ZERO_FLAG 0x00
#define PKT_LEN 7 
#define Asc(x) x + '0'
#define MOD8(x) x %256

/////////////*********************  ������  *************** //////////////
#define INIT_CMD 0x31
#define STOP_CMD 0x32
#define SPEED_CMD 0x33
#define ADD_CMD 0x34
#define DOWN_CMD 0x35
#define TIMER_CMD 0x36
/////////////*********************  ������  *************** //////////////


 
/////////////*********************  ״̬��  *************** //////////////
#define SUCCESS_CODE 0x01 //У��ɹ�
#define FAILED_CODE 0x02
#define UNKNOW_CODE 0X03
#define TIMER_CODE 0x04


#define INIT_SUCCESS 0x11
#define STOP_SUCCESS 0x21
#define ADD_SUCCESS 0x31
#define DOWN_SUCCESS 0x41 
#define SPEED_SECCESS 0x51
#define TIMER_SUCCESS 0x61


#define INIT_FAILED 0x12
#define STOP_FAILED 0x22
#define ADD_FAILED  0x32
#define DOWN_FAILED 0x42
#define SPEED_FAILED 0x52
#define TIMER_FAILED 0x62
/////////////*********************  ״̬��  *************** //////////////


#define BUFFER_SIZE 1024
#define IRQ_NUM		IRQ_TICK


U8 data1;
U8 key_flag=0x00;			//������һ����������Ϊ�����־




int flag10=0;
int data2=30;
int i;
int j;
int h;
int k;
	     //   0    1   2    3    4    5    6    7    8    9    a    b    c    d    e    f    -    .    0ff
int num[19]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xbf,0x7f,0xff};

void TimerInit(int dTCMPB);
void Uart_SendByten(int,U8);
char Uart_Getchn(char* Revdata, int Uartnum);
void delay(int time1,int time2);


void sendMsg(int code);
//void sendRation(U8 ration);
void sendRation(U8 ration,U8 a);
void sendAck(U8 cmd,U8 param1);
int makePacket(U8 pkt[],U8 cmd, U8 param1, U8 param2);
int checkSum(U8 pkt[],U8 cmd ,U8 param1,U8 param2);
int sendPkt(U8 pkt[]);
void RTC_init(void);


int minu,sec,times=0;

char c1[1];
char err;
U8 recarr[6];

U16 checksum=0x0000;
U16 aa=0x0000;

int main(void)
{   
            	
	ARMTargetInit();        //do target (uHAL based ARM system) initialisation 
	 
    //��ʼ���˿�H�����Ź���Ϊ���ڹ��ܣ�UART0�Ĺ������ţ�
    rGPHCON = (rGPHCON | 0x0000faaa) & 0xfffffaaa;
    //��ʼ��UART0�����ļĴ���
    rUFCON0=0;
    rULCON0 = 0x03;
    rUBRDIV0 = ((int)(PCLK/(115200*16)+0.5)-1);
    rUCON0=0x345;
    //��ʼ��UART1�����ļĴ���
    rUFCON1=0;
    rULCON1 = 0x03;
    rUBRDIV1 = ((int)(PCLK/(115200*16)+0.5)-1);
    rUCON1=0x345;
    //���淢����ʾ��Ϣ��Timer  
    data1=0x54;
    Uart_SendByten(0,data1);
    data1=0x69;
    Uart_SendByten(0,data1);
    data1=0x6d;    
    Uart_SendByten(0,data1);
    data1=0x65;
    Uart_SendByten(0,data1);
    data1=0x72;    
    Uart_SendByten(0,data1);
    data1=0xa;    				//����
    Uart_SendByten(0,data1);
    data1=0xd;    				//�س�
    Uart_SendByten(0,data1);
    
    //��ʼ���˿�B�����Ź���ΪTout1��Tout0�Ĺ���
     rGPBCON = (rGPBCON & 0x3ffff0) | 0xa;
    
	while(1)
	{
		int flag=check();
		if(flag==1){
		key_flag=recarr[1];
		//key_flag=0x01;
	 	switch (key_flag)
       {   case INIT_CMD:   //�������
       			// lednum1con=num[5];
           		//  lednum2con=num[5];
                TimerInit(MOTOR_MID - MOTOR_CONT/10); 					//ִ����������,˳ʱ��ת
               lednum1con=num[1];			//��ʾ��λ��	
               lednum2con=num[0];			//��ʾ��λ��
                key_flag=0x00;
                sendAck(SUCCESS_CODE,0);
                break;      
           case STOP_CMD:   //ֹͣ���
            	//lednum1con=num[4];
           		  //lednum2con=num[4];
                TimerInit(MOTOR_MID);		//ִ��ֹͣ����
                lednum1con=num[18];			//��ʾ��λ��	
                lednum2con=num[18];			//��ʾ��λ��
                key_flag=0x00;
                sendAck(SUCCESS_CODE,0);
                break;
           case SPEED_CMD: // ����ģʽ
           		  lednum1con=num[2];
           		  lednum2con=num[2];
           		  delay(10,10);
           		  sendAck(SUCCESS_CODE,0);
                while(1)
                {
                   	flag=check();//�Ӵ��ڽ��յ���ռ�ձȵĲ���
                   	if(flag==1){
	                   	 if (recarr[1]==STOP_CMD)
	                     { 
	                       TimerInit(MOTOR_MID);
	                       lednum1con=num[18];			//��ʾ��λ��	
	                       lednum2con=num[18];			//��ʾ��λ��
	                       sendAck(SUCCESS_CODE,0);
	                       break;
	                     }
	                   // �������ת��
	                   if(recarr[1]==ADD_CMD){
	                   		if(data2>4){ //Data2��¼�ŵ����ǰ��ռ�ձȲ���
		           				data2=data2-2;
		           				//��ʾռ�ձ�
		           				k=data2/10;
		           				lednum1con=num[k];
		           				k=data2%10;
		           				lednum2con=num[k];
		           				TimerInit(MOTOR_MID - MOTOR_CONT/data2);
		           				sendAck(SUCCESS_CODE,data2);
		           			}
		           			else{
		           				k=data2/10;
		           				lednum1con=num[k];
		           				k=data2%10;
		           				lednum2con=num[k];
		           				TimerInit(MOTOR_MID - MOTOR_CONT/data2);//���ͼ���ʧ�ܵ���Ӧ
		           				sendAck(FAILED_CODE,data2);//���ͼ���ʧ�ܵ���Ӧ
		           			}
		           			
	                   }
	                   // �������ת��
	                   else if(recarr[1]==DOWN_CMD){
		                   	if(data2<30){
			           				data2=data2+2;
			           				//��ʾռ�ձ�
			           				k=data2/10;
			           				lednum1con=num[k];
			           				k=data2%10;
			           				lednum2con=num[k];
			           				TimerInit(MOTOR_MID - MOTOR_CONT/data2);
			           				sendAck(SUCCESS_CODE,data2);
			           		}
			           		else{//����30���ټ���
			           				k=data2/10;
			           				lednum1con=num[k];
			           				k=data2%10;
			           				lednum2con=num[k];
			           				TimerInit(MOTOR_MID - MOTOR_CONT/data2);
			           				sendAck(FAILED_CODE,data2);//���ͼ���ʧ�ܵ���Ӧ
			           		}
			           		
	                   }
	                   else if(recarr[1]==SPEED_CMD){//�Զ����ٶ�
		                   data1=recarr[2];
		                   //������ʾ��2λLED��ʾ����
		                   i=(data1 & 0xf0)/16;
		                   lednum1con=num[i];			//��ʾ��λ��	
		                   i=(data1 & 0x0f);
		                   lednum2con=num[i];			//��ʾ��λ��
		                   data1=((data1 & 0xf0)/16)*10 + (data1 & 0x0f);
		                   data2=data1;
		                   TimerInit(MOTOR_MID - MOTOR_CONT/data1);
		                   sendAck(SUCCESS_CODE,data2);
	                   }
	                }
	              else{
		               lednum1con=num[3];	
	    			   lednum2con=num[3];
	              } 
                }
                key_flag=0x00;
                break;
          case TIMER_CMD:
           		lednum1con=num[3];	
	    		lednum2con=num[6];
	    		flag10=1;
                RTC_init();
          		key_flag=0x00;
          		sendAck(SUCCESS_CODE,0);
                break;                       
           break;   
       }
	 }
	 else{ 
	 //h=(checksum&0xff00)/256;
	  lednum1con=num[1];
		// h=(checksum&0x00ff);		
      lednum2con=num[1];
      sendAck(FAILED_CODE,0);
	}	  
	}
	
	return 0;			
}

void TimerInit(int dTCMPB)
{
     
     //Dead Zone=24, PreScalero1=2;
	 rTCFG0=(0<<16)|2;

	 //divider timer0=1/2;
	 rTCFG1=0;

	 rTCNTB0= MOTOR_CONT;
	 rTCMPB0= dTCMPB;  
	 	
	 rTCON=0x2;			//update mode for TCNTB0 and TCMPB0.
	 rTCON=0x19;		//timer0 = auto reload, start. Dead Zone  
}
	
void Uart_SendByten(int com ,U8 data)
{
     if (com==0)			//com==0��ʾUART0
     {
         while((rUTRSTAT0&0x4)!=0x4);
         WrUTXH0(data);
     }
     else
     {
         while((rUTRSTAT1&0x4)!=0x4);
         WrUTXH1(data);
     }
}

char Uart_Getchn(char* Revdata, int Uartnum)
{
	
	if(Uartnum==0){
		while(!(rUTRSTAT0 & 0x1)); //Receive data read
		*Revdata=RdURXH0();
		return TRUE;
	}
	else
	{
		while(!(rUTRSTAT1 & 0x1));//Receive data read
		*Revdata=RdURXH1();
		return TRUE;
	}
}

int check(){
	checksum=0x0000;
	 for(j=0;j<6;j++){
		recarr[j]=0x00;
	}
   for(j=0;j<6;j++){
    	err=Uart_Getchn(c1,0);	//�Ӵ��ڽ�������
 		delay(10,10);
		recarr[j]=c1[0];
		if(j<=3){
		   checksum+=recarr[j];
		}
	}
	//aa=(recarr[4]<<8)|recarr[5];
	// h=(checksum&0xff00)/256;
	//lednum1con=num[h];
	//h=(checksum&0x00ff);		
    //lednum2con=num[h];
	
	if(checksum==((recarr[4]<<8)|recarr[5])){
	  // sendAck(SUCCESS_CODE,0);
	   return 1;
	}
	else {
	  // sendAck(FAILED_CODE,0);
       return 0;
	};
}

void delay(int time1,int time2)
{
   int i,j;
   for(i=0;i<time1;i++)
   {
       for(j=0;j<time2;j++);
   } 
}

//void sendRation(U8 ratio){
//	U8 pkt[PKT_LEN];
//	int i = 0;
//	for(;i<PKT_LEN;i++){
//		pkt[i] = 0x00;
//	}
//	makePacket(pkt,0x01,0x01,ratio);
//	sendPkt(pkt);
//}


//ά��״̬�����ķ����߼�,���Ա��������յ�����ָ��֮���ִ��״̬
void sendAck(U8 cmd,U8 param1){
    U8 pkt[PKT_LEN];
    int i = 0;
    for(;i<PKT_LEN;i++){
		pkt[i] = 0x00;
    }
    if(cmd == SUCCESS_CODE){
 		switch(recarr[1]){
 			case INIT_CMD:
			//��������ɹ���ACK
 			makePacket(pkt,SUCCESS_CODE,INIT_SUCCESS,ZERO_FLAG);
 			break;
			//���ֹͣ�ɹ���ACK
 			case STOP_CMD:
 			makePacket(pkt,SUCCESS_CODE,STOP_SUCCESS,ZERO_FLAG);
 			break;
			//������ٳɹ���ACK
 			case SPEED_CMD:
 			makePacket(pkt,SUCCESS_CODE,SPEED_SECCESS,param1);
 			break;
			//������ٳɹ���ACK, �ش�ռ�ձ�,0����δ֪
 			case ADD_CMD:
 			makePacket(pkt,SUCCESS_CODE,ADD_SUCCESS,param1);
 			break;
			//������ٳɹ���ACK
 			case DOWN_CMD:
 			makePacket(pkt,SUCCESS_CODE,DOWN_SUCCESS,param1);
 			break;
			//�����ʱ�����ɹ���ACK
 			case TIMER_CMD:
 			makePacket(pkt,SUCCESS_CODE,TIMER_SUCCESS,param1);
 			break;
 			default:
			//������δ֪��������
 			makePacket(pkt,UNKNOW_CODE,ZERO_FLAG,ZERO_FLAG);
 			break;
 		}	
    }
    else if (cmd == FAILED_CODE){
        //ʧ�ܵ�ACK
        switch(recarr[1]){
    		case INIT_CMD:
    			makePacket(pkt,FAILED_CODE,INIT_FAILED,ZERO_FLAG);
    		break;
    		case STOP_CMD:
    			makePacket(pkt,FAILED_CODE,STOP_FAILED,ZERO_FLAG);
    		break;
 			case SPEED_CMD:
 				makePacket(pkt,FAILED_CODE,SPEED_FAILED,ZERO_FLAG);
 			break;	
 			case ADD_CMD:
 			    makePacket(pkt,FAILED_CODE,ADD_FAILED,ZERO_FLAG);
 			break;
 			case DOWN_CMD:
 				makePacket(pkt,FAILED_CODE,DOWN_FAILED,ZERO_FLAG);
 			break;
 			case TIMER_CMD:
 			makePacket(pkt,FAILED_CODE,TIMER_FAILED,ZERO_FLAG);
 			break;
 			default:
 			makePacket(pkt,UNKNOW_CODE,ZERO_FLAG,ZERO_FLAG);
 			break;
        }
    }
    	sendPkt(pkt);
}


//Packet���캯��,Packet�ĸ�ʽ�������ҷֱ�����ʼ���������롢����1������2��У�����λ���������λ����ֹ��
int makePacket(U8 pkt[],U8 cmd, U8 param1, U8 param2){
	pkt[0] = START_FLAG; //д����ʼ����
	pkt[1] = cmd;        //д��������
	pkt[2] = param1;     //д�����1
	pkt[3] = param2;     //
	return checkSum(pkt,cmd,param1,param2);
}

//У���д�뺯��,�ͼ�����д�뵽Packet����
int checkSum(U8 pkt[],U8 cmd ,U8 param1,U8 param2){
	//����ӷ�������ȶ�U8�ֱ�ȡģ
	U8 sum = MOD8(START_FLAG) + MOD8(cmd) + MOD8(param1) + MOD8(param2);
	//ʮ����У��͵ĸ�λASCII��
	U8 highCheckSum = Asc(sum / 10);
    //ʮ���Ƽ���͵ĵ�λASCII��
	U8 lowCheckSum = Asc(sum % 10);
	pkt[4] = highCheckSum; //д��У�����λ
	pkt[5] = lowCheckSum;  //д��У�����λ
	pkt[6] = END_FLAG;     //д����ֹ��
	return sum;
}


//ͨ������0��PC������
int sendPkt(U8 pkt[]){
	int i;
	for(i=0;i<PKT_LEN;i++){
		Uart_SendByten(0,pkt[i]); //ÿ�η���һ��U8�ַ�(��һ���ֽڵĸ�ʽ)
		//delay(10,10);
	}
	return 1;
}


void sendRation(U8 ratio,U8 a){
	U8 pkt[PKT_LEN];
	int i = 0;
	for(;i<PKT_LEN;i++){
		pkt[i] = 0x00;
	}
	makePacket(pkt,0x01,a,ratio);
	sendPkt(pkt);
}

void sendTimer(U8 sen,U8 mm){
	U8 pkt[PKT_LEN];
	int i = 0;
	for(;i<PKT_LEN;i++){
		pkt[i] = 0x00;
	}
	makePacket(pkt,TIMER_CODE,sen,mm);
	sendPkt(pkt);
}


void sendMsg(int code){
	Uart_SendByten(0,code);
}


//RTC part
static void RTC_TICK_ISR(int vector, void* data)
{  
     
     U8 Y,S,MO,D,W,H,MI,sen,mm;
     int fen,miao,kk;
     	   
     rRTCCON = (U8)(rRTCCON |0x01);
     S = rBCDSEC;
     MI=rBCDMIN;
     rRTCCON = (U8)(rRTCCON &0xfe);
         
    sen=((S & 0xf0)/16)*10 + (S & 0x0f);
   	mm=((MI & 0xf0)/16)*10 + (MI & 0x0f);  
   
     //sendRation(mm,0x03);  
     //sendRation(sen,0x02);  
     sendTimer(mm,sen);
     
     //judge part
     fen=(MI&0x70)/16*10+(MI&0x0f);
     miao=(S&0x70)/16*10+(S&0x0f);		
     
    if(flag10==1){
	  if(sec<50){
	     	if(miao==sec+10){
	     		 TimerInit(MOTOR_MID - MOTOR_CONT/10);
	     		 lednum1con=num[1];			
        		 lednum2con=num[0];	 
        		 flag10=0;	 
	     		 return;
	     	}	     	
	     }
	     else{
	     	if((fen==minu+1)&&(miao==sec+10-60)){
	     		TimerInit(MOTOR_MID - MOTOR_CONT/10);
	     		lednum1con=num[1];			
     		    lednum2con=num[0];	
     		    flag10=0;
	     		return;
	     	}	     	 
	     }	    
	  }
	  
	/* if(fen==4&&miao==30){
	 	TimerInit(MOTOR_MID - MOTOR_CONT/10);
	 	//��ʾռ�ձ�
	 	 lednum1con=num[1];			
         lednum2con=num[0];	
	 	return;
	 }  */
     
}
volatile char year,month,day,wkd,hour,minute,second,flag;

void RTC_init(void)
{
	U8 Y,MO,D,W,H,MI,S;
	year=19;
	month=1;
	day=10;
	wkd=4;
	hour=15;
	//minute=4;
	//second=50;
	//��ʼ��RTC��ؼĴ���
	rRTCCON = (rRTCCON|0x01);
	rRTCALM = 0x00;
	rRTCRST = 0x00;
	rTICINT = 0xff;
	rRTCCON = (rRTCCON&0xfe);
	
	
	Y=(U8)(year/10*16+year%10);
	MO=(U8)(month/10*16+month%10);
	D=(U8)(day/10*16+day%10);
	W=(U8)(wkd);
	H=(U8)(hour/10*16+hour%10);
	//MI=(U8)(minute/10*16+minute%10);
	//S=(U8)(second/10*16+second%10);
	
	rRTCCON = (rRTCCON|0x01);
	
	rBCDYEAR=Y;
	rBCDMON=MO;
	rBCDDAY=W;
	rBCDDATE=D;
	rBCDHOUR=H;
	rBCDMIN=recarr[2];
	rBCDSEC=recarr[3];
	rRTCCON = (rRTCCON&0xfe);
	
	 minu=(recarr[2]&0x70)/16*10+(recarr[2]&0x0f);
     sec=(recarr[3]&0x70)/16*10+(recarr[3]&0x0f);
	
    INTS_OFF();
	SetISR_Interrupt(IRQ_NUM, RTC_TICK_ISR, NULL);  //�����жϷ���������
    INTS_ON();   //��ʼ��CPSR�Ĵ������жϿ���λ
}
	

