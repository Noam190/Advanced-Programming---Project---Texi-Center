
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include "sockets/Udp.h"
#include "core_classes/Point.h"
#include "persons/Driver.h"
#include "cabs/StandardCab.h"
#include "cabs/LuxuryCab.h"
#include "creators/DriverCreator.h"
#include "Clock.h"
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
    std::cout << "Hello, from client" << std::endl;

    //create a driver
    Driver driver = insertDriver();
    //serialize driver
    std::string serial_str_driver = serialize<Driver>(&driver);

    cout << argv[1] << endl;
    Udp udp(0, atoi(argv[1]));
    udp.initialize();

    //deserialize receive clock
    char buffer_receive_clock[1024];
    udp.receiveData(buffer_receive_clock, sizeof(buffer_receive_clock));
    std::string clockStr(buffer_receive_clock);
    Clock *c = deserialize<Clock>(clockStr);

    char buffer_receive_vehicle[1024];
    udp.sendData(serial_str_driver);
    udp.receiveData(buffer_receive_vehicle, sizeof(buffer_receive_vehicle));
    std::string vehicleStr(buffer_receive_vehicle);
    //deserialize receive vehicle
    TaxiCab *v = deserialize<TaxiCab>(vehicleStr);

    char buffer_receive_trip[1024];
    while (1) {

        udp.receiveData(buffer_receive_trip, sizeof(buffer_receive_trip));
        std::string tripStr(buffer_receive_trip);
        //deserialize receive vehicle
        Trip *t = deserialize<Trip>(tripStr);
        Ride ride = Ride(t, &driver);

        while (!ride.isDone()) {
            udp.receiveData(buffer_receive_trip, sizeof(buffer_receive_trip));
            std::string operation(buffer_receive_trip);
            if (operation == "operation") {
                ride.moveOneStep();
            } else if (operation == "exit") {
                return 0;
            }
        }
    }

    return 0;
}
