//
// Created by noam on 16/12/16.
//

#include "Menu.h"
#include "Serialization.h"
#include "sockets/Udp.h"

//  run the input to the program
void Menu::run(TaxiCenter taxiCenter) {
    getObstacles();
    cin.ignore();

    int option;
    cin >> option;
    while (option != 7) {
        cin.ignore();
        switch (option) {
            case 1: //insert drivers
                expectingDriver(taxiCenter);
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
            case 6: //move all the drivers to driver
                startDrivingAll();
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
void Menu::updatesFromClient(TaxiCenter taxiCenter) {
    Udp udp(1, 5555);
    udp.initialize();

    char buffer[1024];
    udp.receiveData(buffer, sizeof(buffer));
    cout << buffer << endl;
    udp.sendData("sup?");


// deserialize driver
    string serial_str_driver;
    std::cin >> serial_str_driver;
    Driver *d = deserialize<Driver>(serial_str_driver);
    taxiCenter.addDriver(*d);

    TaxiCab taxiCab = taxiCenter.getTaxi(d->getVehicleId());
    //serialize taxi

    string serial_str_vehicle = serialize(&taxiCab);

    //sent back the taxi
    udp.sendData(serial_str_vehicle);

    //serialize trip
    taxiCenter.createRides();
    Trip *trip = taxiCenter.getTrip(d->getId());
    string serial_str_trip=serialize(trip);
    udp.sendData(serial_str_trip);
}

//expecting a new driver from the client
void Menu::expectingDriver(TaxiCenter taxiCenter){
    int numOfDrivers;
    std::cin>>numOfDrivers;
    int index =1;
    while (index<=numOfDrivers){
        updatesFromClient(taxiCenter);
        index++;
    }

}

//insert a new trip from the input arguments
void Menu::insertTrip() {
    char dummy;
    int id;
    int xStart, yStart, xEnd, yEnd;
    int numOfPass;
    double tariff;
    std::cin >> id >> dummy >> xStart >> dummy >> yStart >> dummy >> xEnd
             >> dummy >> yEnd >> dummy >> numOfPass >> dummy >> tariff;
    //create the trip
    Trip newTrip = createTrip(grid, id, xStart, yStart, xEnd, yEnd, numOfPass, tariff);
    taxiCenter.addTrip(newTrip);

}

////insert a new driver from the input arguments
//void Menu::insertDriver() {
//    char dummy;
//    int id, age;
//    char status;
//    int experience, vehicleId;
//    std::cin >> id >> dummy >> age >> dummy >> status >> dummy >> experience >> dummy >> vehicleId;
//    Driver d = createDriver(id, age, status, experience, vehicleId);
//    taxiCenter.addDriver(d);
//
//}

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
void Menu::startDrivingAll() {
    taxiCenter.createRides();
    taxiCenter.moveAllRidesToTheEnd();

}

//constructor to a new 
Menu::Menu(TaxiCenter taxiCenter, Matrix grid) : grid(grid), taxiCenter(taxiCenter) {}
