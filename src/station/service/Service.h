//
// Created by Adrian Murawski on 01/05/2023.
//

#ifndef PROI_VETURILO_SERVICE_H
#define PROI_VETURILO_SERVICE_H

#include "src/station/station/Station.h"
#include "src/vehicle/Vehicle.h"

class Service {
public:
    string identifier;
    vector < Station* > supportedStations;

    Service();
    Service(string id, vector < Station* > stations);
    static bool moveVehicle(Vehicle* vehicle, Station* fromStation, Station* toStation);
    static bool repairVehicle(Vehicle* vehicle);
    static bool checkVehicleCanBeMoved(Vehicle* veh, Station* fromStation, Station* toStation);
    static bool changeStationLimit(int newLimit, Station* station);
    void printSupportedStations();
    static void printVehiclesInStation(Station* station);
    static bool changeStationLocation(Station* station, Location newLocation);
    static bool addVehicle(Station* station, Vehicle* vehicle);
    static bool removeVehicle(Station* station, Vehicle* vehicle);
    vector< Station* >::iterator begin();
    vector< Station* >::iterator end();
};


#endif //PROI_VETURILO_SERVICE_H
