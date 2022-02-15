# IceNET.DmaEngine

This is the mathematical model of the DMA Engine

The target model is a parallelepiped volume enclosed in dimentional spheres

It is still under development

	Compile Engine ---> make

Whenever C/C++ function is executed ---> input arguments to that function is translated to assemblies in the following order@

	1st ---> RCX
	2nd ---> RDX
	3rh ---> RSI
	4th ---> RDI

In order to connect to the TCP server and talk to SQL database a TCP client is required 

	#include <netdb.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <sys/socket.h>
	#include <unistd.h> 
	#include <arpa/inet.h>

	#include "clientTCP.h"

	#define TCP_BUFFER_SIZE 80
	#define PORT 8080
	#define SA struct sockaddr

	void communication(int sockfd)
	{
	    char buffer[TCP_BUFFER_SIZE];
	    int n;

	    for (;;) {
	        bzero(buffer, sizeof(buffer));
	        printf("Server Command : ");
	        n = 0;
	        while ((buffer[n++] = getchar()) != '\n')
	        {
	            // While Loop until ---> \n in this case
	            // This can be anything
	        }

	        write(sockfd, buffer, sizeof(buffer));
	        // bzero(buffer, sizeof(buffer));
	        // read(sockfd, buffer, sizeof(buffer));
	        // printf("Server Command :: %s", buffer);
	        if ((strncmp(buffer, "exit", 4)) == 0) {
	            printf("Client Exit...\n");
	            break;
	        }
	    }
	}
	   
	int main()
	{
	    int ClientSocket;
	    struct sockaddr_in ServerAddress;
	   
	    // ClientSocket create and verification
	    ClientSocket = socket(AF_INET, SOCK_STREAM, 0);
	    
	    if (ClientSocket == -1) 
	    {
	        printf("ClientSocket creation failed...\n");
	        exit(0);
	    }
	    else
	    {
	        printf("ClientSocket successfully created..\n");
	    }
	    
	    bzero(&ServerAddress, sizeof(ServerAddress));
	   
	    // assign IP, PORT
	    ServerAddress.sin_family = AF_INET;
	    ServerAddress.sin_addr.s_addr = inet_addr("192.168.0.104");
	    ServerAddress.sin_port = htons(PORT);
	   
	    // connect the client ClientSocket to server ClientSocket
	    if (connect(ClientSocket, (SA*)&ServerAddress, sizeof(ServerAddress)) != 0) {
	        printf("connection with the server failed...\n");
	        exit(0);
	    }
	    else
	    {
	        printf("connected to the server..\n");
	    }
	   
	    // function for chat
	    communication(ClientSocket);
	   
	    // close the ClientSocket
	    close(ClientSocket);
	}




# ICE
