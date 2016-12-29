#include <iostream>
#include "sockets/Udp.h"


int main() {
    std::cout << "Hello, from server" << std::endl;

    Udp udp(1, 5555);
    udp.initialize();

    char buffer[1024];
    udp.receiveData(buffer, sizeof(buffer));
    cout << buffer << endl;
    udp.sendData("sup?");


    Udp udp2(1, 5555);
    udp2.initialize();

    char buffer2[1024];
    udp2.receiveData(buffer2, sizeof(buffer2));
    cout << buffer2 << endl;
    udp2.sendData("sup?");

    // support more than one client?
    return 0;
}
