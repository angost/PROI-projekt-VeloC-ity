//
// Created by k3acp on 06.06.2023.
//

#include <string>
#include <vector>
#include <map>
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
    map<int, string> &reservedVehicles;
//    vector <Vehicle*> &reservedVehicles;
//    vector <Vehicle*> &rentedVehicles;

//    UserStats(string username, string userClass, int vehicleCounter, float balance, string drivingLicense, vector <Vehicle*> &reservedVehicles, vector <Vehicle*> &rentedVehicles);
    UserStats(string username, string userClass, int vehicleCounter, float balance, string drivingLicense, map<int, string> &reservedVehicles);

};


#endif //PROI_PROJEKT_USERARGS_H
