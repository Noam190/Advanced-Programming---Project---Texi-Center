#include "sockets/Udp.h"
#include "core_classes/Matrix.h"
#include "TaxiCenter.h"
#include "Menu.h"


int main(int argc, char *argv[]) {
    std::cout << "Hello, from server" << std::endl;
    std::cout << "standard menu" << std::endl;

    int portNum = atoi(argv[1]);
    Udp udp(true, portNum);
    //udp.initialize();

    Clock clock = Clock();
    TaxiCenter taxiCenter = TaxiCenter(&clock);
    int width, height;

    //grid initialize grid and add obstacles if there are any.
    std::cin >> width >> height;
    Matrix grid = Matrix(width, height);
//    grid.initDistanceForAll(-1);
//    Node* start = grid.getNode(0,0);
//    Node* end = grid.getNode(2,2);
//
//    // Mark all the vertices as not visit
//    std::list<Node *> pathNodes = BFS(start, end);
//    for (list<Node *>::iterator it = pathNodes.begin(); it != pathNodes.end() ; ++it) {
//        Node* n = *(it);
//        cout << *n;
//    }

    Menu menu = Menu(taxiCenter, grid, clock, udp);
    //run all the other inputs
    menu.run();


//    char buffer2[1024];
//    udp.receiveData(buffer2, sizeof(buffer2));
//    cout << buffer2 << endl;
//    udp.sendData("sup?");

    // support more than one client?
    return 0;
}

