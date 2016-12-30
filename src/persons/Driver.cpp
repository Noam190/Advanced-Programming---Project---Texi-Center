//
// Created by mei and noam on 29/11/16.
//

#include "Driver.h"
//constructor
Driver::Driver(Point location, int id, int age, int yearsOfExperience,
               int averageSatisfaction, STATUS status, int vehicleId) : Person(id, age, status, location), taxi(NULL) {
    this->yearsOfExperience = yearsOfExperience;
    this->averageSatisfaction = averageSatisfaction;
    this->vehicleId=vehicleId;
}

//getters and setters
int Driver::getYearsOfExperience(){
    return this->yearsOfExperience;
}
//getters and setters
void Driver::setYearsOfExperience(int yearsOfExperience){
    this->yearsOfExperience = yearsOfExperience;
}
//getters and setters
int Driver::getAverageSatisfaction(){
    return this->averageSatisfaction;
}
//getters and setters
void Driver::setAverageSatisfaction(int averageSatisfaction){
    this->averageSatisfaction = averageSatisfaction;
}
//getters and setters
int Driver::getVehicleId(){
    return  this->vehicleId;
}

//getters and setters
void Driver::setVehicleId(int vehicleIdNew){
    this->vehicleId =vehicleIdNew;
}