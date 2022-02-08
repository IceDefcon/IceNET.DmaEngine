#include <iostream>     // system
#include <cstring>      // memcpy
#include <semaphore.h>
#include "dump.h"
#include "timer.h"
#include "server.h"

#define BUFFER_SIZE 128

int i = 0;
char prev, curr;

#ifndef __cplusplus
# include <stdatomic.h>
#else
# include <atomic>
# define _Atomic(X) std::atomic< X >
#endif

_Atomic(char) source[BUFFER_SIZE];
_Atomic(char) dest[BUFFER_SIZE];

sem_t DmaSwitchSemaphore; 
sem_t DmaServerSemaphore; 

// Thread Id
pthread_t DmaSwitch;
pthread_t DmaServer;

void* DmaSwitchThread(void* args)
{

    memset(source, 0, sizeof(source));
    memset(dest, 0, sizeof(dest));

    sem_wait(&DmaSwitchSemaphore);
    //
    // Do the switch work and signal Working Thread
    //
    printf("Dma Switch Thread\n");
    sem_post(&DmaServerSemaphore);
    printf("Dma Switch Thread ---> Post: DmaServerSemaphore\n");

    return 0;
}

void* DmaServerThread(void* args)
{
    sem_wait(&DmaServerSemaphore);
    printf("Dma Server Thread\n");

    InitTCPServer();

    return 0;
}


void DmaInit(void)
{
    sem_init(&DmaSwitchSemaphore, 0, 1);  // 0 --> only 1 processor, 0 --> inital value = 0 so it must be posted to be able to wait 
    sem_init(&DmaServerSemaphore,  0, 0);

    // Creating Thread
    if(pthread_create(&DmaSwitch,NULL,&DmaSwitchThread,NULL) != 0) perror("Failed to create Switch thread");
    if(pthread_create(&DmaServer,NULL,&DmaServerThread,NULL) != 0) perror("Failed to create Work thread");
    if(pthread_join(DmaSwitch, NULL) != 0) perror("pthread_create() error");
    if(pthread_join(DmaServer, NULL) != 0) perror("pthread_create() error");

    sem_destroy(&DmaSwitchSemaphore);
    sem_destroy(&DmaServerSemaphore);
}

void DmaTerminate(void)
{
    printf("\n");
    printf("-----=====[ ------------------- ]=====-----\n");
    printf("-----=====[ Terminating Program ]=====-----\n");
    printf("-----=====[ ------------------- ]=====-----\n");
}
