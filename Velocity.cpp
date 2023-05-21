//
// Created by Adrian Murawski on 21/05/2023.
//

#include "Velocity.h"

Velocity::Velocity(vector<Station *> stations, User *user) {
this->stations = stations;
this->user = user;
}


bool Velocity::rentVehicle(Vehicle *vehicle, Station *station) {
    if (vehicle->checkRentedStatus()) {
        return false;
    }
    if (vehicle->checkReservedStatus()){
        if (!user->checkRented(vehicle)){
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
    vehicle->setRentedStatus(true);
    vehicle->setReservedStatus(false);
    vehicle->increaseNumberOfRentals();
    user->addVehicle(vehicle);
    user->increaseVehicleCounter();
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
    user->reserveVehicle(vehicle);
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
    if (!station->checkIfSpaceAvailable()){
        return false;
    }
    vehicle->setRentedStatus(false);
    user->removeVehicle(vehicle);
    user->withdraw(vehicle->rentalPrice);
    station->addToStation(vehicle);
    return true;
}


bool Velocity::cancelReservation(Vehicle *vehicle, Station *station) {
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
