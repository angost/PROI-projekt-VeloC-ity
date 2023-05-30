#ifndef PROI_VETURILO_BIKE_H
#define PROI_VETURILO_BIKE_H

using namespace std;
#include "Vehicle.h"

class Bike: public Vehicle {
public:
    bool hasBasket;
    Bike(int id, int numberOfRentals = 0, int technicalCondition = 5);
    void takeOff();
};


#endif //PROI_VETURILO_BIKE_H