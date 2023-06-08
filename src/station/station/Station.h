//
// Created by Adrian Murawski on 23/04/2023.
//

#ifndef PROI_VETURILO_STATION_H
#define PROI_VETURILO_STATION_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>

#include "src/vehicle/Vehicle.h"
#include "src/vehicle/Bike.h"
#include "src/vehicle/Scooter.h"
#include "src/vehicle/ElectricScooter.h"
#include "src/Location.h"


using namespace std;


class Station {
private:
    Location location;
public:
    int numberOfRentals;
    string name;
    string code;
    string type;
    int maxVehiclesNumber;
    vector < Vehicle* > currentVehicles;

    Station(string name, string code, Location location, vector < Vehicle* > currentVehicles, int maxVehicles = 10, int numberOfRentals = 0);
    virtual ~Station() = default;
    bool addToStation(Vehicle* vehicle);
    bool deleteVehicle(Vehicle* vehicle);
    bool deleteVehicleByIndex(int index);
    bool changeLimit(int newLimit);
    void incrementCounter();
    bool changeLocation(Location newLocation);
    int countAvailableSpots() const;
    bool checkIfSpaceAvailable() const;
    bool checkIfVehicleInStation(Vehicle* veh);
    void printVehiclesInStation();
    virtual void getDesc() = 0;
    Location getStationLocation();
    bool operator==(Station* other) const;
    friend ostream& operator<<(ostream &out, const Station &station);
    friend istream& operator>>(istream &stream, Station &station);
    vector< Vehicle* >::iterator begin();
    vector< Vehicle* >::iterator end();
};


#endif //PROI_VETURILO_STATION_H
