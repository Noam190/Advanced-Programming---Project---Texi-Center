//
// Created by noam on 12/01/17.
//

#include "TcpServer.h"

TcpServer::TcpServer(int port_num) {
    this->port_number = port_num;
    this->isServer = true;
}

int TcpServer::initialize() {
    //initialize the struct
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons((uint16_t) this->port_number);
    //bind
    if (bind(this->socketDescriptor,
             (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        //return an error represent error at this method
        return ERROR_BIND;
    }
    //listen
    if (listen(this->socketDescriptor, this->backLog) < 0) {
        //return an error represent error at this method
        return ERROR_LISTEN;
    }
    //return correct if there were no problem
    return CORRECT;
}

int TcpServer::sendData(string data, int descriptorCommunicateClient) {
    return Tcp::sendData(data,descriptorCommunicateClient);
}

unsigned long TcpServer::receiveData(char *buffer, unsigned long size, int descriptorCommunicateClient) {
    return Tcp::receiveData(buffer,size,descriptorCommunicateClient);
}

int TcpServer::connectClient() {
    //accept
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int  descriptorCommunicateClient = accept(this->socketDescriptor,
                                               (struct sockaddr *) &client_sin, &addr_len);
    if (descriptorCommunicateClient < 0) {
        //return an error represent error at this method
        return ERROR_ACCEPT;
    }
}
