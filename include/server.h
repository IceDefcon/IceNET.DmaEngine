#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */

#ifndef __cplusplus
#include <stdatomic.h>
#else
#include <atomic>
#define _Atomic(X) std::atomic< X >
#endif

#define PORT 8080
#define MAXLINE 1024
#define MAX_COMMAND 256
#define SA struct sockaddr

class Server
{
	private:

		_Atomic(long long int) rx[MAX_COMMAND];
		_Atomic(long long int) tx[MAX_COMMAND];

	    int ServerSocket;
	    int ClientDescriptor;

	    socklen_t AddressLength;

	    sockaddr_in ServerAddress;
	    sockaddr_in ClientAddress;

	public:

		Server();
		~Server();

		void InitSemaphores(void);
		void DeleteSemaphores(void);

		int RunServer(void);

		void GetRxCommand(int descriptor);
		void ProcessRxCommand(void);
};



#endif /* SERVER_H */