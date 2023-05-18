#include "SilverUser.h"
#include <iostream>

SilverUser::SilverUser(string username, int maxResVehicles, int maxRentedVehicles, int discount){
    type = "Silver";
    premiumAccess = true;
}

void StandardUser::accountStats() {
    cout << "Your account type: " << this->type << endl;
    cout << "Vehicles rented: " << this->vehicleCounter << endl;
    cout << "Your Balance: " << this->balance << endl;
    cout << "You have premium access!" << endl;
}