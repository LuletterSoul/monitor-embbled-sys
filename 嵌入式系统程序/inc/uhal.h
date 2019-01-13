/* ARM board targetting source file.*/

#define uHALr_InitInterrupts()		ISR_Init()

/*** Called by ARMTargetInit() ***/
//Reset memory management unit.
void uHALr_ResetMMU(void);


//Initialize timer that is used OS.
void uHALr_InitTimers(void);

/*** Called by ARMTargetStart() ***/
//Request the system timer.
//return value 1:success   0:fail
int uHALr_RequestSystemTimer(void *tick, const unsigned char *str);

//Start system timer & enable the interrupt.
void uHALr_InstallSystemTimer(void);

//for debugging

void ARMTargetInit(void);
