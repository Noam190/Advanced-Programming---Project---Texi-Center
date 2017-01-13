//
// Created by noam on 16/12/16.
//

#include "Menu.h"
#include "ThreadPool.h"
#include <pthread.h>

//  run the input to the program
void Menu::run() {
    getObstacles();
    cin.ignore();
    int option;
    cin >> option;
    while (option != 7) {
        cin.ignore();
        switch (option) {
            case 1: //insert drivers
                expectingDriver();
                break;
            case 2: //insert trip
                insertTrip();
                break;
            case 3: //insert taxi
                insertTaxi();
                break;
            case 4: //get the drivers location
                getDriverLocation();
                break;
            case 6: //move all the drivers to end
                moveAllDriversToTheEnd();
                break;
            case 9: //update clock time
                advance();
                break;


            default:
                break;
        }
        cin >> option;
    }
    sendDataToAllClient("E");
 //   taxiCenter.~TaxiCenter();
    return;
}
class DriverAgrs{
public:
    TaxiCenter* taxiCenter;
    TcpServer* tcp;
    bool stop;
    DriverAgrs(TaxiCenter* taxiCenter,int  connectNum, TcpServer* tcp, bool stop) {
        this->taxiCenter = taxiCenter;
        this->tcp = tcp;
        this->stop = stop;
    }
};
//insert a new taxi from the input arguments
void Menu::insertTaxi() {
    char dummy;
    int id, taxiType;
    char manufacturer, color;
    std::cin >> id >> dummy >> taxiType >> dummy >> manufacturer >> dummy >> color;
    //create the taxi
    TaxiCab* cab = createTaxi(id, taxiType, manufacturer, color);
    this->taxiCenter->addTaxiCab(cab);

}

//pass date from server<->client
void Menu::updatesFromClient() {
//    unsigned long readBytes;
//    char buffer[1024];
//    std::fill_n(buffer, 1024, 0);
//    readBytes = this->tcp->receiveData(buffer, sizeof(buffer));
//
//    // deserialize driver
//    string serial_str_driver(buffer, readBytes);
//    Driver *d = deserialize<Driver>(serial_str_driver);
//
//    TaxiCab* taxiCab = this->taxiCenter->getTaxi(d->getVehicleId());
//
//    //serialize taxi
//    string serial_str_taxi = serialize(taxiCab);
//    //sent back the taxi
//    this->tcp->sendData(serial_str_taxi);
//
//    //add driver to the taxi-center.
//    this->taxiCenter->addClient(d);

}

//expecting a new driver from the client
void Menu::expectingDriver() {
    int numOfDrivers;
    int connectNum ;
    std::cin >> numOfDrivers;
    this->numOfDrivers = numOfDrivers;

    for (int i = 0; i < numOfDrivers; ++i) {
        pthread_t t1 = (pthread_t) i;
        DriverAgrs* args = new DriverAgrs(taxiCenter,connectNum,tcp, false);
        threadPool->createThread(t1,addClient,args);
    }
}

//insert a new trip from the input arguments
void Menu::insertTrip() {
    char dummy;
    int id;
    int xStart, yStart, xEnd, yEnd;
    int numOfPass;
    double tariff;
    int timeOfStart;
    std::cin >> id >> dummy >> xStart >> dummy >> yStart >> dummy >> xEnd
             >> dummy >> yEnd >> dummy >> numOfPass >> dummy >> tariff
             >> dummy >>timeOfStart;
    //create the trip
    Trip* newTrip = createTrip(threadPool, grid, id, xStart, yStart, xEnd, yEnd,
                              numOfPass, tariff, timeOfStart);

    taxiCenter->insertTrip(newTrip);
}

//create obstacles from the input arguments
void Menu::getObstacles() {
    int numOfObstacles;
    char dummy;
    int x;
    int y;
    //num of obstacles
    std::cin >> numOfObstacles;
    while (numOfObstacles > 0) {
        std::cin >> x >> dummy  >> y;
        Node* n = new NodeMatrix(x, y);
        this->grid->addObstacle(n);
        delete n;
        numOfObstacles--;
    }

}

//get the driver location from the input arguments
void Menu::getDriverLocation() {
    int idDriver;
    std::cin >> idDriver;
    std::cout << this->taxiCenter->getDriverLocation(idDriver);
}

// move all the drivers to the next node in the trip
void Menu::moveAllDriversToTheEnd() {
    this->taxiCenter->moveAllRidesToTheEnd();
}


//constructor to a new
Menu::Menu(ThreadPool* threadPool,TaxiCenter *taxiCenter, Matrix *grid,
           Clock *clock, TcpServer *tcp, int numOfDrivers)
        : threadPool(threadPool),grid(grid), taxiCenter(taxiCenter),
          clock(clock), tcp(tcp), numOfDrivers(0) {
    tcp->initialize();
    this->numOfDrivers = numOfDrivers;
}

// move the drivers to the next point.
void Menu::advance() {
    this->clock->addToCurrentTime(1);

    this->taxiCenter->moveAllRidesOneStep();

    this->taxiCenter->createRides();
}



void * Menu::addClient(void *args){
    DriverAgrs* argsD =(DriverAgrs*) args;
    bool stop = argsD->stop;
    TcpServer* tcp = argsD->tcp;
    TaxiCenter* taxiCenter = argsD->taxiCenter;
    int connectNum = tcp->connectClient();

    unsigned long readBytes;
    char buffer[1024];
    std::fill_n(buffer, 1024, 0);
    readBytes = tcp->receiveData(buffer, sizeof(buffer), connectNum);

    // deserialize driver
    string serial_str_driver(buffer, readBytes);
    Driver *d = deserialize<Driver>(serial_str_driver);

    TaxiCab* taxiCab = taxiCenter->getTaxi(d->getVehicleId());

    //serialize taxi
    string serial_str_taxi = serialize(taxiCab);
    //sent back the taxi
    tcp->sendData(serial_str_taxi, connectNum);

    //add driver to the taxi-center.
    taxiCenter->addDriver(d);

    Trip* trip;
    while (!stop) {
        trip = taxiCenter->getTripById(d->getId());
        if (trip != NULL ) {
            tcp->sendData("T", connectNum);
            string serial_str_trip = serialize(trip);
            tcp->sendData(serial_str_trip, connectNum);
        } else{
            stop= true;
        }
    }
}
