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
#include "Clock.h"

class Menu {
private:
    Matrix grid;
    TaxiCenter taxiCenter;
    Clock clock;
public:
    //constructor to a new
    Menu(TaxiCenter taxiCenter, Matrix grid, Clock clock);
    
    //run the funcs with input
    void run();
    
    //create obstacles from the input arguments
    void getObstacles();
    
//    //insert a new driver from the input arguments
//    void insertNewDriver();

    void advance();

    //pass date from server<->client
    void updatesFromClient(TaxiCenter taxiCenter);

    //update clock time
    void updateTimeClock();

    //insert a new driver from the input arguments
    void expectingDriver(TaxiCenter taxiCenter);
    
    //insert a new trip from the input arguments
    void insertTrip();
    
    //insert a new taxi from the input arguments
    void insertTaxi();
    
    //get the driver location from the input arguments
    void getDriverLocation();
    
    // move all the drivers to the next node in the trip
    void moveAllDriversToTheEnd();
    //serialize Clock To Client
    void serializeClockToClient(TaxiCenter taxiCenter) ;
};



#endif //EX2AP_MANUOPTIONS_H
