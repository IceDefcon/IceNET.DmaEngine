//
//
//
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <semaphore.h>

#include "timer.h"
#include "database.h"
#include "ioctl.h"
#include "server.h"

sem_t ServerRxSemaphore; 
sem_t ServerTxSemaphore; 

using namespace std;

Server::Server()
{
    memset(rx, 0, sizeof(rx));
    memset(tx, 0, sizeof(tx));

    ServerSocket = 0;
    ClientDescriptor = 0;

    AddressLength = 0;

    ServerAddress.sin_family = 0;       // Address family: AF_INET
    ServerAddress.sin_port = 0;         // Port in network byte order
    ServerAddress.sin_addr.s_addr = 0;  // Internet address ---> Address in network byte order

    ClientAddress.sin_family = 0;
    ClientAddress.sin_port = 0;
    ClientAddress.sin_addr.s_addr = 0;
}

Server::~Server()
{

}

void Server::GetCommand(int descriptor)
{
    bzero(rx, sizeof(rx));
    
    cout << "IceNET ---> Receiving Server Command" << endl;   
    read(descriptor, rx, sizeof(rx));

    sem_post(&ServerRxSemaphore);

    cout << "IceNET ---> Code Word 0: " << hex << *(rx+0) << endl;
    cout << "IceNET ---> Code Word 1: " << hex << *(rx+1) << endl;
    cout << "IceNET ---> Code Word 2: " << hex << *(rx+2) << endl;
    cout << "IceNET ---> Code Word 3: " << hex << *(rx+3) << endl;

}

void Server::ProcessCommand(void)
{
    sem_wait(&ServerRxSemaphore);

    // MySQL TableOperator;

    // cout << "Inside ---> " << *cmd << endl;
    // cout << "Inside ---> " << *(cmd+1) << endl <<endl;

    // if(strncmp("read", cmd, 4) == 0)
    // {
    //     TableOperator.ReadDmaTable();
    // }   

    // if(strncmp("add", cmd, 3) == 0)
    // {
    //     TableOperator.InsertIntoDmaTable();
    // }

    // if(strncmp("del", cmd, 3) == 0)
    // {
    //     TableOperator.DeleteFormDmaTable();
    // }

    // if(strncmp("exit", cmd, 4) == 0)
    // {
    //     TableOperator.DeleteDmaTable();
    // }

    // if(strncmp("kill", cmd, 4) == 0) 
    // {
    //     TableOperator.DeleteDmaTable();
    //     TableOperator.DeleteServerTable();
    //     TableOperator.DeleteDatabase();

    //     cout << "IceNET ---> Server Exit" << endl;
    //     ServerTerminate = 1;
    // }
}

void Server::InitSemaphores(void)
{
    sem_init(&ServerRxSemaphore, 0, 0);
    sem_init(&ServerTxSemaphore, 0, 0);
}

void Server::DeleteSemaphores(void)
{
    sem_destroy(&ServerRxSemaphore);
    sem_destroy(&ServerTxSemaphore);
}

int Server::RunServer(void)
{
    InitSemaphores();

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
    ServerAddress.sin_port = htons(PORT);
    ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    
   
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
    
    AddressLength = sizeof(ClientAddress);
   
    NextClient:

    // Accept the data packet from client and verification
    ClientDescriptor = accept(ServerSocket, (SA*)&ClientAddress, &AddressLength);
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

    GetCommand(ClientDescriptor);

    // cout << "Rx ---> " << RxMessage << endl;
    // cout << "Rx ---> " << (RxMessage+1) << endl;
    // cout << "Rx ---> " << (RxMessage+2) << endl;
    // cout << "Rx ---> " << (RxMessage+3) << endl;

    // ProcessCommand(&RxMessage[0]);
    // ProcessCommand(&RxMessage[1]);

    // goto NextCommand;
    // goto NextClient;

    close(ServerSocket);

    DeleteSemaphores();

    return 0;
}
