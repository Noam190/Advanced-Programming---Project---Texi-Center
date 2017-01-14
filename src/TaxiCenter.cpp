//
// Created by mei on 03/12/16.
//

#include <iostream>
#include <boost/tuple/tuple.hpp>
#include "TaxiCenter.h"
#include "sockets/TcpServer.h"
#include "Serialization.h"
#include "ThreadPool.h"

//send a taxi
TaxiCab TaxiCenter::sendTaxi() {
    return TaxiCab(HONDA, RED, 0,0,0, 0);
}

//answer call
void TaxiCenter::answerCall() {
    return;
}

//add a driver to the center
void TaxiCenter::addDriver(Driver* d) {
    TaxiCab* taxi = this->getTaxi(d->getId());
    if (taxi != NULL) {
        d->setTaxiCab(taxi);
        this->removeTaxi(taxi->getId());
    }

    this->freeDrivers.push_back(d);
}

//add a taxi cab to the center
void TaxiCenter::addTaxiCab(TaxiCab* taxi) {
    this->freeCabs.push_back(taxi);
}

//add a trip to the center
void TaxiCenter::insertTrip(Trip* t) {
    this->freeTrips.push_back(t);
}

//remove a driver to the center
void TaxiCenter::removeDriver(int id) {
    for (vector<Driver*>::iterator it = freeDrivers.begin(); it != freeDrivers.end(); ++it) {
        if((*it)->getId() == id) {
            it = this->freeDrivers.erase(it);
        }
    }
}

//remove a trip to the center
void TaxiCenter::removeTrip(int id) {
    for (vector<Trip*>::iterator it = freeTrips.begin(); it != freeTrips.end(); ++it) {
        if((*it)->getId() == id) {
            it = this->freeTrips.erase(it);
        }
    }
}

//get a taxi from the list by vehicle id
void TaxiCenter::removeTaxi(int idVehicle) {
    for (vector<TaxiCab*>::iterator it = freeCabs.begin(); freeCabs.size() != 0 && it != freeCabs.end(); ++it) {
        if((*it)->getId() == idVehicle) {
            freeCabs.erase(it);
        }
    }
}

//get the driver location
Point TaxiCenter::getDriverLocation(int id) {
    for (vector<Driver*>::iterator it = freeDrivers.begin(); it != freeDrivers.end(); ++it) {
        if((*it)->getId() == id) {
            return (*it)->getCurrentLocation();
        }
    }
    for (vector<Ride*>::iterator it = rides.begin(); it != rides.end(); ++it) {
        if ((*it)->getDriver()->getId() == id) {
            return (*it)->getDriverLocation();
        }
    }
    return Point(-8,-8);
}

//move all the rides to the end point
void TaxiCenter::moveAllRidesToTheEnd() {
    while(rides.size() > 0) {
        rides.front()->moveToTheEnd();
        freeDrivers.push_back(rides.front()->getDriver());
        delete  rides[0];
        rides.erase(rides.begin());
    }
}

//get a taxi from the list by vehicle id
TaxiCab * TaxiCenter::getTaxi(int idVehicle) {
    int index = 0;
    for (vector<TaxiCab*>::iterator it = freeCabs.begin(); it != freeCabs.end(); ++it ,++index) {
        if((*it)->getId() == idVehicle) {
            return freeCabs[index];
        }
    }
    return NULL;
}

TaxiCenter::TaxiCenter(Clock *clock, TcpServer* tcp) : clock(clock), tcp(tcp) {}


//move all the rides one step forward
void TaxiCenter::moveAllRidesOneStep() {
    this->clock->addToCurrentTime(1);
    this->tcp->sendDataToAllClients("G");
    for (int i = 0; i < rides.size(); ++i) {
        rides[i]->moveOneStep();
        if (rides[i]->isDone()) {
            freeDrivers.push_back(rides[i]->getDriver());
            delete  rides[i];
            rides.erase(rides.begin() + i);
            --i;
        }
    }
    this->createRides();
}


//create a new ride
void TaxiCenter::createRides() {
    void *status;

    for (int j = 0; j < freeTrips.size(); ++j) {
        if (freeTrips[j]->getTimeOfStart() == clock->getCurrentTime()){
            for (int i = 0; i < freeDrivers.size(); ++i) {
                if (freeDrivers[i]->getCurrentLocation() == freeTrips[j]->getStartPoint()) {
                    pthread_join(((pthread_t) freeTrips[j]->getId())* -1, &status);
                    std::vector<Point>* pathPoints = (vector<Point> *) status;
                    freeTrips[j]->setPath(pathPoints);

                    Ride* r = new Ride(freeTrips[j], freeDrivers[i]);
                    rides.push_back(r);

                    sendTrip(freeDrivers[i]->getId(), freeTrips[j]);

                    freeTrips.erase(freeTrips.begin() + j);
                    freeDrivers.erase(freeDrivers.begin() + i);

                    --i;//because we erased one free driver.
                    --j;//because we erased one free trip.
                }
            }
        }
    }
}

TaxiCenter::~TaxiCenter() {
    for (int i = 0; i < freeDrivers.size() ; ++i) {
        delete freeDrivers[i];
    }

    for (int i = 0; i < freeCabs.size() ; ++i) {
        delete freeCabs[i];
    }

    for (int i = 0; i < freeTrips.size() ; ++i) {
        delete freeTrips[i];
    }

    for (int j = 0; j < rides.size() ; ++j) {
        delete rides[j]->getDriver();
        delete rides[j];
    }
}

void TaxiCenter::clientFunction(int client_socket) {

    unsigned long readBytes;
    char buffer[8192];
    std::fill_n(buffer, 8192, 0);
    readBytes = this->tcp->receiveData(buffer, sizeof(buffer), client_socket);

    // deserialize driver
    string serial_str_driver(buffer, readBytes);
    Driver *d = deserialize<Driver>(serial_str_driver);

    TaxiCab* taxiCab = getTaxi(d->getVehicleId());

    //serialize taxi
    string serial_str_taxi = serialize(taxiCab);
    //sent back the taxi
    this->tcp->sendData(serial_str_taxi, client_socket);

    //add driver to the taxi-center.
    this->clients.insert(pair<int, int>(d->getId(), client_socket));
    this->addDriver(d);
}

void* TaxiCenter::threadFunction(void* element) {
    ClientData* data = (ClientData*) element;
    data->taxiCenter->clientFunction(data->client_socket);
    delete data;
    return NULL;
}

void TaxiCenter::addClient(int threadID) {
    pthread_t t1 = (pthread_t) threadID;
    ClientData* clientData = new ClientData;
    clientData->client_socket = tcp->connectClient();
    clientData->taxiCenter = this;
    createThread(t1, threadFunction, clientData);
}

void TaxiCenter::sendTrip(int driverId, Trip *trip) {
    int client_socket = this->clients[driverId];

    //serialize taxi
    string serial_str_trip = serialize(trip);
    //sent back the taxi
    this->tcp->sendData(serial_str_trip, client_socket);
}



//Trip* TaxiCenter::getTripById(int driverId) {
//    return this->drivers_trips.at(driverId);
//}

//void TaxiCenter::clientFunction(Driver *d, int client_socket) {
//    this->clients.insert(pair<int, int>(d->getId(), client_socket));
//    this->clientFunction(d);
//}
