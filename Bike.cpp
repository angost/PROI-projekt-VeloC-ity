
#include "Bike.h"
using namespace std;

Bike::Bike(int id, int numberOfRentals, int technicalCondition) : Vehicle(id, numberOfRentals, technicalCondition)
{
	rentalPrice = 4;
	maxSpeed = 20;
	hasBasket = true;
}
