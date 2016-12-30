//
// Created by noam on 29/12/16.
//

#include "Serialization.h"

template<class T>
T Serialization::deserialize(string serial_str) {
    T p;
    boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char>> s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> p;

    return p;
}


template<class T>
string Serialization::serialize(T *object) {
    std::string serial_str;

    boost::iostreams::back_insert_device<std::string> insertDevice(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string>> s(insertDevice);
    boost::archive::binary_oarchive oa(s);
    oa << object;
    s.flush();

    return serial_str;
}