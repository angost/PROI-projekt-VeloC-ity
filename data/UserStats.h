//
// Created by k3acp on 06.06.2023.
//

#include <string>
#include <vector>
#include "src/vehicle/Vehicle.h"

using namespace std;

#ifndef PROI_PROJEKT_USERARGS_H
#define PROI_PROJEKT_USERARGS_H


class UserStats {
public:
    string userClass;
    int vehicleCounter;
    float balance;
    string drivingLicense;
    string username;
//    vector <Vehicle*> &reservedVehicles;
//    vector <Vehicle*> &rentedVehicles;

//    UserStats(string username, string userClass, int vehicleCounter, float balance, string drivingLicense, vector <Vehicle*> &reservedVehicles, vector <Vehicle*> &rentedVehicles);
    UserStats(string username, string userClass, int vehicleCounter, float balance, string drivingLicense);

};


#endif //PROI_PROJEKT_USERARGS_H
