#ifndef PROI_PROJEKT_GOLDUSER_H
#define PROI_PROJEKT_GOLDUSER_H

#include "User.h"

class SilverUser: public User{
public:
    string type;
    bool premiumAccess;
    SilverUser(string username = "NoUser", int maxResVehicles = 5, int maxRentedVehicles = 5, int discount = 5);
    void accountStats();
    void addDrivingLicense(string drivingLicense);
};


#endif //PROI_PROJEKT_GOLDUSER_H
