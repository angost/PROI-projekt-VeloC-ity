#include "User.h"
#include <stdexcept>

User::User(string username, string drivingLicense) {
	this->username = username;
	this->drivingLicense = drivingLicense;
	balance = 0;
	minBalance = 10;
	vehicleCounter = 0;
	maxResVehicles = 3;
	maxRentedVehicles = 3;
}

bool User::checkSolvency() {
	if (minBalance <= balance) {
		return true;
	}
	return false;
}

void User::withdraw(float amount) {
	balance -= amount;
}

void User::makeDeposit(float amount) {
	balance += amount;
}

void User::addVehicle(Vehicle vehicle) {
	rentedVehicles.push_back(vehicle);
}

void User::removeVehicle(Vehicle vehicle) {
	rentedVehicles.erase(std::remove(rentedVehicles.begin(), rentedVehicles.end(), vehicle), rentedVehicles.end());
}

void User::reserveVehicle(Vehicle vehicle) {
	reservedVehicles.push_back(vehicle);
}

void User::cancelReserveVehicle(Vehicle vehicle) {
	reservedVehicles.erase(std::remove(reservedVehicles.begin(), reservedVehicles.end(), vehicle), reservedVehicles.end());
}

bool User::checkAvailability(Vehicle vehicle){
	if (!vehicle.checkRentedStatus() and !vehicle.checkReservedStatus()) {
		return true;
	}
	else if (checkReserved(vehicle)) {
		return true;
	}
	return false;
}

bool User::checkRented(Vehicle vehicle) {
	auto checkVehicle = find(rentedVehicles.begin(), rentedVehicles.end(), vehicle);
	if (checkVehicle != rentedVehicles.end()) {
		return true;
	}
	return false;
}

bool User::checkReserved(Vehicle vehicle) {
	auto checkVehicle = find(reservedVehicles.begin(), reservedVehicles.end(), vehicle);
	if (checkVehicle != reservedVehicles.end()) {
		return true;
	}
	return false;
}

bool User::checkRentSpace() {
	if (maxRentedVehicles < rentedVehicles.size()) {
		return true;
	}
	return false;
}

bool User::checkReserveSpace() {
	if (maxResVehicles < (reservedVehicles.size() + rentedVehicles.size())) {
		return true;
	}
	return false;
}

void User::increaseVehicleCounter() {
    vehicleCounter++;
}

void User::addDrivingLicense(std::string drivingLicense) {
    this->drivingLicense = drivingLicense;
}

