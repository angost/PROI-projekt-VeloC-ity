#ifndef PROI_PROJEKT_GOLDUSER_H
#define PROI_PROJEKT_GOLDUSER_H

#include "User.h"

class GoldenUser: public User{
public:
    string type;
    bool premiumAccess;
    GoldenUser(string username = "NoUser", Location userLocation = Location(), int maxResVehicles = 5, int maxRentedVehicles = 5, int discount = 5);
    void accountStats();
    void addDrivingLicense(string drivingLicense);
};


#endif //PROI_PROJEKT_GOLDUSER_H
