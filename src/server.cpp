
#include "core/Matrix.h"
#include "TaxiCenter.h"
#include "Menu.h"
#include <iostream>
#include <boost/algorithm/string.hpp>

#define ELPP_THREAD_SAFE
#include "logging/easylogging++.h"
#include "Job.h"
#include "ThreadPool.h"

INITIALIZE_EASYLOGGINGPP


int main(int argc, char *argv[]) {
    START_EASYLOGGINGPP(argc, argv);
    el::Configurations defaultConf;
    defaultConf.setToDefault();
    // Values are always std::string
    defaultConf.set(el::Level::Info,
                    el::ConfigurationType::Format, "%datetime %level %msg");
    // default logger uses default configurations
    el::Loggers::reconfigureLogger("default", defaultConf);
    LOG(INFO) << "SERVER LOG: \n";
    // To set GLOBAL configurations you may use
    defaultConf.setGlobally(
            el::ConfigurationType::Format, "%level %msg");
    el::Loggers::reconfigureLogger("default", defaultConf);


    int portNum = atoi(argv[1]);
    TcpServer* tcp = new TcpServer(portNum);
    tcp->start();

    ThreadPool* tripThreadPool= new ThreadPool(3);
    Job *arr;


    Clock* clock = new Clock();
    TaxiCenter* taxiCenter = new TaxiCenter(clock, tcp);
    InputParser* inputParser = new InputParser();
    inputParser->addRegex("grid", "\\d* \\d*");

    //grid initialize grid and add obstacles if there are any.
    //std::cin >> width >> height;
    string inputGrid;
    getline(cin, inputGrid);
    if (inputParser->checkInput("grid", inputGrid)) {
        vector<string> temp;
        boost::split(temp, inputGrid, boost::is_any_of(" "));
        long width = stol(temp[0]);
        long height = stol(temp[1]);
        if (height > 0 && width > 0) {

            Matrix *grid = new Matrix((unsigned) width, (unsigned) height);
            Menu menu = Menu(taxiCenter, grid, inputParser, tripThreadPool,arr, 0);
            //run all the other inputs
            menu.run();

            delete grid;
            delete clock;
            delete tripThreadPool;
            delete taxiCenter;
            delete tcp;
            delete inputParser;
            return 0;
        }
    }
}

//Node* n  = grid->getNode(4, 34);
//std::list<Node*> l = n->getNeighbors();
//while (!l.empty()){
//std::cout << *(l.front()) << std::endl;
//l.pop_front();
//}

//    //thread
//    pthread_t t1;
//    int * data = new int;
//    *data = 2;
//    int status = pthread_create(&t1, NULL, printTry, (void*) data);
//    if (status)
//    {
//        std::cout<<" error";
//    }

//void *printTry( void *ptr )
//{
//    int message = *((int*) ptr);
//    cout << "test seoond thread" << message << "\n";
//}