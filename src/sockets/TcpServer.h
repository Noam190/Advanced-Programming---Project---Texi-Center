#define CORRECT 0
#define ERROR_SEND 5
#define CONNECTION_CLOSED 8
#define ERROR_RECIVE 6

#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <sstream>
#include <stdexcept>
#include <pthread.h>
#include <list>

using namespace std;

class TcpServer {
public:
    TcpServer(int port);
	void Start();
   // void connectClients(int numOfClients, void (*ClientFunc)(void*), void *args);
    void connectOneClient(int numOfClients, void (*ClientFunc)(void*), void *args);
    unsigned long receiveData(char *buffer, unsigned long size, int client) ;
    static void* threadFunction(void* element);
    int sendData(string data, int client) ;
    int findClientSocketNumber(int client);

        virtual ~TcpServer();

    struct ClientData
	{
		int client_socket;
		int client;
		unsigned int client_size;
		bool online;
        TcpServer* server;
        void (*operationFunc)(void*);
        void * args;

    };

private:
	int port;
	int capacity;
	int num_of_connections;
	int server_socket;
	bool online;
	struct sockaddr_in server_details;
    map<int,ClientData*>* clients;

    pthread_mutex_t connection_locker;
	pthread_mutex_t list_locker;
};

#endif /* SERVER_SERVER_H_ */
