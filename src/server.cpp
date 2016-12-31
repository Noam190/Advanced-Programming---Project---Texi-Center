#include "sockets/Udp.h"
#include "core_classes/Matrix.h"
#include "TaxiCenter.h"
#include "Menu.h"


int main() {
    std::cout << "Hello, from server" << std::endl;
    std::cout << "standard menu" << std::endl;

    Udp udp(1, 5555);
    udp.initialize();

    Clock clock = Clock();
    TaxiCenter taxiCenter = TaxiCenter(&clock);
    int width, height;

    //grid initialize grid and add obstacles if there are any.
    std::cin >> width >> height;
    Matrix grid = Matrix(width, height);
    Menu menu = Menu(taxiCenter, grid, &clock, udp);
    //run all the other inputs
    menu.run();


//    char buffer2[1024];
//    udp.receiveData(buffer2, sizeof(buffer2));
//    cout << buffer2 << endl;
//    udp.sendData("sup?");

    // support more than one client?
    return 0;
}

