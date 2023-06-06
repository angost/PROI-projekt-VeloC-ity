#ifndef PROI_VETURILO_BIKE_H
#define PROI_VETURILO_BIKE_H

#include "Vehicle.h"

class Bike: public Vehicle {
public:
    bool hasBasket;
    Bike(int id, int numberOfRentals = 0, int technicalCondition = 5);
    ~Bike() override = default;
    void takeOff() override;
};


#endif //PROI_VETURILO_BIKE_H