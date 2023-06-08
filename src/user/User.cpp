#include "User.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>

User::User(string username, Location loc, int maxResVehicles, int maxRentedVehicles, int discount) {
	this->username = username;
    this->type = "";
    this->maxResVehicles = maxResVehicles;
    this->maxRentedVehicles = maxRentedVehicles;
    this->discount = discount;
    drivingLicense = "None";
	balance = 0;
	minBalance = 10;
	vehicleCounter = 0;
    userLocation = loc;
}

bool User::checkSolvency() {
	if (minBalance <= balance) {
		return true;
	}
	return false;
}

float User::checkBalance(){
    return balance;
}

float User::checkMinBalance(){
    return minBalance;
}

void User::withdraw(float amount) {
	balance -= (amount - (amount * discount / 100));
}

void User::makeDeposit(float amount) {
	balance += amount;
}

void User::addVehicle(Vehicle* vehicle) {
	rentedVehicles.push_back(vehicle);
}

void User::removeVehicle(Vehicle* vehicle) {
	rentedVehicles.erase(std::remove(rentedVehicles.begin(), rentedVehicles.end(), vehicle), rentedVehicles.end());
}

void User::reserveVehicle(Vehicle* vehicle, Station* vehicleStation) {
    reservedVehicles[vehicle] = vehicleStation;
}

void User::cancelReserveVehicle(Vehicle* vehicle) {
    reservedVehicles.erase(vehicle);
}

bool User::checkRented(Vehicle* vehicle) {
	auto checkVehicle = find(rentedVehicles.begin(), rentedVehicles.end(), vehicle);
	if (checkVehicle != rentedVehicles.end()) {
		return true;
	}
	return false;
}

bool User::checkReserved(Vehicle* vehicle) {
	if (reservedVehicles.find(vehicle) != reservedVehicles.end()) {
		return true;
	}
	return false;
}

bool User::checkRentSpace() {
	if (maxRentedVehicles > rentedVehicles.size()) {
		return true;
	}
	return false;
}

bool User::checkReserveSpace() {
	if (maxResVehicles > (reservedVehicles.size() + rentedVehicles.size())) {
		return true;
	}
	return false;
}

Location User::getLocation() {
    return userLocation;
}

bool User::changeLocation(Location newLocation) {
    this->userLocation = newLocation;
    return true;
}

void User::increaseVehicleCounter() {
    vehicleCounter++;
}

vector< Vehicle* > User::getRentedVehicles(){
    return rentedVehicles;
}

map <Vehicle*, Station*> User::getReservedVehicles(){
    return reservedVehicles;
}

//
//template <typename V, typename T>
//void User::print(V value, T text){
//    cout << text << value << endl;
//}