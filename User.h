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
	bool checkSolvency(Vehicle);
	void withdraw(float amount);
	void makeDeposit(float amount);
	void addVehicle(Vehicle);
	void removeVehicle(Vehicle);
	void reserveVehicle(Vehicle);
	void cancelReserveVehicle(Vehicle);
	/*void vehicleReservation(Vehicle, Station);
	void rentVehicle(Vehicle, Station);
	void returnVehicle(Vehicle, Station);*/
	bool checkAvailability(Vehicle);
	bool checkRented(Vehicle);
	bool checkReserved(Vehicle);
};

#endif //PROI_VETURILO_USER_H