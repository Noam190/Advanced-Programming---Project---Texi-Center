//
// Created by noam on 16/12/16.
//

#ifndef EX2AP_TRIPCREATOR_H
#define EX2AP_TRIPCREATOR_H


#include "../Trip.h"
#include "../core/Matrix.h"
#include "../ThreadPool.h"

//help to create a trip
Trip* createTrip(ThreadPool threadPool,Matrix *grid, int id, int xStart, int yStart,
                int xEnd, int yEnd, int numOfPass, double tariff, int timeOfStart);


#endif //EX2AP_TRIPCREATOR_H
