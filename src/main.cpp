#include <iostream>     // system
#include <unistd.h>     // sleep
#include "dma.h"

int main(int argc, char* argv[]) {

    system("clear");

    DmaInit();

    while(true)
    {
        // This is main loop
        if(shutdown == 1) break;
    }
    sleep(1);
    return 0;
}
