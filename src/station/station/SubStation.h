//
// Created by Adrian Murawski on 17/05/2023.
//

#ifndef PROI_PROJEKT_SUBSTATION_H
#define PROI_PROJEKT_SUBSTATION_H

#include <iostream>
#include <utility>
#include "Station.h"

class SubStation : public Station{
public:
    string type;
    bool vendingMachine;
    SubStation();
    SubStation(string name, string code, Location location, vector < Vehicle* > currentVehicles, int maxVehicles = 25, int numberOfRentals = 0);
    ~SubStation() override = default;
    void getDesc() override;
};


#endif //PROI_PROJEKT_SUBSTATION_H
