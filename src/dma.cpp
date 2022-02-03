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

sem_t mutex; 

void* DmaSwitchThread(void* args)
{
    memset(source, 0, sizeof(source));
    memset(dest, 0, sizeof(dest));
    while(true)
    {   
        sem_wait(&mutex);
        //
        // Do the work and eventually post the semaphore !!!
        //
        printf("Switch Thread ---> i[%x]\n",i);
        if(shutdown) break;
        sem_post(&mutex);   // First post 
        delay(100);         // For the Work Thread to Initialize
    }
    return 0;
}

void* DmaWorkThread(void* args)
{
    delay(1000); // Delay 1s ---> So Switch Thread is 1st 
    while(true)
    {
        sem_wait(&mutex);
        printf("Work Thread   ---> i[%x]\n",i);
        i++;
        //
        // Do the work ---> if semaphore was posted !!!
        //
        sem_post(&mutex);   // For the Switch thread
        delay(200);         // For the Switch thread 
    }
    return 0;
}

void* DmaShutdownThread(void* args)
{
    while(true)
    {
        delay(5000); // Lengt befor Thread will shotd down !!!
        shutdown = true;
    }
    return 0;
}

int DmaInit(void)
{
    sem_init(&mutex, 0, 0);  // 0 --> only 1 processor, 0 --> inital value = 0 so it must be posted to be able to wait 

	// Thread Id
    pthread_t DmaSwitch;
    pthread_t DmaWork;
    pthread_t DmaShutdown;
    
    // Creating Thread
    if(pthread_create(&DmaSwitch,NULL,&DmaSwitchThread,NULL) != 0) perror("Failed to create Switch thread");
    if(pthread_create(&DmaWork,NULL,&DmaWorkThread,NULL) != 0) perror("Failed to create Work thread");
    if(pthread_create(&DmaShutdown,NULL,&DmaShutdownThread,NULL) != 0) perror("Failed to create Shutdown thread");

    sem_destroy(&mutex);
    return 0;
}

