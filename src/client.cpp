
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

template<class T>
T *deserialize(string serial_str) {
    T *p;
    unsigned long x = serial_str.size();
    boost::iostreams::basic_array_source<char> device(serial_str.c_str(), x);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char>> s(device);
    boost::archive::binary_iarchive ia(s);
    ia >> p;

    return p;
}


template<class T>
string serialize(T *object) {
    std::string serial_str;

    boost::iostreams::back_insert_device<std::string> insertDevice(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string>> s(insertDevice);
    boost::archive::binary_oarchive oa(s);
    oa << object;
    s.flush();

    return serial_str;
}

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


//    Point p = Point(1, 9);
//    std::string str = serialize<Point>(&p);
//    Point *p2 = deserialize<Point>(str);
//    cout << *p2;
//
//    Trip trip = Trip(6, 4, 5, 4, 34, p, Point(3, 3), list<Point>());
//    std::string str2 = serialize<Trip>(&trip);
//    Trip *T2 = deserialize<Trip>(str2);
//
//    TaxiCab taxi = TaxiCab(HONDA, RED, 12, 45, 4);
//    std::string str3 = serialize<TaxiCab>(&taxi);
//    TaxiCab *taxi2 = deserialize<TaxiCab>(str3);
//
//    StandardCab standard = StandardCab(23, 43, 7, TESLA, PINK);
//    std::string str4 = serialize<StandardCab>(&standard);
//    StandardCab *standard2 = deserialize<StandardCab>(str4);
//
//    LuxuryCab luxury = LuxuryCab(21, 56, 14, SUBARO, GREEN);
//    std::string str5 = serialize<LuxuryCab>(&luxury);
//    LuxuryCab *luxury2 = deserialize<LuxuryCab>(str5);
//
//    Driver d = Driver(Point(0, 0), 0, 30, 3, 1, MARRIED);
//    d.setTaxiCab(standard2);
//    std::string str6 = serialize<Driver>(&d);
//    Driver *dr2 = deserialize<Driver>(str6);

    //create a driver
    Driver d =insertDriver();
    //serialize driver
    std::string serial_str_driver = serialize<Driver>(&d);

    cout << argv[1] << endl;
    Udp udp(0, atoi(argv[1]));
    udp.initialize();

    char buffer_receive_vehicle[1024];
    udp.sendData(serial_str_driver);
    udp.receiveData(buffer_receive_vehicle, sizeof(buffer_receive_vehicle));
    std::string veihcleStr(buffer_receive_vehicle);
    //desreialize receive vehicle
    Vehicle *v = deserialize<Vehicle>(veihcleStr);

    char buffer_receive_trip[1024];
    udp.receiveData(buffer_receive_trip, sizeof(buffer_receive_trip));
    std::string tripStr(buffer_receive_trip);
    //desreialize receive vehicle
    Trip *t = deserialize<Trip>(tripStr);




//    char buffer[1024];
//    udp.sendData(serial_str_driver);
//    udp.receiveData(buffer, sizeof(buffer));
//    cout << buffer << endl;

    return 0;
}
