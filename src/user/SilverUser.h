#ifndef PROI_PROJEKT_SILVERUSER_H
#define PROI_PROJEKT_SILVERUSER_H

#include "User.h"

class SilverUser: public User{
public:
    bool premiumAccess;
    SilverUser(string username = "NoUser", Location userLocation = Location(), int maxResVehicles = 4, int maxRentedVehicles = 4, int discount = 3);
    void accountStats();
};


#endif //PROI_PROJEKT_SILVERUSER_H
