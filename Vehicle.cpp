
#include "Vehicle.h"

using namespace std;

Vehicle::Vehicle(int id, float rentalPrice, int maxSpeed, Station currentStation, Location location, int numberOfRentals, int technicalCondition)
{
	if (id < 0)
		throw invalid_argument("Id cannot be negative");
	this->id = id;

	if (rentalPrice < 0)
		throw invalid_argument("Rental price cannot be negative");
	this->rentalPrice = rentalPrice;

	if (maxSpeed <= 0)
		throw invalid_argument("Max speed has to be greater than 0");
	this->maxSpeed = maxSpeed;

	// na poczatku nie powinno byc usera -> zrobic User None? -> empty constructor usera tworzy noUsera?
	User noUser();
	currentUser = noUser;
	//

	if (currentStation.countAvailableSpots() == 0)
		throw invalid_argument("No available spots on chosen station");
	this->currentStation = currentStation;

	this->location = location;

	rented = false;
	reserved = false;

	if (numberOfRentals < 0)
		throw invalid_argument("Number of rentals cannot be negative");
	this->numberOfRentals = numberOfRentals;

	// technicalCondition od 0 do 5, gdy spadnie do 0 jest unable to use ?
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

void Vehicle::setUser(User user)
{
	this->currentUser = user;
}

void Vehicle::removeUser()
{
	User noUser();
	this->currentUser = noUser;

}

void Vehicle::setStation(Station station)
{
	this->currentStation = station;
}

void Vehicle::removeStation()
{
	// znowu, co jak stacja pusta?
	Station noStation();
	this->currentStation = noStation;
}

void Vehicle::setLocation(Location location)
{
	this->location = location;
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

bool Vehicle::reserveVehicle(User user)
{
	// w Userze - sprawdzenie czy ma odpowiedni balance, czy nie ma pelnego limitu wypozyczonych pojazdow
	// w Userze/Vehicle - czy ten vehicle jest juz zarezerwowany/pozyczony
	this->setReservedStatus(true);
	this->setUser(user);
	//dodaj do zarezerwowanych pojazdow usera?
	return true;
}

bool Vehicle::cancelReserveVehicle(User user)
{
	// w Userze/Vehicle - czy ten vehicle jest zarezerwowany przez tego usera
	this->setReservedStatus(false);
	this->removeUser();
	//usun z zarezerwowanych pojazdow usera?
	return true;
}

bool Vehicle::rentVehicle(User user)
{
	// w Userze - sprawdzenie czy ma odpowiedni balance, czy jest na stacji takiej jak ten vehicle, czy vehicle nie jest zarezerwowany/jest przez tego usera
	// w Vehicle - zmiana statusu, zwiekszenie liczby wypozyczen, ustawienie uzytkownika, usuniecie ze stacji
	this->setRentedStatus(true);
	this->setReservedStatus(false);
	this->increaseNumberOfRentals();
	this->setUser(user);
	user.addVehicle(this);
	this->currentStation.deleteVehicle(this);
	return true;
}


bool Vehicle::returnVehicle(Station station)
{
	// w Userze - czy jest na stacji, czy na stacji sa miejsca
	// w Vehicle - zmien status, usun usera, dodaj do stacji
	this->setRentedStatus(false);
	this->removeUser();
	user.removeVehicle(this);
	this->currentStation = station;
	station.addToStation(this);
	return true;
}
