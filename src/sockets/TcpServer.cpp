/*
 * TcpServer.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: uriah
 */

#include "TcpServer.h"

TcpServer::TcpServer(int port) {
	this->port = port;
	this->clients = new list<ClientData*>;
	this->server_socket = -1;
	this->capacity = 50;
	this->num_of_connections = 0;
	this->online = false;
	// Init mutex
	pthread_mutex_init(&this->connection_locker, 0);
	pthread_mutex_init(&this->list_locker, 0);
}

void TcpServer::Start() {
	// Socketing TCP
	this->server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->server_socket == -1)
		cout << ">> Failure: opening socket." << endl;
	else
		cout << ">> Successfully opened socket." << endl;

	// Server details
	memset(&this->server_details, 0, sizeof(this->server_details));
	this->server_details.sin_family = AF_INET;
	this->server_details.sin_addr.s_addr = INADDR_ANY;
	this->server_details.sin_port = htons(this->port);
	bzero(&(this->server_details.sin_zero), 8);

	// Binding
	if (bind(this->server_socket, (struct sockaddr*)&this->server_details,
			sizeof(struct sockaddr)) == -1)
	{
		cout << ">> Failure: binding." << endl;
	}
	else
		cout << ">> Successfully binded." << endl;

	// Listening
	listen(this->server_socket, this->capacity);
	cout << ">> Server is listening on port: " << this->port << "." << endl;
	this->online = true;

//    pthread_t thread;
//    // Create a thread in order to connect the clients.
//    pthread_create(&thread, NULL, threadConnectFunction, (void*) this);
}

void* TcpServer::threadFunction(void* element) {
	ClientData* data = (ClientData*) element;
	data->operationFunc(element);
	data = NULL;
	return NULL;
}

TcpServer::~TcpServer() {
	close(this->server_socket);

	pthread_mutex_destroy(&this->connection_locker);
	pthread_mutex_destroy(&this->list_locker);

	ClientData* data = NULL;
	while (!this->clients->empty())
	{
		data = this->clients->front();
		delete data;
		this->clients->pop_front();
	}
	delete this->clients;
}

void TcpServer::connectClients(int numOfClients, void (*ClientFunc)(void*), void *args) {
    // While we're not out of capacity
    while (numOfClients > 0 && this->online)
    {
        int client;
        int client_socket;
        unsigned int client_size;
        ClientData* data;
        pthread_t thread;

        // If there's some remaining capacity on server
        if (this->num_of_connections < this->capacity)
        {
            // Accepted a client
            client = accept(this->server_socket, (struct sockaddr*)&client_socket, &client_size);
            if (client >= 0)
            {
                // Create the clients data
                data = new ClientData();
                data->client_socket = client_socket;
                data->client = client;
                data->client_size = client_size;
                data->server = this;
                data->online = true;
                data->operationFunc = ClientFunc;
                data->args = args;

                // Push the client to the list

                pthread_mutex_lock(&this->list_locker);
                this->clients->push_back(data);
                pthread_mutex_unlock(&this->list_locker);

                // Create a thread in order to listen to the client
                pthread_create(&thread, NULL, threadFunction, (void*)data);

                --numOfClients;
            }
        }
    }
}
