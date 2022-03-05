#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <semaphore.h>

#define MAX 80
#define PORT 8080
#define MAXLINE 1024

#define SA struct sockaddr

int ServerTerminate = 0;

sem_t DmaSwitchSemaphore; 
sem_t DmaServerSemaphore; 
sem_t DmaInterfaceSemaphore;
sem_t DmaMySQLSemaphore;



#endif /* SEMAPHORES_H */