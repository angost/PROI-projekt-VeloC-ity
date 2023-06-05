
#include "Bike.h"
#include <iostream>
using namespace std;

Bike::Bike(int id, int numberOfRentals, int technicalCondition) : Vehicle(id, numberOfRentals, technicalCondition)
{
	rentalPrice = 4;
	maxSpeed = 20;
	hasBasket = true;
    type = "Bike";
}

void Bike::takeOff()
{
	cout << "Velocity: 0" << endl;
	cout << "Start pedaling..." << endl;
	cout << "Velocity: " << this->maxSpeed / 4 << endl;
}
