#include <iostream>     // system

#include "dma.h"
#include "server.h"



int main(int argc, char* argv[]) 
{
    system("clear");

    InitDma();

    TerminateDma();

    return 0;
}
