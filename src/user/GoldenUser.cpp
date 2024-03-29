#include "GoldenUser.h"
#include <iostream>

GoldenUser::GoldenUser(string username, Location loc, int maxResVehicles, int maxRentedVehicles, int discount) : User(username, loc, maxResVehicles, maxRentedVehicles, discount){
    type = "Golden";
    premiumAccess = true;
}

void GoldenUser::accountStats() {
    cout << "Your account type: " << this->type << endl;
    cout << "Total Vehicles rented: " << this->vehicleCounter << endl;
    cout << "Your Balance: " << this->balance << endl;
    cout << "You have premium access!" << endl;
    cout << "Limit of rented Vehicles: " << this->maxRentedVehicles << endl;
    cout << "Limit of reserved Vehicles: " << this->maxResVehicles << endl;
    if (this->drivingLicense == "None"){
        cout << "You can add your driving license." << endl;
    }
    else {
        cout << "You can rent motor engine vehicles!" << endl;
    }
}


void GoldenUser::addDrivingLicense(string drivingLicense) {
    this->drivingLicense = drivingLicense;
}