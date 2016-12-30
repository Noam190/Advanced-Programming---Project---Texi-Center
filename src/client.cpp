
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include "sockets/Udp.h"
#include "core_classes/Point.h"
#include "persons/Driver.h"

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


int main(int argc, char *argv[]) {
    std::cout << "Hello, from client" << std::endl;

    Driver d = Driver(Point(0, 0), 0, 30, 3, 1, MARRIED);

    Point p = Point(1, 9);
    std::string str = serialize<Point>(&p);
    Point *d2 = deserialize<Point>(str);
    cout << d2;

    Trip trip = Trip(6, 4, 5, 4, 34, p, Point(3, 3), list<>);


    cout << argv[1] << endl;
    Udp udp(0, atoi(argv[1]));
    udp.initialize();

    char buffer[1024];
    udp.sendData("hello");
    udp.receiveData(buffer, sizeof(buffer));
    cout << buffer << endl;

    return 0;
}
