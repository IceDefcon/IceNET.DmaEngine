#include <iostream>
#include "dma.h"

using namespace std;

int main(int argc, char* argv[]) {

    system("clear");

    Init_Dma_Thread();

    Dma_dump();

    while(true)
    {
        // This is main loop      
    }

    return 0;
}
