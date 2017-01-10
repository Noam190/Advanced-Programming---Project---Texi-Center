//
// Created by mei on 10/01/17.
//

#include <iostream>
#include "ThreadPool.h"


ThreadPool::ThreadPool(int pool_size) : m_pool_size(pool_size)
{
    for (int i = 0; i < m_pool_size; i++) {
        pthread_t tid;
        int ret = pthread_create(&tid, NULL, start_thread, (void*) this);
        if (ret != 0) { /* error handling */ }
        m_threads.push_back(tid);
    }
    std::cout << m_pool_size << " threads created by the thread pool" << std::endl;
}
ThreadPool::~ThreadPool()
{
    for (int i = 0; i < m_pool_size; i++) {
        pthread_join(m_threads[i],NULL);
    }
    std::cout << m_pool_size << " threads exited from the thread pool" << std::endl;
}
void  ThreadPool::add_trip_thread(thread_t threadNew){
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, calculatePath, (void*) this);
    if (ret != 0) { /* error handling */ }
    m_threads.push_back(tid);
    m_threads.push_back(threadNew);
}
void* ThreadPool::calculatePath(){

}
void* ThreadPool::start_thread(void* arg)
{

}

//int ThreadPool::add_task(Task* task)
//{
//    m_tasks.push_back(task);
//}