//
// Created by Adrian Murawski on 04/06/2023.
//

#include "UserInterface.h"

UserInterface::UserInterface(vector<Station *> stations, User *user) : stations(stations), user(user) {
    Velocity vel(stations, user);
    this->velocity = vel;
}

bool UserInterface::rentVehicle(Vehicle* vehicle, Station* station) {
    return this->velocity.rentVehicle(vehicle, station);
}

bool UserInterface::reserveVehicle(Vehicle* vehicle, Station* station){
    return this->velocity.reserveVehicle(vehicle, station);
}

bool UserInterface::returnVehicle(Vehicle* vehicle, Station* station){
    return this->velocity.returnVehicle(vehicle, station);
}

bool UserInterface::addCredits(float amount){
    return this->velocity.addCredits(amount);
}

bool UserInterface::cancelReservation(Vehicle* vehicle, Station* station){
    return this->velocity.cancelReservation(vehicle, station);
}

Station* UserInterface::findNearestStation(){
    return this->velocity.findNearestStation();
}

map < int, vector < Station* > > UserInterface::calculateDistanceToAllStations(){
    return this->velocity.calculateDistanceToAllStations();
}

