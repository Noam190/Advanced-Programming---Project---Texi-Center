//
// Created by noam on 16/12/16.
//

#ifndef EX2AP_TRIPCREATOR_H
#define EX2AP_TRIPCREATOR_H


#include "../Trip.h"
#include "../core/Matrix.h"
#include "ThreadCreator.h"

struct tripAndThread {
    Trip* trip;
    pthread_t ptId;
};

//help to create a trip
tripAndThread createTrip(Matrix *grid, int id, long xStart, long yStart, long xEnd, long yEnd, int numOfPass,
                         double tariff, int timeOfStart);

void * calculatePath(void *pathArgs);



class PathAgrs{
public:
    Matrix* grid;
    Point* start;
    Point* end;
    PathAgrs(Matrix *grid, Point start,  Point end) : grid(grid) {
        this->start = new Point(start.x(), start.y());
        this->end = new Point(end.x(), end.y());
    }

    ~PathAgrs(){
        delete start;
        delete end;
    }
};

#endif //EX2AP_TRIPCREATOR_H
