//
//
//
#include <iostream>

#include "ioctl.h"

using namespace std;

static long Ice_Ioctl(ComplexData *pData, unsigned int cmd, unsigned long arg)
{
	switch(cmd) 
	{
		case ICE_IOCTL_0:
			cout << "Case 0" << endl;
			break;
		case ICE_IOCTL_1:
			cout << "Case 1" << endl;
			break;
		default:
			cout << "Default Executed" << endl;
			break;
	}
	return 0;
}

static API IceNET =
{
    .ioctl = Ice_Ioctl,
};

