//
// Created by mei on 29/11/16.
//
#include "Point.h"
#ifndef EX2AP_TRIP_H
#define EX2AP_TRIP_H

class Trip {
private:

    unsigned long length;
    int id;
    int totalMeters;
    int numOfPassengers;
    double tariff;
    Point startPoint;
    Point endPoint;
    Point currentLocation;
public:
    // Constructor all the members
    Trip(unsigned long length, int id, int totalMeters,
           int numberOfPass,
         double tariff, Point start, Point end);

    //getters ang setters
    unsigned long getLength();

    //getters ang setters
    void setLength(unsigned long length);

    //getters ang setters
    int getId();

    //getters ang setters
    void setId(int id);

    //getters ang setters
    int getTotalMeters();

    //getters ang setters
    void setTotalMeters(int totalMeters);

    //getters ang setters
    int getNumberOfPassengers();

    //getters ang setters
    void setNumberOfPassengers(int numberOfPassengers);

    //getters ang setters
    double getTariff();

    //getters ang setters
    void setTariff(double tariff);

    //getters ang setters
    Point getStartPoint();

    //getters ang setters
    Point getEndPoint();

    //getters ang setters
    void setStartPoint(Point p);

    //getters ang setters
    void setEndPoint(Point p);

    //getters ang setters
    Point getCurrentPoint();

    //getters ang setters
    void setCurrentPoint(Point p);

    //update the trip location
   void updateLocation(Point p);

    template<class Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & BOOST_SERIALIZATION_NVP(length);
        archive & BOOST_SERIALIZATION_NVP(id);
        archive & BOOST_SERIALIZATION_NVP(totalMeters);
        archive & BOOST_SERIALIZATION_NVP(numOfPassengers);
        archive & BOOST_SERIALIZATION_NVP(tariff);
        archive & BOOST_SERIALIZATION_NVP(startPoint);
        archive & BOOST_SERIALIZATION_NVP(endPoint);
        archive & BOOST_SERIALIZATION_NVP(currentLocation);
    }

};


#endif //EX2AP_TRIP_H
