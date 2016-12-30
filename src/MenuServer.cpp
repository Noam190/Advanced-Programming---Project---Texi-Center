//
// Created by mei on 29/12/16.
//

#include "MenuServer.h"
//  run the input to the program
void MenuServer::run() {
    getObstacles();
    cin.ignore();

    int option;
    cin >> option;
    while (option != 7) {
        cin.ignore();
        switch (option) {
            case 1: //insert drivers
                insertDriver();
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
void MenuServer::insertTaxi() {
    char dummy;
    int id, taxiType;
    char manufacturer, color;
    std::cin >> id >> dummy >> taxiType >> dummy >> manufacturer >> dummy >> color;
    //create the taxi
    TaxiCab cab = createTaxi(id, taxiType, manufacturer, color);
    taxiCenter.addTaxiCab(cab);

}

//insert a new trip from the input arguments
void MenuServer::insertTrip() {
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

//insert a new driver from the input arguments
void MenuServer::insertDriver() {
    char dummy;
    int id, age;
    char status;
    int experience, vehicleId;
    std::cin >> id >> dummy >> age >> dummy >> status >> dummy >> experience >> dummy >> vehicleId;
    Driver d = createDriver(id, age, status, experience, vehicleId);
    taxiCenter.addDriver(d);

}

//create obstacles from the input arguments
void MenuServer::getObstacles() {
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
void MenuServer::getDriverLocation() {
    int idDriver;
    std::cin >> idDriver;
    std::cout << taxiCenter.getDriverLocation(idDriver);

}

// move all the drivers to the next node in the trip
void MenuServer::startDrivingAll() {
    taxiCenter.createRides();
    taxiCenter.moveAllRidesToTheEnd();

}

//constructor to a new
MenuServer::MenuServer(TaxiCenter taxiCenter, Matrix grid) : grid(grid), taxiCenter(taxiCenter) {}
