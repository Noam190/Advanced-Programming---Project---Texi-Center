//
// Created by mei on 10/01/17.
//

#include <iostream>
#include "ThreadCreator.h"

void createThread(thread_t threadNew, void* pFunc(void*), void* args) {
    int ret = pthread_create(&threadNew, NULL, pFunc, args);
    if (ret != 0) {
        std::cout << " error in create thread! exited from the thread pool" << std::endl;
    }
    std::cout << " finish create thread! exited from the thread pool" << std::endl;
}
