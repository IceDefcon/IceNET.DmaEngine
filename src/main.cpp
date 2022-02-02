#include <iostream>     // system
#include <unistd.h>     // sleep
#include "dma.h"

int main(int argc, char* argv[]) {

    system("clear");

    DmaInit();

    while(true)
    {
        // This is the main loop
        if(shutdown) break;
    }
    sleep(1); // 1s delay ---> for the treads to temrinate
    return 0;
}
