//
// Created by noam on 12/01/17.
//

#ifndef TAXI_CENTER_TCPSERVER_H
#define TAXI_CENTER_TCPSERVER_H


#include "Socket.h"
#include "Tcp.h"

class TcpServer : public Tcp {
public:
    /***********************************************************************
    * function name: Tcp												   *
    * The Input: Boolean, true - if server, false if client and port number*
    * The output: none										               *
    * The Function operation: creating new Tcp						       *
    ***********************************************************************/
    TcpServer(int port_num);
    /***********************************************************************
    * function name: ~Tcp												   *
    * The Input: none													   *
    * The output: none										               *
    * The Function operation: default destructor					       *
    ***********************************************************************/
    virtual ~TcpServer();
    /***********************************************************************
	* function name: initialize											   *
	* The Input: none              										   *
	* The output: int number representing the return status		           *
	* The Function operation: initialize the Socket object and getting a   *
	* socket descriptor.												   *
	***********************************************************************/
    int initialize();
    int connectClient();
    /***********************************************************************
    * function name: sendData											   *
    * The Input: string representing the data to send		               *
    * The output: int number representing the return status		           *
    * The Function operation: sending the input data to the socket         *
    * who connect to this socket. 										   *
    ***********************************************************************/
    int sendData(string data, int descriptorCommunicateClient);
    /***********************************************************************
    * function name: recive												   *
    * The Input: none										               *
    * The output: int number representing the return status	               *
    * The Function operation: getting data from the other socket and print *
    * the data															   *
    ***********************************************************************/
    unsigned long receiveData(char *buffer, unsigned long size, int descriptorCommunicateClient);
};


#endif //TAXI_CENTER_TCPSERVER_H
