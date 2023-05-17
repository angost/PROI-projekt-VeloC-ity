//
// Created by Adrian Murawski on 01/05/2023.
//

#include "Service.h"
#include <algorithm>

using namespace std;

Service::Service() {
    vector < Station* > stations;
    this->supportedStations = stations;
}


Service::Service(vector<Station*> stations) {
    this->supportedStations = stations;
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

    if (fromStation->deleteVehicle(vehicle)){
        if (toStation->addToStation(vehicle)){
            return true;
        }
    }
    return false;
}

bool Service::repairVehicle(Vehicle* vehicle){
    vehicle->setTechnicalCondition(5);
    return true;
}

vector< Station* >::iterator Service::begin() {
    return supportedStations.begin();
}


vector < Station* >::iterator Service::end() {
    return supportedStations.end();
}