//
// Created by Adrian Murawski on 01/05/2023.
//

#include "Service.h"
#include <algorithm>

using namespace std;

Service::Service(vector<Station> stations) {
    this->supportedStations = stations;
}

bool Service::checkVehicleCanBeMoved(Vehicle veh, Station fromStation, Station toStation){
    if (std::find(supportedStations.begin(), supportedStations.end(), fromStation) == supportedStations.end()
        or std::find(supportedStations.begin(), supportedStations.end(), toStation) == supportedStations.end()) {
        return false;
    }
    if (not fromStation.checkIfVehicleInStation(veh)){
        return false;
    }
    if (not toStation.checkIfSpaceAvailable()){
        return false;
    }
    return true;
}


bool Service::moveVehicle(Vehicle vehicle, Station fromStation, Station toStation) {

    if (fromStation.deleteVehicle(vehicle)){
        if (toStation.addToStation(vehicle)){
            return true;
        }
    }
    return false;
}

bool Service::repairVehicle(Vehicle vehicle){
//TODO when class Vehicle is finished
    vehicle.setTechnicalCondition(5);
    return true;
}