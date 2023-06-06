//
// Created by Adrian Murawski on 17/05/2023.
//

#include "AdminService.h"

#include <utility>


AdminService::AdminService() : Service() {
    this->serviceTeams = vector < Service > ();
}

AdminService::AdminService(string identifier, vector<Station *> stations, vector < Service > serviceTeams) : Service(std::move(identifier), std::move(stations)){
    this->serviceTeams = std::move(serviceTeams);
}

AdminService::AdminService(string identifier, vector<Service> serviceTeams, vector < Station* > allStations) : Service(std::move(identifier), vector<Station*>()){
    this->serviceTeams = std::move(serviceTeams);
    this->stations = std::move(allStations);
}


bool AdminService::assignStation(Station* station, Service serviceCrew) {
    serviceCrew.supportedStations.push_back(station);
    return true;
}


void AdminService::displayStations() {
    cout << "All stations: " << endl;
    for (auto i : stations) {
        displayStationInfo(i);
    }
}


void AdminService::displayStationAssignment() {
    for (auto& service : serviceTeams) {
        cout << "Service team identifier: " << service.identifier << endl;
        for (auto i : service) {
            displayStationInfo(i);
        }
        cout << endl;
    }
}


void AdminService::displayStationInfo(Station* station){
    string stationType = station->type;
    int targetLength = 20;
    if (stationType.length() < targetLength) {
        stationType.resize(targetLength, ' ');
    }
    cout << "Type: " << stationType << "    Code: " << station->code << "     Name: " << station->name
         << "    Vehicles: " << station->currentVehicles.size() << " / " << station->maxVehiclesNumber << endl;
}

bool AdminService::removeExistingStation(Station *station) {
    int j = 0;
    for (auto &i : stations) {
        if (i->code == station->code) {
            stations.erase(stations.begin() + j);
            return true;
        }
        j += 1;
    }
    return false;
}


void AdminService::unassignRemovedStation(Station *station) {
    for (auto &crew: serviceTeams) {
        int z = 0;
        for (auto &i: crew.supportedStations) {
            if (i->code == station->code) {
                crew.supportedStations.erase(crew.supportedStations.begin() + z);
            }
            z += 1;
        }
    }
}