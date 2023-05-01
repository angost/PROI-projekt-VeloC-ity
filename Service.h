//
// Created by Adrian Murawski on 01/05/2023.
//

#ifndef PROI_VETURILO_SERVICE_H
#define PROI_VETURILO_SERVICE_H

#include "Station.h"
#include "Vehicle.h"

class Service {
private:
    vector < Station > supportedStations;
public:
    Service(vector < Station > stations);
    bool moveVehicle(Vehicle vehicle, Station fromStation, Station toStation);
    bool repairVehicle(Vehicle vehicle);
};


#endif //PROI_VETURILO_SERVICE_H
