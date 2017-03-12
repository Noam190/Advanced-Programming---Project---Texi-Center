
#include "core/Matrix.h"
#include "TaxiCenter.h"
#include "Menu.h"
#include <iostream>
#include <boost/algorithm/string.hpp>

#define ELPP_THREAD_SAFE
/*#include "logging/easylogging++.h"*/
#include "Job.h"
#include "ThreadPool.h"
#include "GridAndObstecalesArgs.h"

/*
INITIALIZE_EASYLOGGINGPP
*/
vector<NodeMatrix*>* deleteObstacles(vector<NodeMatrix *> *obstacles) {
    for (int i = 0; i < obstacles->size(); ++i) {
        delete (*obstacles)[i];
    }
    delete obstacles;
    return NULL;
}

vector<NodeMatrix*>* getObstacles(std::string obsecalesInput,int numObstacles,
                              InputParser *inputParser, long width, long height) {
    vector<NodeMatrix *> *obstacles = new vector<NodeMatrix *>();
    ;
    string input;
   // long numOfObstacles;
    long x;
    long y;
//    //num of obstacles
//    getline(cin, input);
//    trim(input);
//    if (!inputParser->checkInput(regex("\\d+"), input)) {
//        return NULL;
//    }
   // numOfObstacles = stoi(input);
    //numOfObstacles =atoi(input.c_str());
    vector<string> tempStringParse;
    std::string str(obsecalesInput);
    boost::split(tempStringParse, str, boost::is_any_of("-"));
    int counterStringParse=0;

    while (numObstacles > 0) {
        input=tempStringParse[counterStringParse];
        if (inputParser->checkInput(regex("\\d+,\\d+"), input)) {
            vector<string> temp;
            boost::split(temp, input, boost::is_any_of(","));
            //x = stol(temp[0]);
            x =atol(temp[0].c_str());
           // y = stoll(temp[1]);
            y =atol(temp[1].c_str());
            if (x >= 0 && x < width && y >= 0 && x < height) {
                NodeMatrix *n = new NodeMatrix(x, y);
                obstacles->push_back(n);
                numObstacles--;
                counterStringParse++;
            } else {
                return deleteObstacles(obstacles);
            }

        } else {
            return deleteObstacles(obstacles);
        }

    }
    return obstacles;
}


//create obstacles from the input arguments
vector<NodeMatrix*>* getGridArgs(char* inputArgs,InputParser* inputParser, long* width, long* height) {
    //gridWidth gridHeight*numObstecal*
    vector<string> tempParse;
    std::string str(inputArgs);
    boost::split(tempParse, str, boost::is_any_of("*"));

    string inputGrid=tempParse[0];
   // trim(inputGrid);
    if (inputParser->checkInput(regex("\\d+ \\d+"), inputGrid)) {
        vector<string> temp;
        boost::split(temp, inputGrid, boost::is_any_of(" "));
       // *width = stol(temp[0]);
        *width =atol(temp[0].c_str());
       // *height = stol(temp[1]);
        *height =atol(temp[1].c_str());
        if (*height > 0 && *width > 0) {
            int numObstecale=atoi(tempParse[1]);
            std::string obsecalesInput= tempParse[2];
            return getObstacles(obsecalesInput,numObstecale,inputParser, *width, *height);
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
}

void expectingGui(TaxiCenter* taxiCenter) {

    taxiCenter->addGuiClient();

}
int main(int argc, char *argv[]) {
/*    START_EASYLOGGINGPP(argc, argv);
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
*/
    int portNum = atoi(argv[1]);
    TcpServer* tcp = new TcpServer(portNum);
    tcp->start();

    ThreadPool* tripThreadPool= new ThreadPool(5);

    Clock* clock = new Clock();
    TaxiCenter* taxiCenter = new TaxiCenter(clock, tcp);
    InputParser* inputParser = new InputParser();

    //adding Gui as a client***********************************************************
    expectingGui(taxiCenter);
    GridAndObstecalesArgs* gridAndObstecalesArgs;

    long readBytes;
    char buffer[120000];

    readBytes = tcp->receiveData(buffer, sizeof(buffer),taxiCenter->getGuiNum());
    std::string gridAndObstecalesArgsStr(buffer, readBytes);
    //deserialize receive gui
    gridAndObstecalesArgs = deserialize<GridAndObstecalesArgs>(gridAndObstecalesArgsStr);




    long width = -1  , height = -1;
    vector<NodeMatrix *> *obstacles = NULL;
    do {
        obstacles = getGridArgs(gridAndObstecalesArgs->getString(),inputParser, &width, &height);
        if (obstacles == NULL) {
            std::cout << "-1" << std::endl;
        }
    } while (obstacles == NULL);
    Matrix *grid = new Matrix((unsigned) width, (unsigned) height);
    for (int i = 0; i < obstacles->size(); ++i) {
        Node* n = (*obstacles)[i];
        grid->addObstacle(n);
        delete n;
    }
    delete obstacles;

    Menu menu = Menu(taxiCenter, grid, inputParser, tripThreadPool);
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