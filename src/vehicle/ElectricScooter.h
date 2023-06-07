#ifndef PROI_VETURILO_ELECTRICSCOOTER_H
#define PROI_VETURILO_ELECTRICSCOOTER_H

#include "Scooter.h"

class ElectricScooter : public Scooter {
public:
    int batteryLevel;
    bool charged;
    ElectricScooter(int id, int numberOfRentals = 0, int technicalCondition = 5, int batteryLevel = 100, bool charged = true);
    ~ElectricScooter() override = default;
    void takeOff() override;
};


#endif //PROI_VETURILO_ELECTRICSCOOTER_H