//
// Created by Adrian Murawski on 17/05/2023.
//

#ifndef PROI_PROJEKT_MAINSTATION_H
#define PROI_PROJEKT_MAINSTATION_H

#include "Station.h"
#include <iostream>
#include <utility>

class MainStation : public Station {
public:
    bool wheelPump;
    bool repairStation;
    MainStation();
    MainStation(string name, string code, Location location, vector < Vehicle* > currentVehicles, int maxVehicles = 50, int numberOfRentals = 0);
    ~MainStation() override = default;
    void getDesc() override;
};


#endif //PROI_PROJEKT_MAINSTATION_H
