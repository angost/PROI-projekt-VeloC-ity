
using namespace std;
#include "ElectricScooter.h"
#include "Scooter.h"

ElectricScooter::ElectricScooter(int id, int numberOfRentals, int technicalCondition, int batteryLevel, bool charged) : Scooter(id, numberOfRentals, technicalCondition)
{
	rentalPrice = 10;
	maxSpeed = 25;
	this->batteryLevel = batteryLevel;
	this->charged = charged;
}
