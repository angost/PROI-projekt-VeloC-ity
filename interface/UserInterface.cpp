//
// Created by Adrian Murawski on 04/06/2023.
//

#include "UserInterface.h"

UserInterface::UserInterface(vector<Station *> stations, User *user) : stations(stations), user(user) {
    Velocity vel(stations, user);
    this->velocity = vel;

}
