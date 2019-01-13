/***************************************************************************\
	Copyright (c) 2004-2007 threewater@up-tech.com, All rights reserved.
	by threewter	2004.5.12
\***************************************************************************/
/***************************************************************************\
    #说明: C  main 函数，ucos-ii初始化等定义
	----------------------------------  Bug  --------------------------------------

	----------------------------------  TODO list  --------------------------------------

	----------------------------------修正--------------------------------------

	2004-5-12	移植

\***************************************************************************/

#include <string.h>
#include <stdio.h>

//#include "../inc/lib.h"
#include "../inc/macro.h"
#include "../inc/reg2410.h"
#include "inc/uhal.h"
#include "inc/isr.h"

static int I_COUNT=0;

void Enter_UNDEF(void)
{
	printf("!!!Enter UNDEFINED. %d\r\n", I_COUNT++);

	for(;;);
}//BreakPoint


void Enter_SWI(void)
{
	printf("!!!Enter SWI. %d\r\n", I_COUNT++);	

	for(;;);
}

void Enter_PABORT(void)
{
	printf("!!!Enter Prefetch ABORT %d\r\n", I_COUNT++);

	for(;;);
}

void Enter_DABORT(void)
{
	printf("!!!Enter Data ABORT %d\r\n", I_COUNT++);

	for(;;);
}

void Enter_FIQ(void)
{
	printf("!!!Enter FIQ. %d\r\n", I_COUNT++);

	for(;;);
}


void ARMTargetInit(void)
{    

	uHALr_InitInterrupts();

}


