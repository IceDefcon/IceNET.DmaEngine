#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

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
            printf("IceNET 3 ---> CreateInterface [%d]\n",CreateInterface);
        }

        // bzero(buffer, MAX);
        
        // i = 0;
        
        // while ((buffer[i++] = getchar()) != '\n')
        // {
        //     // While Loop until ---> \n in this case
        //     // This can be anything
        // }
   
        // write(connection, buffer, sizeof(buffer));

        if(strncmp("read", buffer, 4) == 0)
        {
            ReadDmaTable();
        }   

        if(strncmp("add", buffer, 3) == 0)
        {
            AddTableComponent();
        }

        if(strncmp("exit", buffer, 4) == 0) 
        {
            DeleteDatabase();
            
            printf("Server Exit...\n");
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
        printf("Socket successfully created..\n");
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
        printf("Socket successfully binded..\n");
   
    // Now server is ready to listen and verification
    if ((listen(ServerSocket, 5)) != 0) 
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
    {
        printf("Server listening..\n");
    }
    
    length = sizeof(ClientAddress);
   
    // Accept the data packet from client and verification
    connection = accept(ServerSocket, (SA*)&ClientAddress, &length);
    if (connection < 0) 
    {
        printf("server accept failed...\n");
        exit(0);
    }
    else
    {
        printf("server accept the client...\n");
    }
   
    // Function for chatting between client and server
    ProtocolTCP(connection);
   
    // After chatting close the socket
    close(ServerSocket);

    return 0;
}

