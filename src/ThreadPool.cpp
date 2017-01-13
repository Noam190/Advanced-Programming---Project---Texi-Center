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

void * ThreadPool::calculatePath (void *pathArgs) {
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
void ThreadPool::add_driver_thread(thread_t threadNew, TaxiCenter* taxiCenter, int connectNum) {
    DriverAgrs* args = new DriverAgrs(taxiCenter,connectNum);
    int ret = pthread_create(&threadNew, NULL, ThreadPool::addClient, args);
    if (ret != 0) {
        std::cout << " error in driver thread! exited from the thread pool" << std::endl;
    }
    m_threads.push_back(threadNew);
    std::cout << " finish add driver thread! exited from the thread pool" << std::endl;
}

void ThreadPool::createThread(thread_t threadNew, void* pFunc(void*), void* args) {
    int ret = pthread_create(&threadNew, NULL, pFunc, args);
    if (ret != 0) {
        std::cout << " error in create thread! exited from the thread pool" << std::endl;
    }
    m_threads.push_back(threadNew);
    std::cout << " finish create thread! exited from the thread pool" << std::endl;
}

void * ThreadPool::addClient(void *args){
    DriverAgrs* argsD =(DriverAgrs*) args;
    bool stop = argsD->stop;
    TcpServer* tcp = argsD->tcp;
    TaxiCenter* taxiCenter = argsD->taxiCenter;
    int connectNum = tcp->connectClient();

    unsigned long readBytes;
    char buffer[1024];
    std::fill_n(buffer, 1024, 0);
    readBytes = tcp->receiveData(buffer, sizeof(buffer), connectNum);

    // deserialize driver
    string serial_str_driver(buffer, readBytes);
    Driver *d = deserialize<Driver>(serial_str_driver);

    TaxiCab* taxiCab = taxiCenter->getTaxi(d->getVehicleId());

    //serialize taxi
    string serial_str_taxi = serialize(taxiCab);
    //sent back the taxi
    tcp->sendData(serial_str_taxi, connectNum);

    //add driver to the taxi-center.
    taxiCenter->addDriver(d);

    Trip* trip;
    while (!stop) {
        trip = taxiCenter->getTripById(d->getId());
        if (trip != NULL ) {
            tcp->sendData("T", connectNum);
            string serial_str_trip = serialize(trip);
            tcp->sendData(serial_str_trip, connectNum);
        }
    }
}





//int ThreadPool::add_task(Task* task)
//{
//    m_tasks.push_back(task);
//}

