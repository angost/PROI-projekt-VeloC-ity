//
// Created by Adrian Murawski on 17/05/2023.
//

#include "AdminService.h"


AdminService::AdminService(string identifier, vector<Station *> stations) : Service(identifier, stations){}


void AdminService::assignStation(Station station, Service serviceCrew) {
    serviceCrew.supportedStations.push_back(&station);
}
