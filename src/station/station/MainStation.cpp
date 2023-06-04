//
// Created by Adrian Murawski on 17/05/2023.
//
#include "MainStation.h"
#include <iostream>
#include <utility>

MainStation::MainStation(string name, string code, Location location, vector<Vehicle *> currentVehicles,
                         int maxVehicles, int numberOfRentals) : Station(std::move(name), std::move(code), std::move(location), std::move(currentVehicles), maxVehicles, numberOfRentals) {
    this->type = "A";
    this->wheelPump = true;
    this->repairStation = true;
}

void MainStation::getDesc() {
    cout << "Station type: " << this->type << endl;
    cout << "Repair station and wheel pump are on the right" << endl;
}
