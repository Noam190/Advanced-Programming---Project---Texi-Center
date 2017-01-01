//
// Created by mei and noam on 29/11/16.
//

#include "Driver.h"
// constructor
Driver::Driver(Point location, int id, unsigned int age, unsigned int yearsOfExperience,
               int vehicleId, STATUS status)
        : Person(id, age, status, location), taxiCab(NULL) {
    this->yearsOfExperience = yearsOfExperience;
    this->vehicleId = vehicleId;
    this->averageSatisfaction = 0;
    this->numberOfVotes = 0;
    this->totalPoints = 0;
}

//getters and setters
int Driver::getYearsOfExperience(){
    return this->yearsOfExperience;
}
//getters and setters
void Driver::setYearsOfExperience(unsigned yearsOfExperience) {
    this->yearsOfExperience = yearsOfExperience;
}
//getters and setters
unsigned int Driver::getAverageSatisfaction() {
    return this->averageSatisfaction;
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

void Driver::rateDriver(unsigned int points) {
    this->totalPoints += points;
    this->numberOfVotes++;
    this->averageSatisfaction = totalPoints / numberOfVotes;
}

int Driver::getVelocity() {
    if (this->taxiCab != NULL) {
        return this->taxiCab->getVelocity();
    }
    return 0;
}


