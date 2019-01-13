#include "inc/macro.h"
//void Uart_SendByten(int,U8);
void Uart_SendByten(int Uartnum, U8 data);
char Uart_Getchn(char* Revdata, int Uartnum, int timeout);