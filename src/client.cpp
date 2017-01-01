
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include "sockets/Udp.h"
#include "core_classes/Point.h"
#include "persons/Driver.h"
#include "creators/DriverCreator.h"
#include "Serialization.h"

Driver insertDriver() {
    std::cout << "input driver" << std::endl;
    char dummy;
    int id, age;
    char status;
    int experience, vehicleId;
    std::cin >> id >> dummy >> age >> dummy >> status >> dummy >> experience >> dummy >> vehicleId;
    Driver d = createDriver(id, age, status, experience, vehicleId);
    return d;

}


int main(int argc, char *argv[]) {
    char buffer[1024];
    Ride *ride = NULL;
    Trip *t = NULL;
    unsigned long readBytes;

//    string advance("advance\0", 8);
//    cout << advance.size() << std::endl;
//    string exit("exit\0", 5);

    std::cout << "Hello, from client" << std::endl;
    cout << argv[1] << endl;
    Udp udp(false, atoi(argv[1]));
    udp.initialize();

    //create a driver
    Driver driver = insertDriver();
    //serialize driver
    std::string serial_str_driver = serialize<Driver>(&driver);
    udp.sendData(serial_str_driver);


    //deserialize receive clock
    readBytes = udp.receiveData(buffer, sizeof(buffer));
    std::string clockStr(buffer, readBytes);
    Clock *c = deserialize<Clock>(clockStr);

    readBytes = udp.receiveData(buffer, sizeof(buffer));
    std::string vehicleStr(buffer, readBytes);
    //deserialize receive vehicle
    TaxiCab *taxiCab = deserialize<TaxiCab>(vehicleStr);
    driver.setTaxiCab(taxiCab);

    udp.receiveData(buffer, sizeof(buffer));
    char option = buffer[0];
    std::string data;
    while (option != 'E') {
        switch (option) {
            case 'T':
                readBytes = udp.receiveData(buffer, sizeof(buffer));
                data = string(buffer, readBytes);
                if (ride == NULL) {
                    t = deserialize<Trip>(data);
                    ride = new Ride(t, &driver, c);
                }
                break;

            case 'G':
                if (ride != NULL) {
                    c->addToCurrentTime(1);
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
        udp.receiveData(buffer, sizeof(buffer));
        option = buffer[0];
    }
    return 0;
}

//while (1) {
//
//        readBytes = udp.receiveData(buffer, sizeof(buffer));
//        std::string data(buffer, readBytes);
//        cout << "size" << data.size() << std::endl;
//        if (data == exit) {
//            cout << "1e" << std::endl;
//            return 0;
//        }
//
//        if (data == advance) {
//            cout << "stay" << std::endl;
//            continue;
//        }
//
//        //deserialize receive vehicle
//        Trip *t = deserialize<Trip>(data);
//        Ride ride = Ride(t, &driver, c);
//
//        while (!ride.isDone()) {
//            readBytes = udp.receiveData(buffer, sizeof(buffer));
//            std::string operation(buffer, readBytes);
//            if (operation == advance) {
//                cout << "go" << std::endl;
//                c->addToCurrentTime(1);
//                ride.moveOneStep();
//            } else if (operation == exit) {
//                cout << "2e" << std::endl;
//                return 0;
//            }
//        }
//    }