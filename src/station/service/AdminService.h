//
// Created by Adrian Murawski on 17/05/2023.
//

#ifndef PROI_PROJEKT_ADMINSERVICE_H
#define PROI_PROJEKT_ADMINSERVICE_H

#include <utility>
#include "Service.h"


class AdminService : public Service {
public:
    vector < Service > serviceTeams;
    vector < Station* > stations;
    AdminService();
    AdminService(string identifier, vector < Service > &serviceTeams, vector < Station * > &allStations, vector < Location > locations);
    void displayStationAssignment();
    void displayStations();
    static void displayStationInfo(Station* station);

    static bool assignStation(Station* station, Service& serviceCrew);
    void unassignRemovedStation(Station* station);

    bool removeExistingStation(Station* station);
    bool addNewStation(Station* newStation);

    friend class AdminInterface;
};


#endif //PROI_PROJEKT_ADMINSERVICE_H
