//
// Created by Adrian Murawski on 04/06/2023.
//

#ifndef PROI_PROJEKT_SERVICEINTERFACE_H
#define PROI_PROJEKT_SERVICEINTERFACE_H

#include <memory>
#include <iostream>
#include <utility>
#include "src/station/service/Service.h"
#include "src/vehicle/Bike.h"
#include "src/vehicle/Scooter.h"
#include "src/vehicle/ElectricScooter.h"

#include "data/DataParser.h"


class ServiceInterface {
public:
    Service serviceClass;
    DataParser data;
    ServiceInterface(Service service, DataParser &data);
    void mainInterface();
    static int getAction();
    void printSupportedStations();
    static void printVehiclesInStation(Station* station);
    static void printVehicleDetails(Vehicle* vehicle);
    static bool changeStationLimit(int newLimit, Station* station);
    static bool repairVehicle(Vehicle* vehicle);
    static bool moveVehicle(Vehicle* vehicle, Station* fromStation, Station* toStation);
    static void printSuccess(bool success);
    static bool changeStationLocation(Station* station, Location location);
    static bool addVehicle(Station* station, Vehicle* vehicle);
    static bool removeVehicle(Station* station, Vehicle* vehicle);
    Station* getStation();
    static Vehicle* getVehicle(Station* station);
    Location getLocation();
    Location getRealLocation(int x, int y);
    static Vehicle* getNewVehicle();
};


#endif //PROI_PROJEKT_SERVICEINTERFACE_H
