#ifndef PROI_VETURILO_VEHICLE_H
#define PROI_VETURILO_VEHICLE_H

#include <stdexcept>
#include <string>
using namespace std;

class Vehicle {
public:
    int id;
    float rentalPrice;
    int maxSpeed;
    bool rentedStatus;
    bool reservedStatus;
    int numberOfRentals;
    int technicalCondition;
    bool ableToUse;
    string type;
    Vehicle(int id, int numberOfRentals = 0, int technicalCondition = 5);
    virtual ~Vehicle() = default;
    void setRentedStatus(bool newStatus);
    void setReservedStatus(bool newStatus);
    void increaseNumberOfRentals();
    void setTechnicalCondition(int technicalCondition);
    bool checkRentedStatus();
    bool checkReservedStatus();
    int checkTechnicalCondition();
    bool checkAbleToUse();
    virtual void takeOff() = 0;
    bool operator==(Vehicle* other) const;
};


#endif //PROI_VETURILO_VEHICLE_H
