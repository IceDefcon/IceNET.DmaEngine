#include <iostream>     // system
#include <cstring>      // memcpy
#include <semaphore.h>
#include "dump.h"
#include "timer.h"

#define BUFFER_SIZE 128

int i = 0;
char prev, curr;
bool shutdown = false;


#ifndef __cplusplus
# include <stdatomic.h>
#else
# include <atomic>
# define _Atomic(X) std::atomic< X >
#endif

_Atomic(char) source[BUFFER_SIZE];
_Atomic(char) dest[BUFFER_SIZE];

sem_t SemaphoreSwitch; 
sem_t SemaphoreWork; 

void* DmaSwitchThread(void* args)
{
    memset(source, 0, sizeof(source));
    memset(dest, 0, sizeof(dest));
    while(true)
    {   
        sem_wait(&SemaphoreSwitch);
        //
        // Do the switch work and signal Working Thread
        //
        printf("Switch Thread ---> i[%x]\n",i);
        if(shutdown) break;
        sem_post(&SemaphoreWork);   // First post 
    }
    return 0;
}

void* DmaWorkThread(void* args)
{
    while(true)
    {
        sem_wait(&SemaphoreWork);
        printf("Work Thread   ---> i[%x]\n",i);
        i++;
        //
        // Do the work
        //
        sem_post(&SemaphoreSwitch);
    }
    return 0;
}

void* DmaShutdownThread(void* args)
{
    while(true)
    {
        delay(10); // Lengt befor Thread will shotd down !!!
        //Register_Dump();
        shutdown = true;
    }
    return 0;
}

int DmaInit(void)
{
    sem_init(&SemaphoreSwitch, 0, 1);  // 0 --> only 1 processor, 0 --> inital value = 0 so it must be posted to be able to wait 
    sem_init(&SemaphoreWork,  0, 0);

	// Thread Id
    pthread_t DmaSwitch;
    pthread_t DmaWork;
    pthread_t DmaShutdown;
    
    // Creating Thread
    if(pthread_create(&DmaSwitch,NULL,&DmaSwitchThread,NULL) != 0) perror("Failed to create Switch thread");
    if(pthread_create(&DmaWork,NULL,&DmaWorkThread,NULL) != 0) perror("Failed to create Work thread");
    if(pthread_create(&DmaShutdown,NULL,&DmaShutdownThread,NULL) != 0) perror("Failed to create Shutdown thread");

    sem_destroy(&SemaphoreSwitch);
    sem_destroy(&SemaphoreWork);
    return 0;
}

