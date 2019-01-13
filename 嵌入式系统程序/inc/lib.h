
#ifndef __LIB_H__
#define __LIB_H__

//#include	"io.h"
//#include	"sysdrv.h"		//驱动抽象层头文件
//#include	"../inc/macro.h"

//for debug
#define TRACE		printf
//for kernel information output
#define printk		printf




/***********************System define***************************************/
extern unsigned int PCLK, HCLK, FCLK;



/***********************macro define***************************************/
#define mdelay(n)	hudelay(n*10)

/***********************function define***************************************/
typedef void (*serial_loop_func_t)(void);

/***********************arm define***************************************/
//#define FlushCache()		__asm{mcr p15, 0, r0, c7, c7, 0}

/*lib.c*/
void hudelay(int time); //Watchdog Timer is used.


int Uart_Init(int whichUart,int baud);

int Uart_SendByte(int whichUart, int data);

void Uart_Printf(int whichUart, char *fmt,...);
void Uart_SendString(int whichUart, char *pt);
typedef int (*serial_init_func_t)(int);
typedef int (*serial_read_func_t)(void);
typedef int (*serial_write_func_t)(int);
typedef int (*serial_poll_func_t)(void);	//串口接收数据查询，有数据的时候返回1
typedef int (*serial_flush_input_func_t)(void);
typedef int (*serial_flush_output_func_t)(void);


typedef struct {
	serial_init_func_t init;

	serial_read_func_t read;
	serial_write_func_t write;

	serial_poll_func_t poll;

	serial_flush_input_func_t flush_input;
	serial_flush_output_func_t flush_output;

	int nIsr;		//中断号
} serial_driver_t;




#endif
