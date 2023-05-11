#pragma once

#ifndef PROI_VETURILO_USER_H
#define PROI_VETURILO_USER_H

#include <string>
#include <vector>
#include "Vehicle.h"
#include "Station.h"

using namespace std;

class User {
private:
	string username;
	float balance;
	float minBalance;
	string drivingLicense;
	vector <Vehicle> reservedVehicles;
	vector <Vehicle> rentedVehicles;
	int vehicleCounter;
	int maxResVehicles;
	int maxRentedVehicles;


public:
	User(string username = "NoUser", string driving_license = "None");
	bool checkSolvency();
	void withdraw(float amount);
	void makeDeposit(float amount);
	void addVehicle(Vehicle);
	void removeVehicle(Vehicle);
	void reserveVehicle(Vehicle);
	void cancelReserveVehicle(Vehicle);
	bool checkAvailability(Vehicle);
	bool checkRented(Vehicle);
	bool checkReserved(Vehicle);
	bool checkRentSpace();
	bool checkReserveSpace();
};

#endif //PROI_VETURILO_USER_H