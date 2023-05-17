//
// Created by Adrian Murawski on 17/05/2023.
//

#include "LocalStation.h"
#include <iostream>

LocalStation::LocalStation(string name, string code, Location location, vector<Vehicle *> currentVehicles,
                           int maxVehicles, int numberOfRentals) : Station(name, code, location, currentVehicles, maxVehicles, numberOfRentals) {
    this->type = "C";
    this->emergencyPhone = true;
}

void LocalStation::getDesc() {
    cout << "Station type: " << this->type << endl;
    cout << "Use emergency phone if needed" << endl;
}