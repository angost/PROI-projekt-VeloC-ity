//
// Created by Adrian Murawski on 04/06/2023.
//

#ifndef PROI_PROJEKT_USERINTERFACE_H
#define PROI_PROJEKT_USERINTERFACE_H

#include "src/user/User.h"
#include "src/user/StandardUser.h"
#include "src/user/SilverUser.h"
#include "src/user/GoldenUser.h"
#include "src/station/station/LocalStation.h"
#include "src/Velocity.h"


class UserInterface {
public:
    User* user;
    vector<Station*> stations;
    vector<Location> locations;
    Velocity velocity;
    UserInterface(vector<Station*> stations, vector<Location> locations, User* user);

    void mainInterface();
    int getAction();
    Station* getStation();
    Vehicle* getVehicle(Station* station);
    Vehicle* getVehicle(vector<Vehicle*>* vehicles);
    float getAmount();
    int getCoord(string coord_type);
    string getDrivingLicence();

    void printSuccess(bool success);
    void printAllStations();
    void printVehiclesInStation(Station* station);
    void printBalance();
    void printRentedVehicles();
    void printReservedVehicles();

    bool addDrivingLicence(string drivingLicense);
    bool rentVehicle(Vehicle* vehicle, Station* station);
    bool reserveVehicle(Vehicle* vehicle, Station* station);
    bool returnVehicle(Vehicle* vehicle, Station* station);
    bool addCredits(float amount);
    bool cancelReservation(Vehicle* vehicle, Station* station);
    void printNearestStation();
    void printDistanceToAllStations();
};


#endif //PROI_PROJEKT_USERINTERFACE_H
