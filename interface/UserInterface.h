//
// Created by Adrian Murawski on 04/06/2023.
//

#ifndef PROI_PROJEKT_USERINTERFACE_H
#define PROI_PROJEKT_USERINTERFACE_H

#include "src/user/User.h"
#include "src/user/StandardUser.h"
#include "src/user/SilverUser.h"
#include "src/user/GoldenUser.h"
#include "src/Velocity.h"


class UserInterface {
public:
    User* user;
    vector<Station*> stations;
    Velocity velocity;
    UserInterface(vector<Station*> stations, User* user);
    


};


#endif //PROI_PROJEKT_USERINTERFACE_H
