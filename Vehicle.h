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
    int numberOfRentals;
    int technicalCondition;
    bool ableToUse;

public:
    Vehicle(int id, int numberOfRentals = 0, int technicalCondition = 5);
    void setRentedStatus(bool newStatus);
    void setReservedStatus(bool newStatus);
    void setTechnicalCondition(int technicalCondition);
    bool checkRentedStatus();
    bool checkReservedStatus();
    int checkTechnicalCondition();
    bool checkAbleToUse();
};


#endif //PROI_VETURILO_VEHICLE_H
