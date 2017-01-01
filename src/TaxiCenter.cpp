//
// Created by mei on 03/12/16.
//

#include <iostream>
#include "TaxiCenter.h"

//send a taxi
TaxiCab TaxiCenter::sendTaxi() {
    return TaxiCab(HONDA, RED, 0,0,0, 0);
}

//answer call
void TaxiCenter::answerCall() {
    return;
}

//add a driver to the center
void TaxiCenter::addDriver(Driver d) {
    this->freeDrivers.push_back(d);
}

//add a taxi cab to the center
void TaxiCenter::addTaxiCab(TaxiCab taxi) {
    this->freeCabs.push_back(taxi);
}

//add a trip to the center
int TaxiCenter::insertTrip(Trip t) {
    int index = 0;
    for (vector<Driver>::iterator it = freeDrivers.begin(); it != freeDrivers.end(); ++it, ++index) {
        if (it->getCurrentLocation() == t.getStartPoint()) {
            busyDrivers.push_back(freeDrivers[index]);
            freeDrivers.erase(it);
            busyTrips.push_back(t);
            Ride r = Ride(&busyTrips.back(), &busyDrivers.back(), &clock);
            rides.push_back(r);
            return 1;
        }
    }
    this->freeTrips.push_back(t);
    return 0;
}

//remove a driver to the center
void TaxiCenter::removeDriver(int id) {
    for (vector<Driver>::iterator it = freeDrivers.begin(); it != freeDrivers.end(); ++it) {
        if(it->getId() == id) {
            it = this->freeDrivers.erase(it);
        }
    }
    for (vector<Driver>::iterator it = busyDrivers.begin(); it != busyDrivers.end(); ++it) {
        if(it->getId() == id) {
            it = this->busyDrivers.erase(it);
        }
    }
}

//remove a trip to the center
void TaxiCenter::removeTrip(int id) {
    for (vector<Trip>::iterator it = freeTrips.begin(); it != freeTrips.end(); ++it) {
        if(it->getId() == id) {
            it = this->freeTrips.erase(it);
        }
    }
    for (vector<Trip>::iterator it = busyTrips.begin(); it != busyTrips.end(); ++it) {
        if(it->getId() == id) {
            it = this->busyTrips.erase(it);
        }
    }
}

//get the driver location
Point TaxiCenter::getDriverLocation(int id) {
    for (vector<Driver>::iterator it = freeDrivers.begin(); it != freeDrivers.end(); ++it) {
        if(it->getId() == id) {
            return it->getCurrentLocation();
        }
    }
    for (vector<Driver>::iterator it = busyDrivers.begin(); it != busyDrivers.end(); ++it) {
        if(it->getId() == id) {
            return it->getCurrentLocation();
        }
    }
    return Point(-8,-8);
}


//move all the rides to the end point
void TaxiCenter::moveAllRidesToTheEnd() {
    while(rides.size() > 0) {
        rides.front().moveToTheEnd();
        busyTrips.erase(busyTrips.begin());
        rides.erase(rides.begin());

        freeDrivers.push_back(busyDrivers[0]);
        busyDrivers.erase(busyDrivers.begin());
    }
}

//get a taxi from the list by vehicle id
TaxiCab TaxiCenter::getTaxi(int idVehicle) {
    int index = 0;
    for (vector<TaxiCab>::iterator it = freeCabs.begin(); it != freeCabs.end(); ++it ,++index) {
        if(it->getId() == idVehicle) {
            return freeCabs[index];
        }
    }
}

void TaxiCenter::addTaxiToDriver(Driver *driver) {
    int index = 0;
    for (vector<TaxiCab>::iterator it = freeCabs.begin(); it != freeCabs.end(); ++it, ++index) {
        if (it->getId() == driver->getId()) {
            driver->setTaxiCab(&freeCabs[index]);
        }
    }
}

Trip *TaxiCenter::insertNewDriver(Driver driver) {
    int index = 0;
    Point startPoint = driver.getCurrentLocation();
    addTaxiToDriver(&driver);
    for (vector<Trip>::iterator it = freeTrips.begin(); it != freeTrips.end(); ++it, ++index) {
        if (it->getStartPoint() == startPoint) {
            busyDrivers.push_back(driver);
            busyTrips.push_back(freeTrips[index]);
            freeTrips.erase(it);
            Ride r = Ride(&busyTrips.back(), &busyDrivers.back(), &clock);
            rides.push_back(r);
            return &busyTrips.back();
        }
    }
    freeDrivers.push_back(driver);
    return NULL;
}

TaxiCenter::TaxiCenter(Clock clock) : clock(clock) {}


//move all the rides one step forward
void TaxiCenter::moveAllRidesOneStep() {
    for (int i = 0; i < rides.size(); ++i) {
        rides[i].moveOneStep();
        if (rides[i].isDone()) {
            busyTrips.erase(busyTrips.begin() + i);
            freeDrivers.push_back(busyDrivers[i]);
            busyDrivers.erase(busyDrivers.begin() + i);
            rides.erase(rides.begin() + i);
            --i;
        }
    }
}


//create a new ride
Trip * TaxiCenter::createRides() {
    Trip *trip = NULL;
    for (int i = 0; i < freeDrivers.size(); ++i) {
        for (int j = 0; j < freeTrips.size(); ++j) {
            if (freeDrivers[i].getCurrentLocation() == freeTrips[j].getStartPoint()) {
                busyDrivers.push_back(freeDrivers[i]);
                freeDrivers.erase(freeDrivers.begin() + i);
                busyTrips.push_back(freeTrips[j]);
                freeTrips.erase(freeTrips.begin() + j);
                Ride r = Ride(&busyTrips.back(), &busyDrivers.back(), &clock);
                rides.push_back(r);
                --i;
                --j;

                trip = &busyTrips.back();
            }
        }
    }
    return trip;
}

//    int index = 0;
//    for (vector<Ride>::iterator it = rides.begin(); it != rides.end(); ++it, ++index) {
//        it->moveOneStep();
//        if (it->isDone()) {
//            busyTrips.erase(busyTrips.begin() + index);
//            freeDrivers.push_back(busyDrivers[index]);
//            busyDrivers.erase(busyDrivers.begin() + index);
//            it = rides.erase(it);
//        }
//    }