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


bool Velocity::rentVehicle(Vehicle *vehicle, Station *station, string &errorInfo) {
    if (vehicle->checkRentedStatus()) {
        errorInfo = "Vehicle is already rented.";
        return false;
    }
    if (vehicle->checkReservedStatus()){
        if (!user->checkReserved(vehicle)){
            errorInfo = "Vehicle is reserved by a different user.";
            return false;
        }
    }
    if (!vehicle->checkAbleToUse()){
        errorInfo = "Vehicle is not able to use.";
        return false;
    }
    if (!user->checkRentSpace()){
        errorInfo = "User has not enough space to rent Vehicle.";
        return false;
    }
    if (!user->checkSolvency()){
        errorInfo = "User's balance is to low to rent Vehicle.";
        return false;
    }
    if (!station->checkIfVehicleInStation(vehicle)){
        errorInfo = "Vehicle is not on provided Station.";
        return false;
    }
    if (user->getLocation().getDistanceBetweenLocations(station->getStationLocation()) > 0){
        errorInfo = "To rent a Vehicle User has to be in the same Location as Station with Vehicle.";
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


bool Velocity::reserveVehicle(Vehicle *vehicle, Station *station, string &errorInfo) {
    if (vehicle->checkRentedStatus()) {
        errorInfo = "Vehicle is already rented.";
        return false;
    }
    if (vehicle->checkReservedStatus()){
        errorInfo = "Vehicle is already reserved.";
        return false;
    }
    if (!vehicle->checkAbleToUse()){
        errorInfo = "Vehicle is not able to use.";
        return false;
    }
    if (!user->checkReserveSpace()){
        errorInfo = "User has not enough space to reserve Vehicle.";
        return false;
    }
    if (!user->checkSolvency()){
        errorInfo = "User's balance is to low to reserve Vehicle.";
        return false;
    }
    if (!station->checkIfVehicleInStation(vehicle)){
        errorInfo = "Vehicle is not on provided Station.";
        return false;
    }
    vehicle->setReservedStatus(true);
    user->reserveVehicle(vehicle);
    return true;
}


bool Velocity::addCredits(float amount) {
    user->makeDeposit(amount);
    return true;
}

bool Velocity::returnVehicle(Vehicle *vehicle, Station *station, string &errorInfo) {
    if (!vehicle->checkRentedStatus()){
        errorInfo = "Vehicle is not rented.";
        return false;
    }
    if (!user->checkRented(vehicle)){
        errorInfo = "Vehicle is not rented by this User.";
        return false;
    }
    if (user->getLocation().getDistanceBetweenLocations(station->getStationLocation()) > 0){
        errorInfo = "To return a Vehicle User has to be in the same Location as provided Station.";
        return false;
    }
    if (!station->checkIfSpaceAvailable()){
        errorInfo = "No space available on provided Station.";
        return false;
    }
    vehicle->setRentedStatus(false);
    user->removeVehicle(vehicle);
    user->withdraw(vehicle->rentalPrice);
    station->addToStation(vehicle);
    return true;
}


bool Velocity::cancelReservation(Vehicle *vehicle, string &errorInfo) {
    if (!vehicle->checkReservedStatus()){
        errorInfo = "Vehicle is not reserved.";
        return false;
    }
    if (!user->checkReserved(vehicle)){
        errorInfo = "Vehicle is not reserved by this User.";
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
