//
// Created by mei and noam on 29/11/16.
//

#include "Driver.h"
//constructor
Driver::Driver(Point location, int id, unsigned int age, unsigned int yearsOfExperience,
               int vehicleId, STATUS status, int taxiType)
        : Person(id, age, status, location), taxiCab(NULL) , taxiType(0){
    this->yearsOfExperience = yearsOfExperience;
    this->vehicleId = vehicleId;
    this->averageSatisfaction = 0;
    this->numberOfVotes = 0;
    this->totalPoints = 0;
    this->taxiType=0;
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
    if(this->taxiCab->getTaxiType()==1)
        this->taxiType=1;
    if(this->taxiCab->getTaxiType()==2)
        this->taxiType=2;
    this->taxiCab = taxi;
}

TaxiCab *Driver::getTaxiCab() {
    if(this->taxiCab->getTaxiType()==1)
        setGetTaxiType(1);
    if(this->taxiCab->getTaxiType()==2)
        setGetTaxiType(2);
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

int Driver::getTaxiType(){
    return this->taxiType;
}
void  Driver::setGetTaxiType(int newType){
    this->taxiType=newType;
}

