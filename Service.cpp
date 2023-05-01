//
// Created by Adrian Murawski on 01/05/2023.
//

#include "Service.h"
#include <algorithm>

using namespace std;

Service::Service(vector<Station> stations) {
    this->supportedStations = stations;
}

bool Service::moveVehicle(int vehicle, Station fromStation, Station toStation) {
    if (std::find(supportedStations.begin(), supportedStations.end(), fromStation) == supportedStations.end()
    or std::find(supportedStations.begin(), supportedStations.end(), toStation) == supportedStations.end()) {
        return false;
    if (fromStation.deleteVehicle(vehicle)){
        if (toStation.addToStation(vehicle)){
            return true;
        }
    }
    return false;
}

bool Service::repairVehicle(int vehicle){
//TODO when class Vehicle is finished
    vehicle.repair();
    return true;
}