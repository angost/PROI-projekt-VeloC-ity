
#include "Vehicle.h"

using namespace std;

Vehicle::Vehicle(int id, int numberOfRentals, int technicalCondition)
{
	if (id < 0)
		throw invalid_argument("Id cannot be negative");
	this->id = id;

	rentalPrice = 5;
	maxSpeed = 5;
	rented = false;
	reserved = false;

	if (numberOfRentals < 0)
		throw invalid_argument("Number of rentals cannot be negative");
	this->numberOfRentals = numberOfRentals;

	// technicalCondition od 0 do 5, gdy spadnie do 0 jest unable to use
	if (technicalCondition < 0 || technicalCondition > 5)
		throw invalid_argument("Technical condition has to be between 0 and 5");
	this->technicalCondition = technicalCondition;

	if (technicalCondition == 0)
		ableToUse = false;
	else
		ableToUse = true;
}

void Vehicle::setRentedStatus(bool newStatus)
{
	this->rentedStatus = newStatus;
}

void Vehicle::setReservedStatus(bool newStatus)
{
	this->reservedStatus = newStatus;
}

void Vehicle::increaseNumberOfRentals()
{
	this->numberOfRentals++;
}

void Vehicle::setTechnicalCondition(int technicalCondition)
{
	if (technicalCondition < 0 || technicalCondition > 5)
		throw invalid_argument("Technical condition has to be between 0 and 5");
	this->technicalCondition = technicalCondition;
	if (technicalCondition == 0)
		ableToUse = false;
	else
		ableToUse = true;
}

bool Vehicle::checkRentedStatus()
{
	return this->rentedStatus;
}

bool Vehicle::checkReservedStatus()
{
	return this->reservedStatus;
}

int Vehicle::checkTechnicalCondition()
{
	return this->technicalCondition;
}

bool Vehicle::checkAbleToUse()
{
	return this->ableToUse;
}
