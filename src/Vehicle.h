//
// Created by noam on 12/12/16.
//

#ifndef EX2AP_VEHICLE_H
#define EX2AP_VEHICLE_H

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

enum MANUFACTURER {HONDA, SUBARO, TESLA, FIAT};
enum COLOR {RED, GREEN, BLUE, PINK, WHITE};

class Vehicle {
protected:
    MANUFACTURER manu;
    COLOR c;
public:
    //constructor
    Vehicle(MANUFACTURER carManufacturer, COLOR c);

    //get the COLOR of the Vehicle
    COLOR getColor();

    //get the MANUFACTURER of the Vehicle
    MANUFACTURER  getCarManufacturer();

    template<class Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & BOOST_SERIALIZATION_NVP(manu);
        archive & BOOST_SERIALIZATION_NVP(c);
    }

};


#endif //EX2AP_VEHICLE_H
