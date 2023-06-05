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

    void mainInterface();
    int getAction();
    Station* getStation();
    Vehicle* getVehicle(Station* station);
    float getAmount();
    void printSuccess(bool success);
    void printAllStations();
    void printVehiclesInStation(Station* station);
    void printBalance();

    bool rentVehicle(Vehicle* vehicle, Station* station);
    bool reserveVehicle(Vehicle* vehicle, Station* station);
    bool returnVehicle(Vehicle* vehicle, Station* station);
    bool addCredits(float amount);
    bool cancelReservation(Vehicle* vehicle, Station* station);
    Station* findNearestStation();
    map < int, vector < Station* > > calculateDistanceToAllStations();
};


#endif //PROI_PROJEKT_USERINTERFACE_H