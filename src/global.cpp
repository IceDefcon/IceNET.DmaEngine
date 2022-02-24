//
//
//

#include "global.h"

int CreateInterface;
int ServerConnected;
int DestroyInterface;
int DmaInterfaceTerminate;

void InitGlobals(void)
{
	CreateInterface = 0;
	ServerConnected = 0;
	DestroyInterface = 0;
	DmaInterfaceTerminate = 0;
}