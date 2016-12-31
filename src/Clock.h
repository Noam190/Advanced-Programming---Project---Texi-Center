//
// Created by mei on 30/12/16.
//
#include <boost/serialization/list.hpp>
#ifndef TAXI_CENTER_CLOCK_H
#define TAXI_CENTER_CLOCK_H


class Clock {
private:
    friend boost::serialization::access;
    template<class Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & currentTime;
        archive & endTime;

    }
    int currentTime;
    int endTime; // time to stop
public:
    //constructor -init
    Clock() : currentTime(0), endTime(5){};
    //return the current time, if the time is over return -1
    int getCurrentTime();

    //add 'addTime' to the current time
    void addToCurrentTime(int addTime);
};


#endif //TAXI_CENTER_CLOCK_H
