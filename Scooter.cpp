
using namespace std;
#include "Scooter.h"
#include "Vehicle.h"

Scooter::Scooter(int id, int numberOfRentals, int technicalCondition) : Vehicle(id, numberOfRentals, technicalCondition)
{
	rentalPrice = 5;
	maxSpeed = 15;
}
