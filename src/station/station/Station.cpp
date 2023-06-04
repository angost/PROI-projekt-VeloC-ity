//
// Created by Adrian Murawski on 23/04/2023.
//

#include "Station.h"
#include <fstream>
#include <iostream>
#include <utility>

Station::Station(string name, string code, Location location, vector < Vehicle* > currentVehicles, int maxVehicles, int numberOfRentals) {
    this->name = std::move(name);
    this->code = std::move(code);
    this->location = std::move(location);
    this->currentVehicles = std::move(currentVehicles);
    this->maxVehiclesNumber = maxVehicles;
    this->numberOfRentals = numberOfRentals;
}

bool Station::checkIfSpaceAvailable() const{
    if (this->currentVehicles.size() < this->maxVehiclesNumber){
        return true;
    }
    return false;
}


bool Station::addToStation(Vehicle* vehicle) {
    this->currentVehicles.push_back(vehicle);
    return true;
}

bool Station::changeLimit(int newLimit) {
    if (newLimit < 0){
        return false;
    }
    this->maxVehiclesNumber = newLimit;
    return true;
}

bool Station::checkIfVehicleInStation(Vehicle* veh){
    for (int i = 0; i <= currentVehicles.size(); i++){
        if (currentVehicles[i] == veh){
            return true;
        }
    }
    return false;
}

bool Station::deleteVehicle(Vehicle* vehicle) {
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
    this->location = std::move(newLocation);
    return true;
}

int Station::countAvailableSpots() const
{
    return this->maxVehiclesNumber - (int) this->currentVehicles.size();
}

bool Station::operator==(Station *other) const {
    return (this->code == other->code);
}

Location Station::getStationLocation() {
    return this->location;
}

void Station::printVehiclesInStation() {
    for (auto i : currentVehicles){
        cout << "ID: " << i->id << "     "  << "Status (reserved): ";
        cout << boolalpha << i->rentedStatus << endl;
    }
}

vector<Vehicle *>::iterator Station::begin() {
    return currentVehicles.begin();
}


vector < Vehicle* >::iterator Station::end() {
    return currentVehicles.end();
}

ostream &operator<<(ostream &out, const Station &station) {
    out << station.name << " " << station.code << " " << station.maxVehiclesNumber << " " << station.numberOfRentals;
    return out;
}

istream &operator>>(istream &stream, Station &station) {
    stream >> station.name >> station.code >> station.maxVehiclesNumber >> station.numberOfRentals;
    return stream;
}

