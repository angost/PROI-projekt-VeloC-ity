//
// Created by Adrian Murawski on 17/05/2023.
//

#ifndef PROI_PROJEKT_LOCALSTATION_H
#define PROI_PROJEKT_LOCALSTATION_H

#include "Station.h"

class LocalStation : public Station{
public:
    string type;
    bool emergencyPhone;
    LocalStation(string name, string code, Location location, vector < Vehicle* > currentVehicles, int maxVehicles = 5, int numberOfRentals = 0);
    void getDesc();
};


#endif //PROI_PROJEKT_LOCALSTATION_H
