#include <iostream>
#include "sockets/Udp.h"
#include "core_classes/Matrix.h"
#include "TaxiCenter.h"
#include "MenuServer.h"
#include "Menu.h"

#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
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

void updatesFromClient(TaxiCenter taxiCenter){
    Udp udp(1, 5555);
    udp.initialize();

    char buffer[1024];
    udp.receiveData(buffer, sizeof(buffer));
    cout << buffer << endl;
    udp.sendData("sup?");


// deserialize driver
    string serial_str_driver;
    std::cin>> serial_str_driver;
    Driver *d = deserialize<Driver>(serial_str_driver);
    taxiCenter.addDriver(*d);

    TaxiCab taxiCab = taxiCenter.getTaxi(d->getVehicleId());
    //serialize taxi
    string serial_str_vehicle =serialize(&taxiCab);

    //sent back the taxi
    udp.sendData(serial_str_vehicle);

    //serialize trip
    taxiCenter.createRides();
    Trip *trip = taxiCenter.getTrip(d->getId());
    string serial_str_trip=serialize(trip);
    udp.sendData(serial_str_trip);

}
int main() {
    std::cout << "Hello, from server" << std::endl;
    std::cout << "standard menu" << std::endl;

    TaxiCenter taxiCenter = TaxiCenter();
    int width, height;

    //grid initialize grid and add obstacles if there are any.
    std::cin >> width >> height;
    Matrix grid=Matrix(width,height);

    Menu menu = Menu(taxiCenter, grid);
    //run all the other inputs
    menu.run(taxiCenter);


//    Udp udp(1, 5555);
//    udp.initialize();


//    char buffer[1024];
//    udp.receiveData(buffer, sizeof(buffer));
//    cout << buffer << endl;
//    udp.sendData("sup?");
//
//
//// deserialize driver
//    string serial_str_driver;
//    std::cin>> serial_str_driver;
//    Driver *d = deserialize<Driver>(serial_str_driver);
//    taxiCenter.addDriver(*d);
//
//    TaxiCab taxiCab = taxiCenter.getTaxi(d->getVehicleId());
//    //serialize taxi
//
//    string serial_str_vehicle =serialize(&taxiCab);
//
//    //sent back the taxi
//    udp.sendData(serial_str_vehicle);
//
//    //serialize trip
//    taxiCenter.createRides();
//    Trip *trip = taxiCenter.getTrip(d->getId());
//    string serial_str_trip=serialize(trip);
//    udp.sendData(serial_str_trip);



    Udp udp2(1, 5555);
    udp2.initialize();

    char buffer2[1024];
    udp2.receiveData(buffer2, sizeof(buffer2));
    cout << buffer2 << endl;
    udp2.sendData("sup?");




    // support more than one client?
    return 0;
}

