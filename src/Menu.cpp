//
// Created by noam on 16/12/16.
//

#include "Menu.h"
#include "Serialization.h"
#include "sockets/Udp.h"

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
                expectingDriver(this->taxiCenter);
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
                updateTimeClock();
                advance();
                break;
            case 7: //exit
                return;
            default:
                break;
        }
        cin >> option;
    }
}

//insert a new taxi from the input arguments
void Menu::insertTaxi() {
    char dummy;
    int id, taxiType;
    char manufacturer, color;
    std::cin >> id >> dummy >> taxiType >> dummy >> manufacturer >> dummy >> color;
    //create the taxi
    TaxiCab cab = createTaxi(id, taxiType, manufacturer, color);
    taxiCenter.addTaxiCab(cab);

}

//pass date from server<->client
void Menu::updatesFromClient(TaxiCenter taxiCenter) {
    Udp udp(true, 5555);
    udp.initialize();

    char buffer[1024];
    udp.receiveData(buffer, sizeof(buffer));

    // deserialize driver
    string serial_str_driver;
    std::cin >> serial_str_driver;
    Driver *d = deserialize<Driver>(serial_str_driver);

    TaxiCab taxiCab = taxiCenter.getTaxi(d->getVehicleId());

    //serialize taxi
    string serial_str_vehicle = serialize(&taxiCab);
    //sent back the taxi
    udp.sendData(serial_str_vehicle);


    //serialize trip
    Trip *trip = taxiCenter.insertNewDriver(*d);
    if (trip != NULL) {
        string serial_str_trip = serialize(trip);
        udp.sendData(serial_str_trip);
    }
}

void Menu::serializeClockToClient(TaxiCenter taxiCenter) {
    Udp udp(1, 5555); //TODO NOT SURE WE HAVE TO OPEN NEW UDP
    udp.initialize(); //TODO NOT SURE WE HAVE TO OPEN NEW UDP
    //serialize clock
    Clock * clockForSerialize= &clock;
    string serial_str_clock=serialize(clockForSerialize);
    udp.sendData(serial_str_clock);
}


//expecting a new driver from the client
void Menu::expectingDriver(TaxiCenter taxiCenter){
    int numOfDrivers;
    std::cin >> numOfDrivers;
    for (int i = 0; i < numOfDrivers; ++i) {
        updatesFromClient(taxiCenter);
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
    Trip newTrip = createTrip(grid, id, xStart, yStart, xEnd, yEnd,
                              numOfPass, tariff, timeOfStart);

    int port = taxiCenter.insertTrip(newTrip);
    if (port == 1) {
        Udp udp(true, 5555);
        udp.initialize();
        string serial_str_trip = serialize(&newTrip);
        udp.sendData(serial_str_trip);
    }
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
        grid.addObstacle(n);
        delete n;
        numOfObstacles--;
    }

}

//get the driver location from the input arguments
void Menu::getDriverLocation() {
    int idDriver;
    std::cin >> idDriver;
    std::cout << taxiCenter.getDriverLocation(idDriver);

}

// move all the drivers to the next node in the trip
void Menu::moveAllDriversToTheEnd() {
    taxiCenter.moveAllRidesToTheEnd();
}


//constructor to a new
Menu::Menu(TaxiCenter taxiCenter, Matrix grid, Clock clock)
        : grid(grid), taxiCenter(taxiCenter), clock(clock) {
            this->clock=clock;
}

//update clock time
void Menu::updateTimeClock(){
    this->clock.addToCurrentTime(1);
    serializeClockToClient(taxiCenter);
}

void Menu::advance() {
    taxiCenter.moveAllRidesOneStep();
}
