//
// Created by Adrian Murawski on 17/05/2023.
//

#ifndef PROI_PROJEKT_LOCALSTATION_H
#define PROI_PROJEKT_LOCALSTATION_H

#include <iostream>
#include <utility>
#include "Station.h"

class LocalStation : public Station{
public:
    bool emergencyPhone;
    LocalStation();
    LocalStation(string name, string code, Location location, vector < Vehicle* > currentVehicles, int maxVehicles = 5, int numberOfRentals = 0);
    ~LocalStation() override = default;
    void getDesc() override;
};


#endif //PROI_PROJEKT_LOCALSTATION_H
