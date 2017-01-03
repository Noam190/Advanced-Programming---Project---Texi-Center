#include "sockets/Udp.h"
#include "core/Matrix.h"
#include "TaxiCenter.h"
#include "Menu.h"


int main(int argc, char *argv[]) {


    int portNum = atoi(argv[1]);
    Udp udp(true, portNum);
    //udp.initialize();

    Clock clock = Clock();
    TaxiCenter taxiCenter = TaxiCenter(&clock);
    int width, height;

    //grid initialize grid and add obstacles if there are any.
    std::cin >> width >> height;
    Matrix grid = Matrix(width, height);

    Menu menu = Menu(taxiCenter, grid, clock, udp);
    //run all the other inputs
    menu.run();

    return 0;
}

