#include <iostream>     // system
#include <cstring>      // memcpy
#include "dump.h"
#include "timer.h"

#define BUFFER_SIZE 8

int i = 0;
char prev, curr;

bool ready = false;
char source[BUFFER_SIZE];
char dest[BUFFER_SIZE];

void* DmaKeyThread(void* args)
{

    ioperm(0x60,0x1,1);
    memset(source, 0, sizeof(source));
    memset(dest, 0, sizeof(dest));
    while(true)
    {
        system("clear");
        curr = (char)Key_Dump();
        if(curr != prev) 
        {
            source[i] = curr;
            i++;
        }
        if(i == BUFFER_SIZE)
        {
            // TO DO !!!!!
            // Signal Semaphore
            // Need signal semaphore here 
            // To handle buffers
            //
            memcpy(dest, source, sizeof dest);
            memset(source, 0, sizeof(source));
            ready = true;
            i = 0;
        }
        printf("\n  Toggle No:   %x \n",i);
        printf("\n  Last Key:    %hhx\n",curr);
        delay(100);
        prev = curr;
    }
}

void* DmaSwitchThread(void* args)
{
    while(true)
    {
        if(ready == true) 
        {
            printf("I am DMA Switch\n");
            ready = false;
        }
    }
}

int DmaInit(void)
{
	// Thread Id
    pthread_t Dma_Key;
    pthread_t Dma_Switch;
    
    // Creating Thread
    pthread_create(&Dma_Key,NULL,&DmaKeyThread,NULL);
    pthread_create(&Dma_Switch,NULL,&DmaSwitchThread,NULL);
    // To DO
    // Thread Protection !!!!
    // if(result == 0)
    // {
    //     printf("Thread created successfully.\n");
    // }
    // else
    // {
    //     printf("Thread not created.\n");
    //     return 0; /*return from main*/
    // }
    return 0;
}

void DmaDump(void)
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