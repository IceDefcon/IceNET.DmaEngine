#include <stdio.h>
#include <iostream>
using namespace std;

#define ADDRESS_SPACE 8

struct dma_engine
{
    int *Address[ADDRESS_SPACE] = {nullptr};
};

//////////////////////////////////////////////////////
// Hacking DMA address trough the CPU register pairs
//////////////////////////////////////////////////////
extern "C" int input(int param);
int output(void) { return input(6); }
//////////////////////////////////////////////////////

int main(int argc, char* argv[]) {

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Testing definition of null pointers in the struct
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    dma_engine Dma_0;

    for(int i = 0;i <ADDRESS_SPACE;i++)
    {
        printf("Dma_0.Address[%d] [0x%x] \n",i,Dma_0.Address[i]);
    }
    printf("\n");

    dma_engine *pDma_0 = &Dma_0;

    for(int i = 0;i <ADDRESS_SPACE;i++)
    {
        printf("pDma_0->Address[%d] [0x%x] \n",i,pDma_0->Address[i]);
    }

    printf("\n");
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int result = output();
    printf("Addition in assembly ---> expected: 2000 + 6 = 0x7d6 \n");
    printf("The result is: ---> %x\n",result);
    return 0;
}
