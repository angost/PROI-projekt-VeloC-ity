#pragma once

#ifndef PROI_VETURILO_USER_H
#define PROI_VETURILO_USER_H

#include <string>
#include <vector>
#include "src/vehicle/Vehicle.h"
#include "src/station/station/Station.h"
#include "src/Location.h"

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
    Location userLocation;
    string type;

	User(string username = "NoUser", Location userLocation = Location(), int maxResVehicles = 3, int maxRentedVehicles = 3, int discount = 0);
	bool checkSolvency();
    float checkBalance();
    float checkMinBalance();
	void withdraw(float amount);
	void makeDeposit(float amount);
	void addVehicle(Vehicle* vehicle);
	void removeVehicle(Vehicle* vehicle);
	void reserveVehicle(Vehicle* vehicle);
	void cancelReserveVehicle(Vehicle* vehicle);
	bool checkRented(Vehicle* vehicle);
	bool checkReserved(Vehicle* vehicle);
	bool checkRentSpace();
	bool checkReserveSpace();
    void increaseVehicleCounter();
    Location getLocation();
    bool changeLocation(Location newLocation);
    virtual void accountStats() = 0;
    vector< Vehicle* > getRentedVehicles();
    vector< Vehicle* > getReservedVehicles();
//    template <typename V, typename T>
//    void print(V value, T text);
};

#endif //PROI_VETURILO_USER_H