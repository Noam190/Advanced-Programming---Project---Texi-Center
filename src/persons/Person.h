//
// Created by mei on 03/12/16.
//

#ifndef EX2AP_PERSON_H
#define EX2AP_PERSON_H

#include <string>
#include <boost/serialization/access.hpp>
#include "../core_classes/Point.h"

enum  STATUS {SINGLE, MARRIED, DIVORCED, WIDOWED };

class Person {
private:
    friend boost::serialization::access;
    template<class Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & id;
        archive & age;
        archive & status;
        archive & location;
    }
    int id;
    int age;
    STATUS status;
    Point location;
public:
    //constructor
    Person(int id, int age, STATUS status, Point location);

    //getters and setters
    Point getCurrentLocation();

    //equal two person
    bool equalPerson(Person p2);

    //update current location
    void updateLocation(Point p);

    //getters and setters
    int getId();

    //getters and setters
    void setId(int id);

    //getters and setters
    int getAge();

    //getters and setters
    void setAge(int age);

    //getters and setters
    STATUS getStatus();

    //getters and setters
    void setMaritalStatus(STATUS status);
};


#endif //EX2AP_PERSON_H
