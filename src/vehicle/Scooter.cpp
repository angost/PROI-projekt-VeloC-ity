
#include "Scooter.h"
#include "Vehicle.h"
#include <iostream>
using namespace std;

Scooter::Scooter(int id, int numberOfRentals, int technicalCondition) : Vehicle(id, numberOfRentals, technicalCondition)
{
	rentalPrice = 5;
	maxSpeed = 15;
    foldable = true;
}

void Scooter::takeOff()
{
	cout << "Velocity: 0" << endl;
	cout << "Start pushing off the ground with your foot..." << endl;
	cout << "Velocity: " << this->maxSpeed / 5 << endl;
}