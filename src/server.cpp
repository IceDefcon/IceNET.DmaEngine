#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <iostream>

#include "timer.h"
#include "database.h"
#include "ioctl.h"

#ifndef __cplusplus
# include <stdatomic.h>
#else
# include <atomic>
# define _Atomic(X) std::atomic< X >
#endif

#define MAX_COMMAND 256

_Atomic(int) rx[MAX_COMMAND];
_Atomic(int) tx[MAX_COMMAND];

#define PORT 8080
#define MAXLINE 1024

#define SA struct sockaddr

using namespace std;

void InitAtomics(void)
{
    memset(rx, 0, sizeof(rx));
    memset(tx, 0, sizeof(tx));
}

int GetCommand(int descriptor)
{
    int rx[MAX_COMMAND];
    bzero(rx, sizeof(rx));
    
    cout << "IceNET ---> Receiving Server Command" << endl;   
    read(descriptor, rx, sizeof(rx));

    return rx[0];
}

// void ProcessCommand(char* msg)
// {
//     MySQL TableOperator;

//     cout << "Inside ---> " << msg << endl;

//     if(strncmp("read", msg, 4) == 0)
//     {
//         TableOperator.ReadDmaTable();
//     }   

//     if(strncmp("add", msg, 3) == 0)
//     {
//         TableOperator.InsertIntoDmaTable();
//     }

//     if(strncmp("del", msg, 3) == 0)
//     {
//         TableOperator.DeleteFormDmaTable();
//     }

//     if(strncmp("exit", msg, 4) == 0)
//     {
//         TableOperator.DeleteDmaTable();
//     }

//     if(strncmp("kill", msg, 4) == 0) 
//     {
//         TableOperator.DeleteDmaTable();
//         TableOperator.DeleteServerTable();
//         TableOperator.DeleteDatabase();

//         cout << "IceNET ---> Server Exit" << endl;
//         ServerTerminate = 1;
//     }
// }
   
int InitTCPServer(void)
{
    InitAtomics();

    MySQL TableOperator;

    int ServerSocket;
    int ClientDescriptor;

    socklen_t length;

    struct sockaddr_in ServerAddress;
    struct sockaddr_in ClientAddress;
   
    ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (ServerSocket == -1) 
    {
        cout << "IceNET ---> Socket creation failed..." << endl;
        exit(0);
    }
    else
    {
        cout << "IceNET ---> Socket successfully created.." << endl;
    }
    
    bzero(&ServerAddress, sizeof(ServerAddress));
   
    // assign IP, PORT
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    ServerAddress.sin_port = htons(PORT);
   
    // Binding newly created socket to given IP and verification
    if ((bind(ServerSocket, (SA*)&ServerAddress, sizeof(ServerAddress))) != 0) 
    {
        cout << "IceNET ---> Socket bind failed" << endl;
        exit(0);
    }
    else
        cout << "IceNET ---> Socket successfully binded.." << endl;
   
    // Now server is ready to listen and verification
    if ((listen(ServerSocket, 5)) != 0) 
    {
        cout << "IceNET ---> Server Listen failed" << endl;
        exit(0);
    }
    else
    {
        cout << "IceNET ---> Server successfully listening" << endl;
    }
    
    length = sizeof(ClientAddress);
   
    NextClient:

    // Accept the data packet from client and verification
    ClientDescriptor = accept(ServerSocket, (SA*)&ClientAddress, &length);
    if (ClientDescriptor < 0) 
    {
        cout << "IceNET ---> Server accept failed" << endl;
        exit(0);
    }
    else
    {
        cout << "IceNET ---> Server accept the New client" << endl;
    }

    NextCommand:

    int message = GetCommand(ClientDescriptor);

    cout << "IceNET ---> Command: " << message << endl;

    // ProcessCommand(message);

    // goto NextCommand;
    // goto NextClient;

    close(ServerSocket);

    return 0;
}
