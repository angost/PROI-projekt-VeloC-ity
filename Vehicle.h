#ifndef PROI_VETURILO_VEHICLE_H
#define PROI_VETURILO_VEHICLE_H

using namespace std;

#include "Location.h"
#include "User.h"

class Vehicle {
private:
    int id;
    float rentalPrice;
    int maxSpeed;
    bool rentedStatus;
    bool reservedStatus;
    User currentUser;
    Station currentStation;
    Location currentLocation;
    int numberOfRentals;
    int technicalCondition;
    bool ableToUse;

public:
    Vehicle(int id, Station currentStation, Location currentLocation, int numberOfRentals = 0, int technicalCondition = 5);
    // co jak aktualnie nie ma usera? obiekt User reprezentuj¹cy no user?
    void setRentedStatus(bool newStatus);
    void setReservedStatus(bool newStatus);
    void setUser(User user);
    void removeUser();
    void setStation(Station station);
    void removeStation();
    void setLocation(Location location);
    void increaseNumberOfRentals();
    void setTechnicalCondition(int technicalCondition);
    bool reserveVehicle(User user);
    bool cancelReserveVehicle(User user);
    bool rentVehicle(User user);
    bool returnVehicle(Station station);
    // robic gettery czy nie?
    // ktore void ktore bool, gdzie potrzebujemy info zwrotne czy sie udalo?
};


#endif //PROI_VETURILO_VEHICLE_H
