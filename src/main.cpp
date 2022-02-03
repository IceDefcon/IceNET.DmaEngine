#include <iostream>     // system
#include "dma.h"

int main(int argc, char* argv[]) {

    system("clear");

    DmaInit();

    while(true)
    {
        // This is the main loop
        if(shutdown) break;
    }
    return 0;
}
