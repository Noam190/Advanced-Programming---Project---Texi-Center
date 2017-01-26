//
// Created by noam on 16/12/16.
//

#include "TripCreator.h"
//help to create a trip
tripAndThread createTrip(Matrix *grid, int id, long xStart,
         long yStart, long xEnd, long yEnd, int numOfPass,
         double tariff, int timeOfStart, ThreadPool* tripThreadPool){

    Point* start = new Point(xStart, yStart);
    Point* end = new Point(xEnd, yEnd);

    Trip* trip = new Trip(id, 0, numOfPass, tariff, start, end, timeOfStart);

    PathAgrs* args = new PathAgrs(grid, *start, *end, trip);

    Job* job=new Job(calculatePath, args);
    tripThreadPool->addJob(job);

    //    pthread_t ptId = createThread(calculatePath, args);
    tripAndThread t;
     t.trip = new Trip(id, 0, numOfPass, tariff, start, end, timeOfStart);
    t.ptId = -1;

    return t;
}

 void * calculatePath (void *pathArgs) {
    unsigned long length;
    PathAgrs* args = (PathAgrs*) pathArgs;

    args->grid->initDistanceForAll(-1);

    Node* startNode = args->grid->getNode(args->start->x(), args->start->y());
    Node* endNode = args->grid->getNode(args->end->x(), args->end->y());

    // Mark all the vertices as not visit
    std::list<Node *> pathNodes = BFS(startNode, endNode);
    std::vector<Point*>* pathPoints = new vector<Point*>();
    length = pathNodes.size();
    for (int i = 0; i < length; ++i) {
        Node *n = pathNodes.front();
        Point p = args->grid->getPoint(n);
        pathPoints->push_back(new Point(p.x(), p.y()));
        pathNodes.pop_front();
    }
    delete args;
    return  pathPoints;
}

