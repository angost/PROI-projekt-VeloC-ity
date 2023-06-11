//
// Created by Adrian Murawski on 17/05/2023.
//

#include "AdminService.h"

#include <utility>


AdminService::AdminService() : Service() {
    this->serviceTeams = vector < Service > ();
}

AdminService::AdminService(string identifier, vector<Service> &serviceTeams, vector < Station* > &allStations, vector < Location > locations) : Service(identifier, locations){
    this->serviceTeams = serviceTeams;
    this->stations = allStations;
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
    string stationName = station->name;
    int targetLength = 15;
    if (stationType.length() < targetLength) {
        stationType.resize(targetLength, ' ');
    }
    if (stationName.length() < targetLength) {
        stationName.resize(targetLength, ' ');
    }
    Location currentStationLocation = station->getStationLocation();
    cout << "Type: " << stationType << "   Code: " << station->code << "    Name: " << stationName
         << "   Vehicles: " << station->currentVehicles.size() << " / " << station->maxVehiclesNumber <<
         "      Address: " << currentStationLocation.city << " "
         << currentStationLocation.district << " ul. " << currentStationLocation.street_name << " "
         << currentStationLocation.street_number << " - (" << currentStationLocation.x_coord << ", "
         << currentStationLocation.y_coord << ")" << endl;
}
