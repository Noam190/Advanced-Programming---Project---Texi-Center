
#include "sockets/Udp.h"
#include "core_classes/Point.h"


int main(int argc, char *argv[]) {
    std::cout << "Hello, from client" << std::endl;

    cout << argv[1] << endl;
    Udp udp(0, atoi(argv[1]));
    udp.initialize();

    char buffer[1024];
    udp.sendData("hello");
    udp.receiveData(buffer, sizeof(buffer));
    cout << buffer << endl;

    return 0;
}