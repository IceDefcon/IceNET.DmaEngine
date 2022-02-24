#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "timer.h"
#include "global.h"
#include "database.h"

#define MAX 80
#define PORT 8080
#define MAXLINE 1024

#define SA struct sockaddr


void ProtocolTCP(int connection)
{
    char buffer[MAX];
    int i;

    while(true) 
    {
        bzero(buffer, MAX);
   
        read(connection, buffer, sizeof(buffer));

        if (strncmp("set", buffer, 3) == 0) 
        {
            CreateInterface = 1;
            printf("IceNET ---> CreateInterface [%d]\n",CreateInterface);
        }

        if(strncmp("read", buffer, 4) == 0)
        {
            ReadDmaTable();
        }   

        if(strncmp("add", buffer, 3) == 0)
        {
            InsertIntoDmaTable();
        }

        if(strncmp("del", buffer, 3) == 0)
        {
            DeleteFormDmaTable();
        }

        if(strncmp("exit", buffer, 4) == 0)
        {
            DeleteDmaTable();
            break;
        }

        if(strncmp("terminate", buffer, 9) == 0) 
        {
            DeleteDmaTable();
            DeleteServerTable();
            DeleteDatabase();

            printf("IceNET ---> Server Exit \n");
            DmaInterfaceTerminate = 1;
            break;
        }
    }
}
   
int InitTCPServer(void)
{
    int ServerSocket;
    int connection;
    socklen_t length;
    struct sockaddr_in ServerAddress;
    struct sockaddr_in ClientAddress;
   
    ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (ServerSocket == -1) 
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
    {
        printf("IceNET ---> Socket successfully created..\n");
    }
    
    bzero(&ServerAddress, sizeof(ServerAddress));
   
    // assign IP, PORT
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    ServerAddress.sin_port = htons(PORT);
   
    // Binding newly created socket to given IP and verification
    if ((bind(ServerSocket, (SA*)&ServerAddress, sizeof(ServerAddress))) != 0) 
    {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("IceNET ---> Socket successfully binded..\n");
   
    // Now server is ready to listen and verification
    if ((listen(ServerSocket, 5)) != 0) 
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
    {
        printf("IceNET ---> Server listening..\n");
        ServerConnected = 1;
    }
    
    length = sizeof(ClientAddress);
   
    NextClient:

    // Accept the data packet from client and verification
    connection = accept(ServerSocket, (SA*)&ClientAddress, &length);
    if (connection < 0) 
    {
        printf("IceNET ---> Server accept failed...\n");
        exit(0);
    }
    else
    {
        printf("IceNET ---> Server accept the client...\n");
        CreateDmaTable();
    }
   
    // Function for chatting between client and server
    ProtocolTCP(connection);
    if(DmaInterfaceTerminate == 0) goto NextClient;

    // After chatting close the socket
    close(ServerSocket);

    ServerConnected = 0;

    return 0;
}

