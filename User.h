#pragma once

#ifndef PROI_VETURILO_USER_H
#define PROI_VETURILO_USER_H

#include <string>
#include <vector>
#include "vehicle/Vehicle.h"
#include "station/Station.h"

using namespace std;

class User {
private:
	string username;
	float balance;
	float minBalance;
	string drivingLicense;
	vector <Vehicle*> reservedVehicles;
	vector <Vehicle*> rentedVehicles;
	int vehicleCounter;
	int maxResVehicles;
	int maxRentedVehicles;


public:
	User(string username = "NoUser", string driving_license = "None");
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
    void addDrivingLicense(string drivingLicense);
};

#endif //PROI_VETURILO_USER_H