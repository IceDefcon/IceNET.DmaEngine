//
//
//
#include <iostream>     // system
#include <semaphore.h>

#include "dump.h"
#include "timer.h"
#include "server.h"
#include "dma.h"
#include "database.h"
#include "server.h"

using namespace std;

// Semaphores
sem_t DmaSwitchSemaphore; 
sem_t DmaServerSemaphore; 
sem_t DmaMySQLSemaphore;

// Threads
pthread_t DmaSwitch;
pthread_t DmaServer;
pthread_t DmaMySQL;

void* DmaSwitchThread(void* args)
{
    sem_wait(&DmaSwitchSemaphore);
    cout << "IceNET ---> Dma Switch Thread" << endl;

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
    sem_post(&DmaMySQLSemaphore);

    return 0;
}

void* DmaServerThread(void* args)
{
    sem_wait(&DmaServerSemaphore);
    cout << "IceNET ---> Dma Server Thread" << endl;

    Server Instance;

    Instance.RunServer();

    delay(100); // For the Tcp Server to terminate

    return 0;
}

void* DmaMySQLThread(void* args)
{
    MySQL Dma;

    sem_wait(&DmaMySQLSemaphore);

    //Dma.InitMySQL();

    //Dma.CreateServerTable();

    return 0;
}

void InitDma(void)
{
    sem_init(&DmaSwitchSemaphore,    0, 1);  // 0 --> only 1 processor, 0 --> inital value = 0 so it must be posted to be able to wait 
    sem_init(&DmaServerSemaphore,    0, 0);
    sem_init(&DmaMySQLSemaphore,     0, 0);


    // Creating Thread
    if(pthread_create(&DmaSwitch,NULL,&DmaSwitchThread,NULL) != 0) perror("Failed to create Switch thread");
    if(pthread_create(&DmaServer,NULL,&DmaServerThread,NULL) != 0) perror("Failed to create Work thread");
    if(pthread_create(&DmaMySQL,NULL,&DmaMySQLThread,NULL) != 0) perror("Failed to create Work thread");
    if(pthread_join(DmaSwitch, NULL) != 0) perror("pthread_create() error");
    if(pthread_join(DmaServer, NULL) != 0) perror("pthread_create() error");
    if(pthread_join(DmaMySQL, NULL) != 0) perror("pthread_create() error");

    sem_destroy(&DmaSwitchSemaphore);
    sem_destroy(&DmaServerSemaphore);
    sem_destroy(&DmaMySQLSemaphore);
}

void TerminateDma(void)
{
    printf("\n");
    printf("-----=====[ ------------------- ]=====-----\n");
    printf("-----=====[ Terminating Program ]=====-----\n");
    printf("-----=====[ ------------------- ]=====-----\n");
}
