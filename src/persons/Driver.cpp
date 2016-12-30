//
// Created by mei and noam on 29/11/16.
//

#include "Driver.h"
//constructor
Driver::Driver(Point location, int id, int age, int yearsOfExperience,
               int vehicleId, STATUS status) : Person(id, age, status, location), taxiCab(NULL) {
    this->yearsOfExperience = yearsOfExperience;
    this->vehicleId = vehicleId;
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

void Driver::setTaxiCab(TaxiCab *taxi) {
    this->taxiCab = taxi;
}

TaxiCab *Driver::getTaxiCab() {
    return this->taxiCab;
}

void Driver::setVehicleId(int vehicleId) {
    this->vehicleId = vehicleId;
}

int Driver::getVehicleId() {
    return  this->vehicleId;
}
