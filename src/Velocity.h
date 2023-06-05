//
// Created by Adrian Murawski on 21/05/2023.
//

#ifndef PROI_PROJEKT_VELOCITY_H
#define PROI_PROJEKT_VELOCITY_H

#include <vector>
#include <map>
#include "station/station/Station.h"
#include "user/User.h"
#include "user/StandardUser.h"
#include "vehicle/Vehicle.h"

class Velocity {
    vector < Station* > stations;
    User* user;
    Velocity();
    Velocity(vector <Station* > stations, User* user);
    bool rentVehicle(Vehicle* vehicle, Station* station);
    bool reserveVehicle(Vehicle* vehicle, Station* station);
    bool returnVehicle(Vehicle* vehicle, Station* station);
    bool addCredits(float amount);
    bool cancelReservation(Vehicle* vehicle, Station* station);
    Station* findNearestStation();
    map < int, vector < Station* > > calculateDistanceToAllStations();
    friend class UserInterface;
};


#endif //PROI_PROJEKT_VELOCITY_H
