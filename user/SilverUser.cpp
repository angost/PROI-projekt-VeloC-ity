#include "SilverUser.h"
#include <iostream>

SilverUser::SilverUser(string username, Location loc, int maxResVehicles, int maxRentedVehicles, int discount) : User(username, loc, maxResVehicles, maxRentedVehicles, discount){
    type = "Silver";
    premiumAccess = true;
}

void SilverUser::accountStats() {
    cout << "Your account type: " << this->type << endl;
    cout << "Vehicles rented: " << this->vehicleCounter << endl;
    cout << "Your Balance: " << this->balance << endl;
    cout << "You have premium access!" << endl;
}