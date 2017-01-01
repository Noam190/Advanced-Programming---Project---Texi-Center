//
// Created by mei on 29/11/16.
//

#include "TaxiCab.h"

//constructor
TaxiCab::TaxiCab(MANUFACTURER carManufacturer, COLOR color, int cabId,
                 int numOfKilometers, int tariff, int taxiType)
        : Vehicle(carManufacturer, color) {
    this->cabId = cabId;
    this->numberOfKilometers = numOfKilometers;
    this->tariff = tariff;
    this->taxiType=taxiType;
}

//getters and setters
int TaxiCab::getId(){
    return this->cabId;
}

//getters and setters
void TaxiCab::setId(int id){
    this->cabId = id;
}

//getters and setters
int TaxiCab::getKilometers(){
    return this->numberOfKilometers;
}
//getters and setters
void TaxiCab::setKilometers(int numberOfKilometers){
    this->numberOfKilometers = numberOfKilometers;
}

int TaxiCab::getTariff(){
    return this->tariff;
}

//getters and setters
void TaxiCab::setTariff(int tariff){
    this->tariff = tariff;
}

//get type of taxi - 1  standart, 2 luxury
int TaxiCab::getTaxiType(){
    return  this->taxiType;
}