//
// Created by Adrian Murawski on 23/04/2023.
//

#ifndef PROI_VETURILO_STATION_H
#define PROI_VETURILO_STATION_H

#include <vector>
#include <string>

#include "Location.h"
#include "vehicle/Vehicle.h"

using namespace std;


class Station {
public:
    string name;
    string code;
    Location location;
    int maxVehiclesNumber;
    vector < Vehicle* > currentVehicles;
    int numberOfRentals;

    Station(string name, string code, Location location, vector < Vehicle* > currentVehicles, int maxVehicles = 10, int numberOfRentals = 0);
    bool addToStation(Vehicle* vehicle);
    bool deleteVehicle(Vehicle* vehicle);
    bool deleteVehicleByIndex(int index);
    bool changeLimit(int newLimit);
    void incrementCounter();
    bool changeLocation(Location newLocation);
    int countAvailableSpots() const;
    bool checkIfSpaceAvailable();
    bool checkIfVehicleInStation(Vehicle* veh);
    virtual void getDesc() = 0;
    bool operator==(Station* other) const;
    vector< Vehicle* >::iterator begin();
    vector< Vehicle* >::iterator end();
};


#endif //PROI_VETURILO_STATION_H
