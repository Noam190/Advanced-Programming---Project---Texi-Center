//
// Created by noam on 17/12/16.
//

#ifndef EX2AP_RIDE_H
#define EX2AP_RIDE_H


#include "Trip.h"
#include "persons/Driver.h"
#include "cabs/TaxiCab.h"

class Ride {
private:
    Point start;
    Point end;
    Trip* trip;
    Driver* driver;
public:
    //constructor
    Ride(Trip* trip, Driver* driver);

    //move the ride one step
    void moveOneStep();

    //move the ride to the end
    void moveToTheEnd();

    //getters and setters
    Point getEndPoint();

    //getters and setters
    Point getStartPoint();

    //getters and setters
    Trip* getTrip(int idDriver);

    //getters and setters
    Driver* getDriver();
};


#endif //EX2AP_RIDE_H
