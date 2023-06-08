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

#include "data/DataParser.h"


class AdminInterface {
    AdminService adminService;
    DataParser data;
public:
    AdminInterface(AdminService adminService, DataParser &data);
    void mainInterface();
    static int getAction();
    Station* getStation();
    Service& getServiceCrew();
    void displayStationAssignment();
    void displayStations();
    Station* getNewStation();
    static Location getLocation(const vector < Location >& existingLocations, int x, int y);
    bool addNewStation(Station* newStation);
    bool removeExistingStation(Station* station);
    void unassignRemovedStation(Station* station);
    static bool assignStation(Station* station, Service& serviceTeam);
    friend class ServiceInterface;
};


#endif //PROI_PROJEKT_ADMININTERFACE_H
