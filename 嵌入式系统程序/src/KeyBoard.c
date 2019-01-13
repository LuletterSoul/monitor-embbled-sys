#include "../inc/reg2410.h"
//#include "../inc/zlg7290.h"
#include "../inc/lib.h"
#include "../inc/macro.h"
#include "../inc/isr.h"
#include "../inc/KeyBoard.h"
#include "../inc/iic.h"
#include "../inc/Uart.h"
#include "inc/lcd.h"
#include <stdio.h>
#include <string.h>


#define KBDTYPE_ZLG7290	1
#define KBDTYPE_MCUIIC		2
#define KEYBOARD_TYPE		KBDTYPE_MCUIIC
#define KEY_DOWN			(1ul<<31)

#include "../inc/i2c-tomega8.h"

#define IRQ_KBD		IRQ_IIC
//#define MCU_IICCON		(IICCON_ACKEN |IICCON_CLK512 | IICCON_INTR | IICCON_CLKPRE(0x3))
#define MCU_IICCON		(IICCON_ACKEN  | IICCON_INTR | IICCON_CLKPRE(7))

//static unsigned short KeyBoard_Map[256];
unsigned short mcukey,tempmcukey,up,count;

static void Key_ISR(int vector, void* data)
{  
   
	static int framecnt=0;

	U8 status ,kdata;
	status = rIICSTAT ;
 //printk("enter key_ISR");
	if( (status & IICSTAT_MODE_MSK) != IICSTAT_MODE_SR)
		return;
	//must slave receive mode

	kdata = rIICDS;

	switch(framecnt){
	case 0:
		if(status & IICSTAT_SLAVEADDR){
			//match the own slave address. begin to slave receive data.
			//DPRINTK("key irq: 111\n");
			framecnt++;
		}
		break;
	case 1:
		if(GetI2C_Devtype(kdata) != DTYPE_MKEYB){
			//DPRINTK("key irq: not key farme\n");
			framecnt=0;
		}
		framecnt++;
		break;
	case 2:
		mcukey = kdata;
		if(mcukey&0x80)
		
		{framecnt=0;
		break;}
		else if(!(mcukey&0x80)){
		up=1;
		count=1;
		tempmcukey=mcukey;
		//Uart_Printf(0,"\nmcukey is %x",mcukey);
		//LCD_printf("the key is %x ",mcukey);
		}
		framecnt=0;
		break;
		
		
	}

	rIICCON &= ~IICCON_INTPEND;
	
}

void Key_init(void)
{
	I2C_control i2c_ctrl;

	IIC_init();
	Set_IIC_mode(MCU_IICCON, NULL);

	//set owner i2c address to mega8
	i2c_ctrl.cmd=CMD_MST_ADDR;
	i2c_ctrl.ctrl=I2COWNER_ADDRESS;
	IIC_Send(MEGA8_I2CADDRESS, (const char*)&i2c_ctrl, sizeof(i2c_ctrl));

	//enable keyboard
	i2c_ctrl.cmd=CMD_CTRL;
	i2c_ctrl.ctrl = CTRL_MKEn;
	IIC_Send(MEGA8_I2CADDRESS, (const char*)&i2c_ctrl, sizeof(i2c_ctrl));

    INTS_OFF();
	SetISR_Interrupt(IRQ_KBD, Key_ISR, NULL);
    INTS_ON();

}

void Key_init_restor(void)
{
	IIC_init();
	Set_IIC_mode(MCU_IICCON, NULL);

}

unsigned char GetKey()
{
 unsigned char scankey;
 //段码对应关系：0，  1，  2，  3，  4，  5，  6，  7，  8，  9，  b，  E，  F，  H，  L，  P，  U
 //              0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6,0x3e,0x9e,0x8e,0x6e,0x1c,0xce,0x7c 
	unsigned char KeyBoard_Map[]={0,0,0x9e,0,0,0xe0,0x66,0x60,0,0,0x8e
								,14,0,0xfe,0xb6,0xda,0xfc,0x1c,0x6e,0,0
								,0xf6,0xbe,0xf2,0x3e,0,0,0,0,0xce,0
								,0x7c,0,1,0,0,17,2,0,0,0
								,4,0,6,0,5,0,0,0,7,0
								,9,15,8,0,0,0,0,0,0,0
								,0,0,0
								}; //64,键值映射表							
  while(1){								
     if((up==1)&&(count==1)){
       up=0;
       count=0;
       scankey=KeyBoard_Map[tempmcukey];
       break;
     }
     else continue;
     }
  return scankey;
} 