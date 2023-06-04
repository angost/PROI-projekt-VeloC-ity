//
// Created by Adrian Murawski on 01/05/2023.
//

#include "Service.h"
#include <iostream>
#include <utility>

using namespace std;

Service::Service() {
    vector < Station* > stations;
    this->identifier = "";
    this->supportedStations = stations;
}


Service::Service(string identifier, vector<Station*> stations) {
    this->identifier = std::move(identifier);
    this->supportedStations = std::move(stations);
}

bool Service::checkVehicleCanBeMoved(Vehicle* veh, Station* fromStation, Station* toStation){
    if (not fromStation->checkIfVehicleInStation(veh)){
        return false;
    }
    if (not toStation->checkIfSpaceAvailable()){
        return false;
    }
    return true;
}


bool Service::moveVehicle(Vehicle* vehicle, Station* fromStation, Station* toStation) {
    if (!checkVehicleCanBeMoved(vehicle, fromStation, toStation)){
        return false;
    }
    if (fromStation->deleteVehicle(vehicle) and toStation->addToStation(vehicle)){
        return true;
    }
    return false;
}

bool Service::repairVehicle(Vehicle* vehicle){
    vehicle->setTechnicalCondition(5);
    return true;
}

void Service::printSupportedStations() {
    for (auto i : supportedStations){
        cout << i->code << " " << i->name << endl;
    }
}

void Service::printVehiclesInStation(Station *station) {
    for (auto i : *station){
        cout << "ID: " << i->id << "     "  << "Status (reserved): ";
        cout << boolalpha << i->rentedStatus << endl;
    }
}

bool Service::changeStationLimit(int newLimit, Station* station) {
    return station->changeLimit(newLimit);
}

bool Service::changeStationLocation(Station* station, Location newLocation) {
    return station->changeLocation(std::move(newLocation));
}

bool Service::addVehicle(Station *station, Vehicle *vehicle) {
    if (!station->checkIfSpaceAvailable()){
        return false;
    }
    return station->addToStation(vehicle);
}

bool Service::removeVehicle(Station *station, Vehicle *vehicle) {
    if (!station->checkIfVehicleInStation(vehicle)) {
        return false;
    }
    return station->deleteVehicle(vehicle);
}

vector< Station* >::iterator Service::begin() {
    return supportedStations.begin();
}


vector < Station* >::iterator Service::end() {
    return supportedStations.end();
}