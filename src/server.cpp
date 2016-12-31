#include "sockets/Udp.h"
#include "core_classes/Matrix.h"
#include "TaxiCenter.h"
#include "Menu.h"


int main() {
    std::cout << "Hello, from server" << std::endl;
    std::cout << "standard menu" << std::endl;

    TaxiCenter taxiCenter = TaxiCenter();
    int width, height;

    //grid initialize grid and add obstacles if there are any.
    std::cin >> width >> height;
    Matrix grid = Matrix(width, height);
    Clock clock = Clock();
    Menu menu = Menu(taxiCenter, grid, clock);
    //run all the other inputs
    menu.run();

    Udp udp2(1, 5555);
    udp2.initialize();

    char buffer2[1024];
    udp2.receiveData(buffer2, sizeof(buffer2));
    cout << buffer2 << endl;
    udp2.sendData("sup?");

    // support more than one client?
    return 0;
}

