#ifndef PROI_VETURILO_SCOOTER_H
#define PROI_VETURILO_SCOOTER_H

#include "Vehicle.h"

class Scooter : public Vehicle {
public:
    bool foldable;
    Scooter(int id, int numberOfRentals = 0, int technicalCondition = 5);
    ~Scooter() override = default;
    void takeOff() override;
};


#endif //PROI_VETURILO_SCOOTER_H