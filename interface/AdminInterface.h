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
    AdminInterface(AdminService &adminService, DataParser &data);
    void mainInterface();

    void displayStationAssignment();
    void displayStations();


    static int getAction();
    Station* getStation();
    Service& getServiceCrew();
    Station* getNewStation();
    static Location getLocation(const vector < Location >& existingLocations, int x, int y);

    bool checkNewStation(Station* station);

    friend class ServiceInterface;
};


#endif //PROI_PROJEKT_ADMININTERFACE_H
