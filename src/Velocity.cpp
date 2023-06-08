//
// Created by Adrian Murawski on 21/05/2023.
//
#include "Velocity.h"




Velocity::Velocity() {
    vector<Station *> stations;
    StandardUser user1;
    this->stations = stations;
    this->user = &user1;
}


Velocity::Velocity(vector<Station *> stations, User *user) {
this->stations = std::move(stations);
this->user = user;
}


bool Velocity::rentVehicle(Vehicle *vehicle, Station *station) {
    if (vehicle->checkRentedStatus()) {
        return false;
    }
    if (vehicle->checkReservedStatus()){
        if (!user->checkReserved(vehicle)){
            return false;
        }
    }
    if (!vehicle->checkAbleToUse()){
        return false;
    }
    if (!user->checkRentSpace()){
        return false;
    }
    if (!user->checkSolvency()){
        return false;
    }
    if (!station->checkIfVehicleInStation(vehicle)){
        return false;
    }
    if (user->getLocation().getDistanceBetweenLocations(station->getStationLocation()) > 0){
        return false;
    }
    vehicle->setRentedStatus(true);
    vehicle->setReservedStatus(false);
    vehicle->increaseNumberOfRentals();
    user->addVehicle(vehicle);
    user->increaseVehicleCounter();
    if (user->checkReserved(vehicle)){
        user->cancelReserveVehicle(vehicle);
    }
    station->deleteVehicle(vehicle);
    station->incrementCounter();
    return true;
}


bool Velocity::reserveVehicle(Vehicle *vehicle, Station *station) {
    if (vehicle->checkRentedStatus()) {
        return false;
    }
    if (vehicle->checkReservedStatus()){
        return false;
    }
    if (!vehicle->checkAbleToUse()){
        return false;
    }
    if (!user->checkReserveSpace()){
        return false;
    }
    if (!user->checkSolvency()){
        return false;
    }
    if (!station->checkIfVehicleInStation(vehicle)){
        return false;
    }
    vehicle->setReservedStatus(true);
    user->reserveVehicle(vehicle, station);
    return true;
}


bool Velocity::addCredits(float amount) {
    user->makeDeposit(amount);
    return true;
}

bool Velocity::returnVehicle(Vehicle *vehicle, Station *station) {
    if (!vehicle->checkRentedStatus()){
        return false;
    }
    if (!user->checkRented(vehicle)){
        return false;
    }
    if (user->getLocation().getDistanceBetweenLocations(station->getStationLocation()) > 0){
        return false;
    }
    if (!station->checkIfSpaceAvailable()){
        return false;
    }
    vehicle->setRentedStatus(false);
    user->removeVehicle(vehicle);
    user->withdraw(vehicle->rentalPrice);
    station->addToStation(vehicle);
    return true;
}


bool Velocity::cancelReservation(Vehicle *vehicle) {
    if (!vehicle->checkReservedStatus()){
        return false;
    }
    if (!user->checkReserved(vehicle)){
        return false;
    }
    vehicle->setReservedStatus(false);
    user->cancelReserveVehicle(vehicle);
    return true;
}

Station* Velocity::findNearestStation() {
    int distance = 9999;
    auto nearest = stations[0];
    for (auto i: stations) {
        int new_distance = user->userLocation.getDistanceBetweenLocations(i->getStationLocation());
        if (new_distance < distance) {
            distance = new_distance;
            nearest = i;
        }
    }
    return nearest;
}

map<int, vector<Station *>> Velocity::calculateDistanceToAllStations() {
    map < int, vector < Station* > > distanceMap;
    for (auto i : stations){
        int distance = user->userLocation.getDistanceBetweenLocations(i->getStationLocation());
        distanceMap[distance].push_back(i);
    }
    return distanceMap;
}
