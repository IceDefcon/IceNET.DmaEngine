//
//
//

#include "global.h"

int CreateInterface;
int DestroyInterface;
int DmaInterfaceTerminate;

void InitGlobals(void)
{
	CreateInterface = 0;
	DestroyInterface = 0;
	DmaInterfaceTerminate = 0;
}