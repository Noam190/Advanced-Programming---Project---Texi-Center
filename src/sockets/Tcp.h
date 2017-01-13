/************************************************************
* File description: TCP header file. the class inherit from	*
* socket. methods of tcp socket type						*
************************************************************/

#ifndef TCP_H_
#define TCP_H_
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

//return values to each function if error happened
#define CORRECT 0
#define ERROR_SOCKET 1
#define ERROR_BIND 2
#define ERROR_LISTEN 3
#define ERROR_CONNECT 4
#define ERROR_SEND 5
#define ERROR_RECIVE 6
#define ERROR_ACCEPT 7
#define CONNECTION_CLOSED 8
#define NONE 0

#define IP "127.0.0.1"

class Tcp {
protected:
    //true is the socket is for a server, false if for a client
    bool isServer;
    //the socket descriptor return from sock()
    int socketDescriptor;
    //ip address
    string ip_address;
    int backLog;
    //port number
    int port_number;
public:
    Tcp();
    ~Tcp();
    /***********************************************************************
    * function name: sendData											   *
    * The Input: string representing the data to send		               *
    * The output: int number representing the return status		           *
    * The Function operation: sending the input data to the socket         *
    * who connect to this socket. 										   *
    ***********************************************************************/
    virtual int sendData(string data, int descriptor);

    /***********************************************************************
    * function name: recive												   *
    * The Input: none										               *
    * The output: int number representing the return status	               *
    * The Function operation: getting data from the other socket and print *
    * the data															   *
    ***********************************************************************/
    virtual unsigned long receiveData(char *buffer, unsigned long size, int descriptor);

};

#endif /* TCP_H_ */
