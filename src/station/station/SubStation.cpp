//
// Created by Adrian Murawski on 17/05/2023.
//

#include "SubStation.h"
#include <iostream>
#include <utility>

SubStation::SubStation() : Station("", "", Location(), vector < Vehicle* > (), 25, 0) {
    this->type = "B";
    this->vendingMachine = true;
}


SubStation::SubStation(string name, string code, Location location, vector<Vehicle *> currentVehicles, int maxVehicles,
                       int numberOfRentals) : Station(std::move(name), std::move(code), std::move(location), std::move(currentVehicles), maxVehicles, numberOfRentals){
    this->type = "B";
    this->vendingMachine = true;
}

void SubStation::getDesc() {
    cout << "Station type: " << this->type << endl;
    cout << "Vending machine on the left" << endl;
}