#include <iostream>     // system
#include <cstring>      // memcpy
#include <semaphore.h>
#include "dump.h"
#include "timer.h"

#define BUFFER_SIZE 16

int i = 0;
char prev, curr;

char source[BUFFER_SIZE];
char dest[BUFFER_SIZE];

sem_t mutex; 

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
            memcpy(dest, source, sizeof dest);
            memset(source, 0, sizeof(source));
            i = 0;
            sem_post(&mutex); // Initial value is Zero so we post it after the buffers are coppied
        }
        printf("\n  Toggle No       : %x \n",i);
        printf("\n  Last Key        : %hhx\n",curr);

        delay(100);
        prev = curr;
    }
}

void* DmaSwitchThread(void* args)
{
    while(true)
    {
        sem_wait(&mutex);
        printf("ready is true ---> So I execute 0\n");
        printf("ready is true ---> So I execute 1\n");
        printf("ready is true ---> So I execute 2\n");
        printf("ready is true ---> So I execute 3\n");        
    }
}

int DmaInit(void)
{
    sem_init(&mutex, 0, 0);  // 0 --> only 1 processor, 0 --> inital value = 0 so it must be posted to be able to wait 

	// Thread Id
    pthread_t DmaKey;
    pthread_t DmaSwitch;
    
    // Creating Thread
    if(pthread_create(&DmaKey,NULL,&DmaKeyThread,NULL) != 0) perror("Failed to create thread");
    if(pthread_create(&DmaSwitch,NULL,&DmaSwitchThread,NULL) != 0) perror("Failed to create switch thread");

    sem_destroy(&mutex);
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