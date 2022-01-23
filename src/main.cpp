#include <stdio.h>
#include <iostream>
#include <unistd.h>

#include "Dump.h"

using namespace std;

#define ADDRESS_SPACE 8

struct dma_engine
{
    int (*address)[ADDRESS_SPACE] = {nullptr};
};

struct data_engine
{
    int data[ADDRESS_SPACE] = {0x10,0x14,0x18,0x1B,0x20,0x24,0x28,0x2B};
};

extern "C" unsigned long Return_4x_16bit_arguments(int arg_1, int arg_2, int arg_3, int arg_4);

int main(int argc, char* argv[]) {

    system("clear");
    //
    // Null pointer structure incremented every ---> 20h
    //
    dma_engine dma_0;
    dma_engine *pdma_0 = &dma_0;

    printf("pdma_0\n"); 
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"); 
    for(int i = 0;i <ADDRESS_SPACE;i++)
    {
        printf("pdma_0->address[%d] [%#018" PRIx64 " ] \n",i,pdma_0->address[i]);
    }
    printf("\n");

    data_engine data_0;
    dma_0.address = &data_0.data;

    printf("Again pdma_0\n"); 
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"); 
    for(int i = 0;i <ADDRESS_SPACE;i++)
    {
        printf("pdma_0->address[%d] [%#018" PRIx64 " ] \n",i,pdma_0->address[i]);
    }
    printf("\n");
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Return_4x_16bit_arguments(2,4,6,8);
    Register_Dump();
    long long argumetns = Return_4x_16bit_arguments(2,4,6,8);

    printf("argumetns = %llx \n",argumetns);

    int argumetn_1 = (0xffff000000000000 & argumetns) >> 0x30;
    int argumetn_2 = (0x0000ffff00000000 & argumetns) >> 0x20;
    int argumetn_3 = (0x00000000ffff0000 & argumetns) >> 0x10;
    int argumetn_4 = (0x000000000000ffff & argumetns) >> 0x00;

    printf("argumetn_1 = %x \n",argumetn_1);
    printf("argumetn_2 = %x \n",argumetn_2);
    printf("argumetn_3 = %x \n",argumetn_3);
    printf("argumetn_4 = %x \n",argumetn_4);
    return 0;
}
