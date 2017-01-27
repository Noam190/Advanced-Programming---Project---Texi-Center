
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include "persons/Driver.h"
#include "creators/DriverCreator.h"
#include "Serialization.h"
#include "sockets/TcpClient.h"
#include "InputParser.h"

//insert a driver as a client
Driver* insertDriver() {
    InputParser inputParser = InputParser();
    string input;
    int id, age;
    char status;
    int experience, vehicleId;

    getline(cin, input);
    if(inputParser.checkInput(regex("\\d\\d*,\\d*,[M,D,W,S],\\d\\d*,\\d\\d*"), input)) {
        vector<string> temp;
        boost::split(temp, input, boost::is_any_of(","));
        id = stoi(temp[0]);
        age = stoi(temp[1]);
        status = temp[2][0];
        experience = stoi(temp[3]);
        vehicleId = stoi(temp[4]);
        Driver *d = createDriver(id, age, status, experience, vehicleId);
        return d;
    }

    exit(0);
}


int main(int argc, char *argv[]) {
    char buffer[120000];
    Ride *ride = NULL;
    Trip *t = NULL;
    long readBytes;



    //create a driver
    Driver* driver = insertDriver();


    TcpClient* tcpClient = new TcpClient(argv[1], stoi(argv[2]));
    tcpClient->Connect();

    std::cout<<"start serialize \n";
    //serialize driver
    std::string serial_str_driver = serialize<Driver>(driver);
    tcpClient->sendData(serial_str_driver);
    std::cout<<"finish serialize driver\n";

    readBytes = tcpClient->receiveData(buffer, sizeof(buffer));
    std::string vehicleStr(buffer, readBytes);
    //deserialize receive vehicle
    TaxiCab *taxiCab = deserialize<TaxiCab>(vehicleStr);
    driver->setTaxiCab(taxiCab);

    tcpClient->receiveData(buffer, sizeof(buffer));
    char option = buffer[0];
    std::string data;
    while (option != 'E') {
        switch (option) {
            case 'T':
                readBytes = tcpClient->receiveData(buffer, sizeof(buffer));
                data = string(buffer, readBytes);
                if (ride == NULL) {
                    t = deserialize<Trip>(data);
                    ride = new Ride(t, driver);
                }
                break;

            case 'G':
                if (ride != NULL) {
                    ride->moveOneStep();
                    if (ride->isDone()) {
                        delete ride;
                        ride = NULL;
                    }
                }
                break;

            default:
                break;
        }
        tcpClient->receiveData(buffer, sizeof(buffer));
        option = buffer[0];
    }

    delete tcpClient;
    delete driver;
    if(ride != NULL) {
        delete ride;
    }
    return 0;
}

