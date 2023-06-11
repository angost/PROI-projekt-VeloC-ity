//
// Created by Adrian Murawski on 01/05/2023.
//

#ifndef PROI_VETURILO_SERVICE_H
#define PROI_VETURILO_SERVICE_H


#include <iostream>
#include <utility>
#include "src/station/station/Station.h"
#include "src/vehicle/Vehicle.h"

class Service {
    vector < Station* > supportedStations;
    vector < Station* > allStations;
    vector < Location > locations;
    static bool moveVehicle(Vehicle* vehicle, Station* fromStation, Station* toStation);
    static bool repairVehicle(Vehicle* vehicle);
    static bool checkVehicleCanBeMoved(Vehicle* veh, Station* fromStation, Station* toStation);
    static bool changeStationLimit(int newLimit, Station* station);
    void printSupportedStations();
    static void printVehiclesInStation(Station* station);
    static bool changeStationLocation(Station* station, Location newLocation);
    static bool addVehicle(Station* station, Vehicle* vehicle);
    static bool removeVehicle(Station* station, Vehicle* vehicle);
    friend class ServiceInterface;
    friend class AdminService;
    friend class AdminInterface;
public:
    Service();
    Service(string id, vector < Station* > &stations, vector < Station* > &allStations, vector < Location > locations);
    Service(string id, vector < Station* > &allStations, vector < Location > locations);
    string identifier;
    vector< Station* >::iterator begin();
    vector< Station* >::iterator end();
};


#endif //PROI_VETURILO_SERVICE_H
