//
// Created by noam on 16/12/16.
//

#ifndef EX2AP_TRIPCREATOR_H
#define EX2AP_TRIPCREATOR_H


#include "../Trip.h"
#include "../core/Matrix.h"
#include "ThreadCreator.h"
#include "../TaxiCenter.h"
#include "../Job.h"
#include "../ThreadPool.h"

struct tripAndThread {
    Trip* trip;
    int ptId;
};

//help to create a trip
Trip * createTrip(Matrix *grid, int id, long xStart, long yStart, long xEnd,
                  long yEnd, int numOfPass, double tariff, int timeOfStart, ThreadPool *tripThreadPool);

void * calculatePath(void *pathArgs);



class PathAgrs{
public:
    Matrix* grid;
    Point* start;
    Point* end;
    Trip* trip;

    PathAgrs(Matrix *grid, Point start,  Point end, Trip* trip) : grid(grid), trip(trip) {
        this->start = new Point(start.x(), start.y());
        this->end = new Point(end.x(), end.y());
    }

    ~PathAgrs(){
        delete start;
        delete end;
    }
};

#endif //EX2AP_TRIPCREATOR_H
