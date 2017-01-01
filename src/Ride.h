//
// Created by noam on 17/12/16.
//

#ifndef EX2AP_RIDE_H
#define EX2AP_RIDE_H


#include "Trip.h"
#include "persons/Driver.h"
#include "cabs/TaxiCab.h"
#include "Clock.h"

class Ride {
private:
    Point start;
    Point end;
    Trip* trip;
    Driver* driver;
    Clock *clock;
    int taxiType; //1 is standart,2 is luxury
public:

    //constructor
    Ride(Trip *trip, Driver *driver, Clock *clock, int taxiType);

    bool isDone();

    //move the ride one step
    void moveOneStep();

    //move the ride to the end
    void moveToTheEnd();

    //getters and setters
    Point getEndPoint();

    //getters and setters
    Point getStartPoint();

    //getters and setters
    Trip *getTrip();

    //getters and setters
    Driver* getDriver();

    //get type of taxi - 1  standart, 2 luxury
    int getTaxiType();
};


#endif //EX2AP_RIDE_H
