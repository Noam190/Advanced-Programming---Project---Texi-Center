/************************************************************
* File description: TCP implementation.						*
* the class inherit from socket. 							*
* methods of tcp socket type								*
************************************************************/

#include "Tcp.h"

/***********************************************************************
* function name: sendData											   *
* The Input: string data to send									   *
* The output: int number representing the return status		           *
* The Function operation: sending the required data, using his length  *
* and the socket descroptor											   *
***********************************************************************/
int Tcp::sendData(string data,  int descriptor) {
	unsigned long data_len = data.length();
	const char * datas = data.c_str();
	int sent_bytes = (int) send(descriptor, datas, (size_t) data_len, 0);
	if (sent_bytes < 0) {
		//return an error represent error at this method
		return ERROR_SEND;
	}
	//return correct if there were no problem
	return CORRECT;
}

/***********************************************************************
* function name: recive												   *
* The Input: none										               *
* The output: int number representing the return status	               *
* The Function operation: getting data from the other socket to,	   *
* enter it to the buffer and print the data							   *
***********************************************************************/
unsigned long Tcp::receiveData(char *buffer, unsigned long size,  int descriptor) {
    unsigned long read_bytes = (unsigned long) recv(descriptor, buffer, (size_t) size, 0);
    //checking the errors
    if (read_bytes == 0) {
        return CONNECTION_CLOSED;
    }
    else if (read_bytes < 0) {
        //return an error represent error at this method
        return ERROR_RECIVE;
    }
    //return correct if there were no problem
    return read_bytes;
}