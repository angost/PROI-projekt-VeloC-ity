
#include "ElectricScooter.h"
#include "Scooter.h"
#include <iostream>
using namespace std;

ElectricScooter::ElectricScooter(int id, int numberOfRentals, int technicalCondition, int batteryLevel, bool charged) : Scooter(id, numberOfRentals, technicalCondition)
{
	rentalPrice = 10;
	maxSpeed = 25;
	this->batteryLevel = batteryLevel;
	this->charged = charged;
}

void Scooter::takeOff()
{
	cout << "Velocity: 0" << endl;
	cout << "Turn the scooter on" << endl;
	cout << "Push gas button..." << endl;
	cout << "Velocity: " << this->maxSpeed / 2 << endl;
}