#include "StandardUser.h"
#include <iostream>

StandardUser::StandardUser(string username, Location loc, int maxResVehicles, int maxRentedVehicles, int discount) : User(username, loc, maxResVehicles, maxRentedVehicles, discount){
    type = "Standard";

}

void StandardUser::accountStats() {
//    print(this->type, "Your account type: ");
//    print(this->vehicleCounter, "Vehicles rented: ");
//    print(this->balance, "Your Balance: ");
}