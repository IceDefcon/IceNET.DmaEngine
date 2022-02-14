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

#define MAX 80
#define PORT 8080
#define MAXLINE 1024

#define SA struct sockaddr


// Function designed for chat between client and server.
void CommTCP(int connection)
{
    char buffer[MAX];
    int i;
    // infinite loop for chat
    for (;;) {

        bzero(buffer, MAX);
   
        // read the message from client and copy it in bufferer
        read(connection, buffer, sizeof(buffer));

        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("set", buffer, 3) == 0) 
        {
            CreateInterface = 1;
            printf("CreateInterface ---> %d\n",CreateInterface);
        }

        // print bufferer which contains the client contents
        // printf("From client: %s\t To client : ", buffer);
        bzero(buffer, MAX);
        
        i = 0;
        
        // copy server message in the bufferer
        while ((buffer[i++] = getchar()) != '\n')
        {
            // While Loop until ---> \n in this case
            // This can be anything
        }
   
        // and send that bufferer to client
        write(connection, buffer, sizeof(buffer));
   
        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buffer, 4) == 0) 
        {
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
   
    // socket create and verification
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
    CommTCP(connection);
   
    // After chatting close the socket
    close(ServerSocket);

    return 0;
}


int InitUDPServer(void) 
{
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello from server";
    struct sockaddr_in ServerAddress;
    struct sockaddr_in ClientAddress;
       
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) 
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Server listening..\n");
    }

    memset(&ServerAddress, 0, sizeof(ServerAddress));
    memset(&ClientAddress, 0, sizeof(ClientAddress));
       
    // Filling server information
    ServerAddress.sin_family    = AF_INET; // IPv4
    ServerAddress.sin_addr.s_addr = INADDR_ANY;
    ServerAddress.sin_port = htons(PORT);
       
    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&ServerAddress, sizeof(ServerAddress)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
       
    int n;
    socklen_t len;
   
    len = sizeof(ClientAddress);  //len is value/resuslt
   
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &ClientAddress,&len);
    buffer[n] = '\0';
    printf("Client : %s\n", buffer);
    sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &ClientAddress,len);
    printf("Hello message sent.\n"); 
       
    return 0;
}