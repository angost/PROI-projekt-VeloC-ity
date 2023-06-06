//
// Created by Adrian Murawski on 01/05/2023.
//

#include "Service.h"


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
        string stationType = i->type;
        string stationName = i->name;
        int targetLength = 15;
        if (stationType.length() < targetLength) {
            stationType.resize(targetLength, ' ');
        }
        if (stationName.length() < targetLength) {
            stationName.resize(targetLength, ' ');
        }
        Location currentStationLocation = i->getStationLocation();
        cout << "Type: " << stationType << "    Code: " << i->code << "     Name: " << stationName
        << "    Vehicles: " << i->currentVehicles.size() << " / " << i->maxVehiclesNumber <<
        "       Address: " << currentStationLocation.city << " "
        << currentStationLocation.district << " ul. " << currentStationLocation.street_name << " "
        << currentStationLocation.street_number << " - (" << currentStationLocation.x_coord << ", "
        << currentStationLocation.y_coord << ")" << endl;
    }
}

void Service::printVehiclesInStation(Station *station) {
    station->printVehiclesInStation();
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