#ifndef PROI_PROJEKT_STANDARDUSER_H
#define PROI_PROJEKT_STANDARDUSER_H

#include "User.h"

class StandardUser: public User{
public:
    StandardUser(string username = "NoUser", Location userLocation = Location(), int maxResVehicles = 3, int maxRentedVehicles = 3, int discount = 0);
    void accountStats();
};


#endif //PROI_PROJEKT_STANDARDUSER_H
