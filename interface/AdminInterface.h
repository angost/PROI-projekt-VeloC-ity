//
// Created by Adrian Murawski on 06/06/2023.
//

#ifndef PROI_PROJEKT_ADMININTERFACE_H
#define PROI_PROJEKT_ADMININTERFACE_H

#include "src/station/service/AdminService.h"
#include "interface/ServiceInterface.h"

#include "src/station/station/Station.h"
#include "src/station/station/MainStation.h"
#include "src/station/station/SubStation.h"
#include "src/station/station/LocalStation.h"



class AdminInterface {
    AdminService admin;
public:
    explicit AdminInterface(AdminService admin);
    void mainInterface();
    static int getAction();
    Station* getStation();
    Service& getServiceCrew();
    void displayStationAssignment();
    void displayStations();
    Station* getNewStation();
    Location getLocation(const vector < Location >& existingLocations, int x, int y);
    bool addNewStation(Station* newStation);
    bool removeExistingStation(Station* station);
    void unassignRemovedStation(Station* station);
    static bool assignStation(Station* station, Service& serviceTeam);
};


#endif //PROI_PROJEKT_ADMININTERFACE_H
