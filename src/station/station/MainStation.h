//
// Created by Adrian Murawski on 17/05/2023.
//

#ifndef PROI_PROJEKT_MAINSTATION_H
#define PROI_PROJEKT_MAINSTATION_H

#include "Station.h"

class MainStation : public Station {
public:
    string type;
    bool wheelPump;
    bool repairStation;
    MainStation();
    MainStation(string name, string code, Location location, vector < Vehicle* > currentVehicles, int maxVehicles = 50, int numberOfRentals = 0);
    ~MainStation() override = default;
    void getDesc();
};


#endif //PROI_PROJEKT_MAINSTATION_H
