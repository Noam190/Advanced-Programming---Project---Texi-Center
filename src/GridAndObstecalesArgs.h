//
// Created by mei on 12/03/17.
//

#ifndef TAXI_CENTER_GRIDANDOBSTECALESARGS_H
#define TAXI_CENTER_GRIDANDOBSTECALESARGS_H


#include <boost/serialization/access.hpp>

class string;

class GridAndObstecalesArgs {
private:
    char* args;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & args;

    }

public:
    char* getString();
};


#endif //TAXI_CENTER_GRIDANDOBSTECALESARGS_H
