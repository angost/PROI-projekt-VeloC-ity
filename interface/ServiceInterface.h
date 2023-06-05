//
// Created by Adrian Murawski on 04/06/2023.
//

#ifndef PROI_PROJEKT_SERVICEINTERFACE_H
#define PROI_PROJEKT_SERVICEINTERFACE_H

#include <memory>
#include "src/station/service/Service.h"
#include "src/vehicle/Bike.h"
#include "src/vehicle/Scooter.h"
#include "src/vehicle/ElectricScooter.h"


class ServiceInterface {
public:
    Service serviceClass;
    explicit ServiceInterface(Service service);
    void mainInterface();
    static int getAction();
    void printSupportedStations();
    static void printVehiclesInStation(Station* station);
    static bool changeStationLimit(int newLimit, Station* station);
    static bool repairVehicle(Vehicle* vehicle);
    static bool moveVehicle(Vehicle* vehicle, Station* fromStation, Station* toStation);
    static void printSuccess(bool success);
    static bool changeStationLocation(Station* station, Location location);
    static bool addVehicle(Station* station, Vehicle* vehicle);
    static bool removeVehicle(Station* station, Vehicle* vehicle);
    Station* getStation();
    static Vehicle* getVehicle(Station* station);
    static Location getLocation();
    static std::shared_ptr<Vehicle> getNewVehicle();
};


#endif //PROI_PROJEKT_SERVICEINTERFACE_H
