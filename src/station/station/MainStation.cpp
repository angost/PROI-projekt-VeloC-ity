//
// Created by Adrian Murawski on 17/05/2023.
//
#include "MainStation.h"


MainStation::MainStation() : Station("", "", Location(), vector < Vehicle* > (), 50, 0){
    this->type = "MainStation";
    this->wheelPump = true;
    this->repairStation = true;
}


MainStation::MainStation(string name, string code, Location location, vector<Vehicle *> currentVehicles,
                         int maxVehicles, int numberOfRentals) : Station(std::move(name), std::move(code), std::move(location), std::move(currentVehicles), maxVehicles, numberOfRentals) {
    this->type = "MainStation";
    this->wheelPump = true;
    this->repairStation = true;
}

void MainStation::getDesc() {
    cout << "Station type: " << this->type << endl;
    cout << "Repair station and wheel pump are on the right" << endl;
}
