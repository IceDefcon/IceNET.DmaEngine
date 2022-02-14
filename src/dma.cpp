#include <iostream>     // system
#include <cstring>      // memcpy
#include <semaphore.h>
#include "dump.h"
#include "timer.h"
#include "server.h"
#include "dma.h"
#include "global.h"
#include "interface.h"
#include "database.h"

#define BUFFER_SIZE 128

#ifndef __cplusplus
# include <stdatomic.h>
#else
# include <atomic>
# define _Atomic(X) std::atomic< X >
#endif

_Atomic(int) source[BUFFER_SIZE];
_Atomic(int) dest[BUFFER_SIZE];

sem_t DmaSwitchSemaphore; 
sem_t DmaServerSemaphore; 
sem_t DmaInterfaceSemaphore;
sem_t DmaMySQLSemaphore;

// Thread Id
pthread_t DmaSwitch;
pthread_t DmaServer;
pthread_t DmaInterface;
pthread_t DmaMySQL;

void* DmaSwitchThread(void* args)
{
    sem_wait(&DmaSwitchSemaphore);
    printf("IceNET 0 ---> Dma Switch Thread \n");

    memset(source, 0, sizeof(source));
    memset(dest, 0, sizeof(dest));

    printf("\n");
    dma_engine  Dma_0;
    data_engine Data_0;

    Dma_0.Address = &Data_0.data; 
    
    for(int i = 0;i <ADDRESS_SPACE;i++)
    {
        printf("Dma_0.Address[%d] ---> 0x%x\n",i,(*Dma_0.Address)[i]);
    }
    printf("\n");

    sem_post(&DmaServerSemaphore);
    delay(100); // For the TCP Server to initialize
    sem_post(&DmaInterfaceSemaphore);
    sem_post(&DmaMySQLSemaphore);

    return 0;
}

void* DmaServerThread(void* args)
{
    sem_wait(&DmaServerSemaphore);
    printf("IceNET 1 ---> Dma Server Thread \n");

    InitTCPServer();

    return 0;
}

void* DmaInterfaceThread(void* args)
{
    sem_wait(&DmaInterfaceSemaphore);
    printf("IceNET 2 ---> Dma Interface Thread \n");

    interface *pinterface;

    while(true)
    {
        if(CreateInterface == 1) 
        {
            pinterface = new interface();

            pinterface->setLength(100);
            pinterface->getLength();

            CreateInterface = 0;   
        }

        if(DmaInterfaceTerminate == 1) 
        {
            delay(100); // For the Tcp Server to terminate
            delete pinterface;
            break;
        }
    }

    return 0;
}

void* DmaMySQLThread(void* args)
{
    sem_wait(&DmaMySQLSemaphore);

    InitMySQL();

    return 0;
}

void InitDma(void)
{
    sem_init(&DmaSwitchSemaphore,    0, 1);  // 0 --> only 1 processor, 0 --> inital value = 0 so it must be posted to be able to wait 
    sem_init(&DmaServerSemaphore,    0, 0);
    sem_init(&DmaInterfaceSemaphore, 0, 0);
    sem_init(&DmaMySQLSemaphore,     0, 0);


    // Creating Thread
    if(pthread_create(&DmaSwitch,NULL,&DmaSwitchThread,NULL) != 0) perror("Failed to create Switch thread");
    if(pthread_create(&DmaServer,NULL,&DmaServerThread,NULL) != 0) perror("Failed to create Work thread");
    if(pthread_create(&DmaInterface,NULL,&DmaInterfaceThread,NULL) != 0) perror("Failed to create Work thread");
    if(pthread_create(&DmaMySQL,NULL,&DmaMySQLThread,NULL) != 0) perror("Failed to create Work thread");
    if(pthread_join(DmaSwitch, NULL) != 0) perror("pthread_create() error");
    if(pthread_join(DmaServer, NULL) != 0) perror("pthread_create() error");
    if(pthread_join(DmaInterface, NULL) != 0) perror("pthread_create() error");
    if(pthread_join(DmaMySQL, NULL) != 0) perror("pthread_create() error");

    sem_destroy(&DmaSwitchSemaphore);
    sem_destroy(&DmaServerSemaphore);
    sem_destroy(&DmaInterfaceSemaphore);
    sem_destroy(&DmaMySQLSemaphore);
}

void TerminateDma(void)
{
    printf("\n");
    printf("-----=====[ ------------------- ]=====-----\n");
    printf("-----=====[ Terminating Program ]=====-----\n");
    printf("-----=====[ ------------------- ]=====-----\n");
}
