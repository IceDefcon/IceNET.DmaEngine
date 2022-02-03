#include <iostream>     // system
#include <cstring>      // memcpy
#include <semaphore.h>
#include "dump.h"

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
        //
        // Do the work and eventually post the semaphore !!!
        //
        system("clear");
        sem_post(&mutex); // Initial value is Zero so we post it after the buffers are coppied
        if(shutdown) break;
    }
    return 0;
}

void* DmaWorkThread(void* args)
{
    while(true)
    {
        sem_wait(&mutex);
        //
        // Do the work ---> if semaphore was posted !!!
        //
        
    }
    return 0;
}

int DmaInit(void)
{
    sem_init(&mutex, 0, 0);  // 0 --> only 1 processor, 0 --> inital value = 0 so it must be posted to be able to wait 

	// Thread Id
    pthread_t DmaSwitch;
    pthread_t DmaWork;
    
    // Creating Thread
    if(pthread_create(&DmaSwitch,NULL,&DmaSwitchThread,NULL) != 0) perror("Failed to create thread");
    if(pthread_create(&DmaWork,NULL,&DmaWorkThread,NULL) != 0) perror("Failed to create switch thread");

    sem_destroy(&mutex);
    return 0;
}

