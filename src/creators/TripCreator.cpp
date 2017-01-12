//
// Created by noam on 16/12/16.
//

#include "TripCreator.h"
//help to create a trip
Trip* createTrip(ThreadPool* threadPool,Matrix *grid, int id, int xStart, int yStart,
                int xEnd, int yEnd, int numOfPass, double tariff, int timeOfStart){

    Point start = Point(xStart, yStart);
    Point end = Point(xEnd, yEnd);
    pthread_t t1 = (pthread_t) id;

    threadPool->add_trip_thread(t1,grid,start,end);

    return new Trip(id, 0, numOfPass, tariff, start, end, timeOfStart);
}