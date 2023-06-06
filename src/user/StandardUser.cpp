#include "StandardUser.h"
#include <iostream>

StandardUser::StandardUser(string username, Location loc, int maxResVehicles, int maxRentedVehicles, int discount) : User(username, loc, maxResVehicles, maxRentedVehicles, discount){
    type = "Standard";
}

void StandardUser::accountStats() {
    cout << "Your account type: " << this->type << endl;
    cout << "Total Vehicles rented: " << this->vehicleCounter << endl;
    cout << "Your Balance: " << this->balance << endl;
    cout << "Limit of rented Vehicles: " << this->maxRentedVehicles << endl;
    cout << "Limit of reserved Vehicles: " << this->maxResVehicles << endl;
}