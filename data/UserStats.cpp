//
// Created by k3acp on 06.06.2023.
//

#include "UserStats.h"

//UserStats::UserStats(string username, string userClass, int vehicleCounter, float balance, string drivingLicense, vector <Vehicle*> &reservedVehicles, vector <Vehicle*> &rentedVehicles) :
//    username(username), userClass(userClass), vehicleCounter(vehicleCounter), balance(balance), drivingLicense(drivingLicense), reservedVehicles(reservedVehicles), rentedVehicles(rentedVehicles) {}

UserStats::UserStats(string username, string userClass, int vehicleCounter, float balance, string drivingLicense, map<int, string> reservedVehicles, vector <int> rentedVehiclesIds, int x_position, int y_position) :
        username(username), userClass(userClass), vehicleCounter(vehicleCounter), balance(balance), drivingLicense(drivingLicense), reservedVehicles(reservedVehicles), rentedVehiclesIds(rentedVehiclesIds), x_position(x_position), y_position(y_position) {}