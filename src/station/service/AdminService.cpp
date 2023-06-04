//
// Created by Adrian Murawski on 17/05/2023.
//

#include "AdminService.h"

#include <utility>


AdminService::AdminService(string identifier, vector<Station *> stations, vector < Service > serviceTeams) : Service(std::move(identifier), std::move(stations)){
    this->serviceTeams = std::move(serviceTeams);
}


void AdminService::assignStation(Station station, Service serviceCrew) {
    serviceCrew.supportedStations.push_back(&station);
}
