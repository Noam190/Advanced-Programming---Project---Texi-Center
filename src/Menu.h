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
#include "core/Grid.h"
#include "Clock.h"
#include "sockets/Udp.h"
#include "core/Matrix.h"
#include "Serialization.h"
#include "ThreadPool.h"
#include "sockets/TcpServer.h"

class Menu {
private:
    Matrix *grid;
    TaxiCenter *taxiCenter;
    Clock *clock;
    TcpServer *tcp;
    ThreadPool *threadPool;
//    struct ClientData {
//        int clientID;
//        Menu* menu;
//    };

public:

    //constructor to a new
    Menu(ThreadPool *threadPool,
         TaxiCenter *taxiCenter, Matrix *grid, Clock *clock, TcpServer *tcp);

    //run the funcs with input
    void run();

    //create obstacles from the input arguments
    void getObstacles();

    void advance();

    //pass date from server<->client
    void updatesFromClient();

    //insert a new driver from the input arguments
    void expectingDriver();

    //insert a new trip from the input arguments
    void insertTrip();

    //insert a new taxi from the input arguments
    void insertTaxi();

    //get the driver location from the input arguments
    void getDriverLocation();

    // move all the drivers to the next node in the trip
    void moveAllDriversToTheEnd();

//    void clientFunction(int clientID);
//
//    static void* Menu::threadFunction(void* element);
};



#endif //EX2AP_MANUOPTIONS_H
