//
// Created by k3acp on 06.06.2023.
//

#include <string>

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
    UserStats(string username, string userClass, int vehicleCounter, float balance, string drivingLicense);
};


#endif //PROI_PROJEKT_USERARGS_H