//
//  Created by noam on 16/12/16.
//

#include "Menu.h"
#include "creators/ThreadCreator.h"
#include "InputParser.h"
#include <pthread.h>

//  run the input to the program
void Menu::run() {
    string input;
    int option = 0;

    //getObstacles();
    //cin.ignore();
     do {
        //cin >> option;
        getline(cin, input);
        if(this->inputParser->checkInput("manu options", input)) {
            option = stoi(input);
            runOption(option);
        } else {
            std::cout << "-1" << endl;
        }
    } while (option != 7);
}

void Menu::runOption(int option) {
    switch (option) {
        case 1: //insert drivers
            expectingDriver();
            break;
        case 2: //insert trip
            insertTrip();
            break;
        case 3: //insert taxi
            insertTaxi();
            break;
        case 4: //get the drivers location
            getDriverLocation();
            break;
        case 6: //move all the drivers to end
            moveAllDriversToTheEnd();
            break;
        case 9:// move the drivers to the next point.
            this->taxiCenter->moveAllRidesOneStep();
            break;
        default:
            return;
    }
}

//insert a new taxi from the input arguments
void Menu::insertTaxi() {
    string input;
    int id, taxiType;
    char manufacturer, color;

    getline(cin, input);
    if(this->inputParser->checkInput("taxi cab", input)) {
        vector<string> temp;
        boost::split(temp, input, boost::is_any_of(","));
        id = stoi(temp[0]);
        taxiType = stoi(temp[1]);
        manufacturer = temp[2][0];
        color = temp[3][0];
        //create the taxi
        TaxiCab *cab = createTaxi(id, taxiType, manufacturer, color);
        this->taxiCenter->addTaxiCab(cab);
        return;
    }

    std::cout << "-1" << endl;
}

//expecting a new driver from the client
void Menu::expectingDriver() {
    int numOfDrivers;
    std::cin >> numOfDrivers;

    for (int i = 0; i < numOfDrivers; ++i) {
        taxiCenter->addClient();
    }
}

//insert a new trip from the input arguments
void Menu::insertTrip() {
    string input;
    int id;
    long xStart, yStart, xEnd, yEnd;
    int numOfPass;
    double tariff;
    int timeOfStart;

    getline(cin, input);
    if(this->inputParser->checkInput("trip", input)) {
        vector<string> temp;
        boost::split(temp, input, boost::is_any_of(","));
        id = stoi(temp[0]);
        xStart = stol(temp[1]);
        yStart = stol(temp[2]);
        xEnd = stol(temp[3]);
        yEnd = stol(temp[4]);
        timeOfStart = stoi(temp[7]);
        if (checkPoint(xStart, yEnd) && checkPoint(xEnd, yEnd) && timeOfStart > 0) {
            numOfPass = stoi(temp[5]);
            tariff = stoi(temp[6]);

            //create the trip
            Trip* newTrip = createTrip(grid, id, xStart, yStart, xEnd, yEnd,
                               numOfPass, tariff, timeOfStart,tripThreadPool);

            taxiCenter->insertTrip(newTrip);
            return;
        }
    }
    std::cout << "-1" << endl;
}

////create obstacles from the input arguments
//void Menu::getObstacles() {
//    string input;
//    int numOfObstacles;
//    long x;
//    long y;
//    //num of obstacles
//    getline(cin, input);
//    if(this->inputParser->checkInput(regex("\\d*"), input)) {
//        numOfObstacles = stoi(input);
//        if (numOfObstacles >= 0) {
//            while (numOfObstacles > 0) {
//                input.clear();
//                getline(cin, input);
//                if(this->inputParser->checkInput(regex("\\d*,\\d*"), input)) {
//                    vector<string> temp;
//                    boost::split(temp, input, boost::is_any_of(","));
//                    x = stol(temp[0]);
//                    y = stol(temp[1]);
//                    if (checkPoint(x, y)) {
//                        Node *n = new NodeMatrix(x, y);
//                        this->grid->addObstacle(n);
//                        delete n;
//                        numOfObstacles--;
//                    }
//                }
//            }
//        }
//    }
//}

//get the driver location from the input arguments
void Menu::getDriverLocation() {
    int idDriver;
    std::cin >> idDriver;
    std::cout << this->taxiCenter->getDriverLocation(idDriver);
}

// move all the drivers to the next node in the trip
void Menu::moveAllDriversToTheEnd() {
    this->taxiCenter->moveAllRidesToTheEnd();
}

//constructor to a new
Menu::Menu(TaxiCenter *taxiCenter, Matrix *grid, InputParser *inputParser, ThreadPool* tripThreadPool)
        : grid(grid), taxiCenter(taxiCenter), inputParser(inputParser), tripThreadPool(tripThreadPool){
    inputParser->addRegex("taxi cab", "\\d*,[12],[FHTS],[RBGWP]");
    inputParser->addRegex("trip", "\\d*,\\d*,\\d*,\\d*,\\d*,\\d*,\\d*,\\d*");
    inputParser->addRegex("manu options", "[1234679]");

}

bool Menu::checkPoint(long x, long y){
    return x >= 0 && x < this->grid->getWidth() && y >= 0 && x < this->grid->getHeight();
}


