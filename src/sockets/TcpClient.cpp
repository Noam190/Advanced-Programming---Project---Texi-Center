//
// Created by noam on 12/01/17.
//

#include "TcpClient.h"

TcpClient::TcpClient(string ip,int port_num){
    this->ip_address=ip;
    this->port_number = port_num;
    this->isServer = false;
}

int TcpClient::initialize() {
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr((this->ip_address).c_str());
    sin.sin_port = htons((uint16_t) this->port_number);
    if (connect(this->socketDescriptor,
                (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        //return an error represent error at this method
        return ERROR_CONNECT;
    }

    //return correct if there were no problem
    return CORRECT;
}

int TcpClient::sendData(string data) {
    return Tcp::sendData(data, this->socketDescriptor);
}

unsigned long TcpClient::receiveData(char *buffer, unsigned long size) {
    return Tcp::receiveData(buffer,size,this->socketDescriptor);
}
