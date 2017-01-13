//
// Created by mei on 03/12/16.
//

#ifndef EX2AP_TAXICENTER_H
#define EX2AP_TAXICENTER_H


#include <vector>
#include "persons/Driver.h"
#include "cabs/TaxiCab.h"
#include "Trip.h"
#include "Ride.h"
#include "sockets/TcpServer.h"

class TaxiCenter {
private:
    Clock *clock;
    static std::vector<Ride*> rides;
    std::vector<Driver*> freeDrivers;
    std::vector<TaxiCab*> freeCabs;
    std::vector<Trip*> freeTrips;
    std::vector<pair<int,int>> numToConnectServer;
public:
    //constructor
    TaxiCenter(Clock *clock);

    ~TaxiCenter();

    //answer call
    void answerCall();

    //send a taxi
    TaxiCab sendTaxi();

    //add a driver to the center
    void addDriver(Driver* d);

    //add a taxi cab to the center
    void addTaxiCab(TaxiCab* taxi);

    //get a taxi from the list by vehicle id
    TaxiCab * getTaxi(int idVehicle);

    //add a trip to the center
    void insertTrip(Trip* t);

    //remove a driver to the center
    void removeDriver(int id);

    //remove a trip to the center
    void removeTrip(int id);

    void removeTaxi(int idVehicle);

    //create a new ride
    Trip* createRides();

    //move all the rides one step forward
    void moveAllRidesOneStep();

    //move all the rides to the end point
    void moveAllRidesToTheEnd();

    //get the driver location
    Point getDriverLocation(int id);

    void addnumToConnectServer(int num, int driverId);

    int findNumToClient(int driverId);

    void sendMessageToAllClients(TcpServer *tcp,string data) ;
};

#endif //EX2AP_TAXICENTER_H
