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

bool User::checkSolvency(Vehicle vehicle) {
	if (vehicle.rentalPrice <= balance) {
		return true;
	}
	throw invalid_argument("You don't have enough money.");
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

/*void User::vehicleReservation(Vehicle vehicle, Station station) {
	if (reservedVehicles.size() < maxResVehicles) {
		auto checkVehicle = find(station.currentVehicles.begin(), station.currentVehicles.end(), vehicle);
		if (checkVehicle != station.currentVehicles.end()) {
			if (checkAvailability(vehicle) and checkSolvency(vehicle)) {

			}
		}
		else {
			throw invalid_argument("No vehicles like this in given station.");
		}
	}
}

void User::rentVehicle(Vehicle vehicle, Station station) {
	if (rentedVehicles.size() < maxRentedVehicles) {
		auto checkVehicle = find(station.currentVehicles.begin(), station.currentVehicles.end(), vehicle);
		if (checkVehicle != station.currentVehicles.end()) {
			if (checkAvailability(vehicle) and checkSolvency(vehicle)) {

			}
		}
		else {
			throw invalid_argument("No vehicles like this in given station.");
		}
	}
}

void User::returnVehicle(Vehicle vehicle, Station station) {
	
}*/

bool User::checkAvailability(Vehicle vehicle){
	if ((vehicle.rentedStatus == false) and (vehicle.reservedStatus == false)) {
		return true;
	}
	else if (checkReserved(vehicle)) {
		return true;
	}
	throw invalid_argument("This vehicle is already taken.");
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

