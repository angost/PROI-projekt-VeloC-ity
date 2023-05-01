//
// Created by Adrian Murawski on 23/04/2023.
//

#include "Station.h"


bool Station::addToStation(Vehicle vehicle) {
    if (this->currentVehicles.size() < this->maxVehiclesNumber){
        this->currentVehicles.push_back(vehicle);
    } else {
        return false;
    }
    return true;
}

bool Station::changeLimit(int newLimit) {
    this->maxVehiclesNumber = newLimit;
    return true;
}

bool Station::deleteVehicle(Vehicle vehicle) {
    for (int i = 0; i <= currentVehicles.size(); i++){
        if (currentVehicles[i] == vehicle){
            deleteVehicleByIndex(i);
        }
    }
}

bool Station::deleteVehicleByIndex(int index) {
    if (index > this->currentVehicles.size()){
        return false;
    }
    this->currentVehicles.erase(currentVehicles.begin() + index);
    return true;
}

void Station::incrementCounter() {
    this->numberOfRentals += 1;
}

bool Station::changeLocation(Location newLocation) {
    this->location = newLocation;
    return true;
}
