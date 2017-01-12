//
// Created by mei on 10/01/17.
//

#include <iostream>
#include "ThreadPool.h"
#include "core/Matrix.h"


ThreadPool::ThreadPool(int pool_size) : m_pool_size(pool_size)
{
    for (int i = 0; i < m_pool_size; i++) {
        pthread_t tid;
//        int ret = pthread_create(&tid, NULL, start_thread, NULL);
//        if (ret != 0) { /* error handling */ }
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
void  ThreadPool::add_trip_thread(thread_t threadNew,Matrix *grid, Point start,  Point end){
    PathAgrs* args = new PathAgrs(grid, start, end);
    int ret = pthread_create(&threadNew, NULL, ThreadPool::calculatePath, args);
    if (ret != 0) {
        std::cout <<  " error in trip thread! exited from the thread pool" << std::endl;
    }
    m_threads.push_back(threadNew);
    std::cout <<  " finish add trip thread! exited from the thread pool" << std::endl;

}

void * ThreadPool::calculatePath ( void *pathArgs) {
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
void* ThreadPool::start_thread(void* arg)
{

}

//int ThreadPool::add_task(Task* task)
//{
//    m_tasks.push_back(task);
//}

