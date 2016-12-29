//
// Created by noam on 29/12/16.
//

#ifndef TAXI_CENTER_SERIALIZATION_H
#define TAXI_CENTER_SERIALIZATION_H

#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

using namespace std;
using namespace boost::archive;
using namespace boost::iostreams;

template<class T>
T deserialize(string serial_str);

template<class T>
string serialize(T *object);


#endif //TAXI_CENTER_SERIALIZATION_H
