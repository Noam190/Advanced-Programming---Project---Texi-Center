//
// Created by mei on 10/01/17.
//
#include <pthread.h>
#include <vector>
#include <thread_db.h>

#ifndef TAXI_CENTER_THREADPOOL_H
#define TAXI_CENTER_THREADPOOL_H


class ThreadPool {
private:
    int m_pool_size;
    std::vector<pthread_t> m_threads;
public:
    ThreadPool(int pool_size);
    ~ThreadPool();
    void  add_trip_thread(thread_t threadNew);
    void* start_thread(void* arg);
    void* calculatePath();

    // std::deque<Task*> m_tasks;
    //int add_task(Task* task);
    //  void* execute_thread();
};


#endif //TAXI_CENTER_THREADPOOL_H
