//
// Created by noam on 16/12/16.
//

#ifndef EX2AP_MANUOPTIONS_H
#define EX2AP_MANUOPTIONS_H

#include <iostream>
#include "creators/DriverCreator.h"
#include "creators/TripCreator.h"
#include "creators/TaxiCreator.h"
#include "TaxiCenter.h"
#include "core_classes/Grid.h"
class Menu {
private:
    Matrix grid;
    TaxiCenter taxiCenter;
public:
    //constructor to a new
    Menu(TaxiCenter taxiCenter, Matrix grid);
    
    //run the funcs with input
    void run(TaxiCenter taxiCenter);
    
    //create obstacles from the input arguments
    void getObstacles();
    
//    //insert a new driver from the input arguments
//    void insertDriver();


    void updatesFromClient(TaxiCenter taxiCenter);


    //insert a new driver from the input arguments
    void expectingDriver(TaxiCenter taxiCenter);
    
    //insert a new trip from the input arguments
    void insertTrip();
    
    //insert a new taxi from the input arguments
    void insertTaxi();
    
    //get the driver location from the input arguments
    void getDriverLocation();
    
    // move all the drivers to the next node in the trip
    void startDrivingAll();
};



#endif //EX2AP_MANUOPTIONS_H
