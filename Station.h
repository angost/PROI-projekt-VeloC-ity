//
// Created by Adrian Murawski on 23/04/2023.
//

#ifndef PROI_VETURILO_STATION_H
#define PROI_VETURILO_STATION_H

#include <vector>
#include <string>

#include "Location.h"
#include "Vehicle.h"

using namespace std;


class Station {
private:
    string name;
    string code;
    Location location;
    int maxVehiclesNumber;
    vector < Vehicle > currentVehicles;
    int numberOfRentals;
public:
    Station(string name, string code, Location location, vector < Vehicle > currentVehicles, int maxVehicles = 10, int numberOfRentals = 0);
    bool addToStation(Vehicle vehicle);
    bool deleteVehicle(Vehicle vehicle);
    bool deleteVehicleByIndex(int index);
    bool changeLimit(int newLimit);
    void incrementCounter();
    bool changeLocation(Location newLocation);
};


#endif //PROI_VETURILO_STATION_H
