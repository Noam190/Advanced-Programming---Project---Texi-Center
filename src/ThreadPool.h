//
// Created by mei on 10/01/17.
//
#include <pthread.h>
#include <vector>
#include <thread_db.h>
#include "core/Matrix.h"
#include "persons/Driver.h"
#include "Serialization.h"
#include "TaxiCenter.h"

#ifndef TAXI_CENTER_THREADPOOL_H
#define TAXI_CENTER_THREADPOOL_H


class ThreadPool {
private:
    int m_pool_size;
    std::vector<pthread_t> m_threads;
public:
//    ThreadPool(int pool_size);
    ~ThreadPool();
    void  ThreadPool::addThread(thread_t threadNew, void * pFunc(void*), void* args);
    static void *  addDriver(void* taxiCenter);
    static void * calculatePath(void *pathArgs);
//    void  add_trip_thread(thread_t threadNew,Matrix *grid, Point start,  Point end);
//    void add_driver_thread(thread_t threadNew, TaxiCenter* taxiCenter) ;


    // std::deque<Task*> m_tasks;
    //int add_task(Task* task);
    //  void* execute_thread();
};

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
#endif //TAXI_CENTER_THREADPOOL_H
