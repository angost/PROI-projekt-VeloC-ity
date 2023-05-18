#include "StandardUser.h"
#include <iostream>

StandardUser::StandardUser(string username, int maxResVehicles, int maxRentedVehicles, int discount){
    type = "Standard";

}

void StandardUser::accountStats() {
    cout << "Your account type: " << this->type << endl;
    cout << "Vehicles rented: " << this->vehicleCounter << endl;
    cout << "Your Balance: " << this->balance << endl;
}