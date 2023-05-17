//
// Created by Adrian Murawski on 17/05/2023.
//

#include "SubStation.h"
#include <iostream>

SubStation::SubStation(string name, string code, Location location, vector<Vehicle *> currentVehicles, int maxVehicles,
                       int numberOfRentals) : Station(name, code, location, currentVehicles, maxVehicles, numberOfRentals){
    this->type = "B";
    this->vendingMachine = true;
}

void SubStation::getDesc() {
    cout << "Station type: " << this->type << endl;
    cout << "Vending machine on the left" << endl;
}