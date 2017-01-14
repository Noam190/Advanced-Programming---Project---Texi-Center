
#include <map>
#include "TcpServer.h"

TcpServer::TcpServer(int port) {
	this->port = port;
	this->clients = new  list<ClientData*>;
	this->server_socket = -1;
	this->capacity = 50;
	this->num_of_connections = 0;
	this->online = false;

	// Init mutex
	pthread_mutex_init(&this->connection_locker, 0);
	pthread_mutex_init(&this->map_locker, 0);
}

void TcpServer::start() {
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

//void* TcpServer::threadFunction(void* element) {
//	ClientData* data = (ClientData*) element;
//	data->operationFunc(element);
//	data = NULL;
//	return NULL;
//}

TcpServer::~TcpServer() {
	close(this->server_socket);

	pthread_mutex_destroy(&this->connection_locker);
	pthread_mutex_destroy(&this->map_locker);

	ClientData* data = NULL;

    for (list<ClientData*>::iterator it = clients->begin(); it != clients->end(); ++it) {
        delete(*it);
    }

	delete this->clients;
}


int TcpServer::connectClient() {
    int client;
    int client_socket;
    unsigned int client_size;
    ClientData* data;

    // If there's some remaining capacity on server
    if (this->num_of_connections < this->capacity) {
        // Accepted a client
        client = accept(this->server_socket, (struct sockaddr*)&client_socket, &client_size);
        if (client >= 0) {
            // Create the clients data
            data = new ClientData();
            data->client_socket = client_socket;
            data->client = client;
            data->client_size = client_size;
            data->server = this;
            data->online = true;


            // Push the client to the list
            pthread_mutex_lock(&this->map_locker);
            this->clients->push_back(data);
            pthread_mutex_unlock(&this->map_locker);

            return data->client_socket;
        }
    }
}

/***********************************************************************
* function name: sendData											   *
* The Input: string data to send									   *
* The output: int number representing the return status		           *
* The Function operation: sending the required data, using his length  *
* and the socket descroptor											   *
***********************************************************************/
int TcpServer::sendData(string data, int client_socket) {
    if (this->online) {
        unsigned long data_len = data.length();
        const char *datas = data.c_str();
        try {
            // Send the message to the server
            int bytes = (int) send(client_socket, datas, (size_t) data_len, 0);
            if (bytes < 0) {
                //return an error represent error at this method
                return ERROR_SEND;
            } else {
                //return correct if there were no problem
                return CORRECT;
            }
        } catch (...) {
            cout << ">> Error." << endl;
        }
    }
    return CONNECTION_CLOSED;
}

/***********************************************************************
* function name: recive												   *
* The Input: none										               *
* The output: int number representing the return status	               *
* The Function operation: getting data from the other socket to,	   *
* enter it to the buffer and print the data							   *
***********************************************************************/
unsigned long TcpServer::receiveData(char *buffer, unsigned long size, int client_socket) {
    if (this->online) {
        unsigned long read_bytes = 0;
        try {
            read_bytes = (unsigned long) recv(client_socket, buffer, (size_t) size, 0);
            //checking the errors
            if (read_bytes == 0) {
                return CONNECTION_CLOSED;
            } else if (read_bytes < 0) {
                //return an error represent error at this method
                return ERROR_RECIVE;
            }
        } catch (...) {
            cout << ">> Error." << endl;
        }

        //return correct if there were no problem
        return read_bytes;
    }
    return CONNECTION_CLOSED;
}
int TcpServer::findClientSocketNumber(int clientNum) {
//    for (map<int,ClientData*>::iterator it = clients->begin(); it != clients->end(); ++it) {
//        if ((*it).first == clientNum) {
//            return (*it).second->client_socket;
//        }
//    }
}

int TcpServer::sendDataToAllClients(string data) {
    for (list<ClientData*>::iterator it = clients->begin(); it != clients->end(); ++it) {
        this->sendData(data, (*it)->client_socket);
    }
}
