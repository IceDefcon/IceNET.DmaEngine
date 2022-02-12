#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

// Function designed for chat between client and server.
void communication(int connection)
{
    char buffer[MAX];
    int i;
    // infinite loop for chat
    for (;;) {

        bzero(buffer, MAX);
   
        // read the message from client and copy it in bufferer
        read(connection, buffer, sizeof(buffer));
        
        // print bufferer which contains the client contents
        printf("From client: %s\t To client : ", buffer);
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
            break;
        }
    }
}
   
int InitTCPServer()
{
    socklen_t length;
    int socked, connection;
    struct sockaddr_in ServerAddress, ClientAddress;
   
    // socket create and verification
    socked = socket(AF_INET, SOCK_STREAM, 0);
    if (socked == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&ServerAddress, sizeof(ServerAddress));
   
    // assign IP, PORT
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    ServerAddress.sin_port = htons(PORT);
   
    // Binding newly created socket to given IP and verification
    if ((bind(socked, (SA*)&ServerAddress, sizeof(ServerAddress))) != 0) 
    {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");
   
    // Now server is ready to listen and verification
    if ((listen(socked, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    length = sizeof(ClientAddress);
   
    // Accept the data packet from client and verification
    connection = accept(socked, (SA*)&ClientAddress, &length);
    if (connection < 0) {
        printf("server accept failed...\n");
        exit(0);
    }
    else
        printf("server accept the client...\n");
   
    // Function for chatting between client and server
    communication(connection);
   
    // After chatting close the socket
    close(socked);

    return 0;
}
