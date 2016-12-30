//
// Created by mei on 29/12/16.
//

#ifndef TAXI_CENTER_MENUSERVER_H
#define TAXI_CENTER_MENUSERVER_H
#include <iostream>
#include "creators/DriverCreator.h"
#include "creators/TripCreator.h"
#include "creators/TaxiCreator.h"
#include "TaxiCenter.h"
#include "core_classes/Grid.h"
class MenuServer {
private:
    Matrix grid;
    TaxiCenter taxiCenter;
public:
    //constructor to a new
    MenuServer(TaxiCenter taxiCenter, Matrix grid);

    //run the funcs with input
    void run();

    //create obstacles from the input arguments
    void getObstacles();

    //insert a new driver from the input arguments
    void insertDriver();

    //insert a new trip from the input arguments
    void insertTrip();

    //insert a new taxi from the input arguments
    void insertTaxi();

    //get the driver location from the input arguments
    void getDriverLocation();

    // move all the drivers to the next node in the trip
    void startDrivingAll();
};

#endif //TAXI_CENTER_MENUSERVER_H
