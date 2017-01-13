//
// Created by noam on 16/12/16.
//

#include "TripCreator.h"
//help to create a trip
Trip* createTrip(ThreadPool* threadPool,Matrix *grid, int id, int xStart, int yStart,
                int xEnd, int yEnd, int numOfPass, double tariff, int timeOfStart){

    Point start = Point(xStart, yStart);
    Point end = Point(xEnd, yEnd);

    pthread_t t1 = ((pthread_t) id ) * -1;

    PathAgrs* args = new PathAgrs(grid, start, end);
    threadPool->createThread(t1,calculatePath,args);

    return new Trip(id, 0, numOfPass, tariff, start, end, timeOfStart);
}

void * calculatePath (void *pathArgs) {
    unsigned long length;
    PathAgrs* args = (PathAgrs*) pathArgs;

    args->grid->initDistanceForAll(-1);

    Node* startNode = args->grid->getNode(args->start->x(), args->start->y());
    Node* endNode = args->grid->getNode(args->end->x(), args->end->y());

    // Mark all the vertices as not visit
    std::list<Node *> pathNodes = BFS(startNode, endNode);
    std::vector<Point>* pathPoints = new vector<Point>();
    length = pathNodes.size();
    for (int i = 0; i < length; ++i) {
        Node *n = pathNodes.front();
        Point p = args->grid->getPoint(n);
        pathPoints->push_back(p);
        pathNodes.pop_front();
    }
    delete args;
    return  pathPoints;
}

