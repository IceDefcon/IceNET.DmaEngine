#include <iostream>     // system
#include "dma.h"
#include "global.h"

int main(int argc, char* argv[]) 
{
    system("clear");

    InitGlobals();

    InitDma();

    TerminateDma();

    return 0;
}
