//
// Created by Adrian Murawski on 23/04/2023.
//

#ifndef PROI_VETURILO_STATION_H
#define PROI_VETURILO_STATION_H

#include <vector>
#include <string>

#include "src/Location.h"
#include "src/vehicle/Vehicle.h"

using namespace std;


class Station {
private:
    int numberOfRentals;
    Location location;
    int maxVehiclesNumber;
public:
    string name;
    string code;
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
