#include <pthread.h>
#include <iostream>
#include "dump.h"
#include "dma.h"
#include "timer.h"

extern "C" unsigned long Return_4x_16bit_arguments(int arg_1, int arg_2, int arg_3, int arg_4);

//
// The DMA Thread Function  
//
void* DmaThread(void* args)
{
	int i = 0;
    char prev, curr, next;
    ioperm(0x60,0x1,1);
    while(true)
    {
        system("clear");
        curr = (char)Key_Dump();
        if(curr != prev) 
        {
            i++;
        }
        printf("\n  Toggle No:   %x \n",i);
        printf("\n  Last Key:    %hhx\n",curr);
        delay(50);
        prev = curr;
    }
}

int Init_Dma_Thread(void)
{
	// Thread Dma_Id
    pthread_t Dma_Id;
    
    // Creating Thread
    int result = pthread_create(&Dma_Id,NULL,&DmaThread,NULL);

    if(result == 0)
    {
        printf("Thread created successfully.\n");
    }
    else
    {
        printf("Thread not created.\n");
        return 0; /*return from main*/
    }
}

void Dma_dump(void)
{

    Return_4x_16bit_arguments(2,4,6,8);
    Register_Dump();
    long long argumetns = Return_4x_16bit_arguments(2,4,6,8);

    printf("\nReturn Arguments Test\n");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"); 
    printf("argumetns = %llx \n",argumetns);

    int argumetn_1 = (0xffff000000000000 & argumetns) >> 0x30;
    int argumetn_2 = (0x0000ffff00000000 & argumetns) >> 0x20;
    int argumetn_3 = (0x00000000ffff0000 & argumetns) >> 0x10;
    int argumetn_4 = (0x000000000000ffff & argumetns) >> 0x00;

    printf("argumetn_1 = %x \n",argumetn_1);
    printf("argumetn_2 = %x \n",argumetn_2);
    printf("argumetn_3 = %x \n",argumetn_3);
    printf("argumetn_4 = %x \n",argumetn_4);

}