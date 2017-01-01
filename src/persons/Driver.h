//
// Created by mei on 29/11/16.
//
#include <string>
#include "Person.h"
#include "../Trip.h"
#include "../cabs/TaxiCab.h"

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#ifndef EX2AP_DRIVER_H
#define EX2AP_DRIVER_H



class Driver : public Person{
private:
    friend boost::serialization::access;
    template<class Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & boost::serialization::base_object<Person>(*this);
        archive & taxiCab;
        archive & vehicleId;
        archive & yearsOfExperience;
        archive & averageSatisfaction;
        archive & totalPoints;
        archive & numberOfVotes;
        archive & taxiType;
    }

    unsigned int yearsOfExperience;
    unsigned int averageSatisfaction;
    unsigned int totalPoints;
    unsigned int numberOfVotes;
    int vehicleId;
    TaxiCab *taxiCab;
    int taxiType;//0 there is no taxi,1 standart,2luxury

public:

    Driver() : taxiCab(NULL), averageSatisfaction(0), totalPoints(0),
               numberOfVotes(0),taxiType(0) {};

    // Constructor all the members
    Driver(Point location, int id, unsigned int age, unsigned int yearsOfExperience,
           int vehicleId, STATUS status,int taxiType );

    //getters and setters
    int getYearsOfExperience();

    //getters and setters
    void setYearsOfExperience(unsigned int yearsOfExperience);

    //getters and setters
    unsigned int getAverageSatisfaction();

    void setVehicleId(int vehicleId);

    int getVehicleId();

    void setTaxiCab(TaxiCab *taxi);

    TaxiCab *getTaxiCab();

    void rateDriver(unsigned int points);

    int getTaxiType();

    void  setGetTaxiType(int newType);

};


#endif //EX2AP_DRIVER_H
