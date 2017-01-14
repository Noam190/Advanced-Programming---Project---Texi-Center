//
// Created by mei on 10/01/17.
//

#include <iostream>
#include "ThreadPool.h"
#include "core/Matrix.h"



//ThreadPool::ThreadPool(int pool_size) : m_pool_size(pool_size)
//{
//    for (int i = 0; i < m_pool_size; i++) {
//        pthread_t tid;
////        int ret = pthread_create(&tid, NULL, start_thread, NULL);
////        if (ret != 0) { /* error handling */ }
//        m_threads.push_back(tid);
//    }
//    std::cout << m_pool_size << " threads created by the thread pool" << std::endl;
//}
//ThreadPool::~ThreadPool()
//{
//    for (int i = 0; i < m_pool_size; i++) {
//        pthread_join(m_threads[i],NULL);
//    }
//    std::cout << m_pool_size << " threads exited from the thread pool" << std::endl;
//}

void createThread(thread_t threadNew, void* pFunc(void*), void* args) {
    int ret = pthread_create(&threadNew, NULL, pFunc, args);
    if (ret != 0) {
        std::cout << " error in create thread! exited from the thread pool" << std::endl;
    }
    //m_threads.push_back(threadNew);
    std::cout << " finish create thread! exited from the thread pool" << std::endl;
}
