//
// Created by Adrian Murawski on 23/04/2023.
//

#include "Station.h"

Station::Station(string name, string code, Location location, vector < Vehicle > currentVehicles, int maxVehicles, int numberOfRentals) {
    this->name = name;
    this->code = code;
    this->location = location;
    this->currentVehicles = currentVehicles;
    this->maxVehiclesNumber = maxVehicles;
    this->numberOfRentals = numberOfRentals;
}

bool Station::checkIfSpaceAvailable(){
    if (this->currentVehicles.size() < this->maxVehiclesNumber){
        return true;
    }
    return false;
}


bool Station::addToStation(Vehicle vehicle) {
    this->currentVehicles.push_back(vehicle);
}

bool Station::changeLimit(int newLimit) {
    this->maxVehiclesNumber = newLimit;
    return true;
}

bool Station::checkIfVehicleInStation(Vehicle veh){
    for (int i = 0; i <= currentVehicles.size(); i++){
        if (currentVehicles[i] == veh){
            return true;
        }
    }
    return false;
}

bool Station::deleteVehicle(Vehicle vehicle) {
    for (int i = 0; i <= currentVehicles.size(); i++){
        if (currentVehicles[i] == vehicle){
            if (deleteVehicleByIndex(i)){
                return true;
            }
            break;
        }
    }
    return false;
}

bool Station::deleteVehicleByIndex(int index) {
    if (index > this->currentVehicles.size() or index < 0){
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

int Station::countAvailableSpots() const
{
    return this->maxVehiclesNumber - this->currentVehicles.size();
}
