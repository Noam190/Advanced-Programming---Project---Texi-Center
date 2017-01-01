
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
    unsigned long readBytes;
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
    char buffer_receive_clock[1024];
    readBytes = udp.receiveData(buffer_receive_clock, sizeof(buffer_receive_clock));
    std::string clockStr(buffer_receive_clock, readBytes);
    Clock *c = deserialize<Clock>(clockStr);

    char buffer_receive_vehicle[1024];
    readBytes = udp.receiveData(buffer_receive_vehicle, sizeof(buffer_receive_vehicle));
    std::string vehicleStr(buffer_receive_vehicle, readBytes);
    //deserialize receive vehicle
    TaxiCab *taxiCab = deserialize<TaxiCab>(vehicleStr);
    driver.setTaxiCab(taxiCab);

    char buffer_receive_data[1024];
    while (1) {

        readBytes = udp.receiveData(buffer_receive_data, sizeof(buffer_receive_data));
        std::string data(buffer_receive_data, readBytes);
        if (data == "exit") {
            return 0;
        }

        if (data == "advance") {
            continue;
        }

        //deserialize receive vehicle
        Trip *t = deserialize<Trip>(data);
        Ride ride = Ride(t, &driver, c);

        while (!ride.isDone()) {
            readBytes = udp.receiveData(buffer_receive_data, sizeof(buffer_receive_data));
            std::string operation(buffer_receive_data, readBytes);
            if (operation == "advance") {
                c->addToCurrentTime(1);
                ride.moveOneStep();
            } else if (operation == "exit") {
                return 0;
            }
        }
    }
}
