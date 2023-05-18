#pragma once

#ifndef PROI_VETURILO_USER_H
#define PROI_VETURILO_USER_H

#include <string>
#include <vector>
#include "../vehicle/Vehicle.h"
#include "../station/Station.h"

using namespace std;

class User {
public:
	string username;
	float balance;
	float minBalance;
	string drivingLicense;
	vector <Vehicle*> reservedVehicles;
	vector <Vehicle*> rentedVehicles;
	int vehicleCounter;
	int maxResVehicles;
	int maxRentedVehicles;
    int discount;

	User(string username = "NoUser", int maxResVehicles = 3, int maxRentedVehicles = 3, int discount = 0);
	bool checkSolvency();
	void withdraw(float amount);
	void makeDeposit(float amount);
	void addVehicle(Vehicle* vehicle);
	void removeVehicle(Vehicle* vehicle);
	void reserveVehicle(Vehicle* vehicle);
	void cancelReserveVehicle(Vehicle* vehicle);
	bool checkAvailability(Vehicle* vehicle);
	bool checkRented(Vehicle* vehicle);
	bool checkReserved(Vehicle* vehicle);
	bool checkRentSpace();
	bool checkReserveSpace();
    void increaseVehicleCounter();
    virtual void accountStats() = 0;
};

#endif //PROI_VETURILO_USER_H