
#include "Vehicle.h"
#include "Bike.h"
#include "Scooter.h"
#include "ElectricScooter.h"
#include <iostream>
#include <vector>
using namespace std;


void print(Vehicle* vehicle)
{
	cout << vehicle->id << endl;
}

int main() {

	Bike bike0(0);
	print(&bike0);
	Scooter scooter1(1);

	vector<Vehicle*> rentedVehicles;
	rentedVehicles.push_back(&bike0);
	rentedVehicles.push_back(&scooter1);
	
	cout << endl;


	/*
	cout << "Bike" << endl;
	Bike bike0(0);
	cout << bike0.checkRentedStatus() << endl;
	bike0.setRentedStatus(true);
	cout << bike0.checkRentedStatus() << endl;
	bike0.takeOff();


	cout << endl << "Scooter" << endl;
	Scooter scooter1(1);
	cout << scooter1.checkRentedStatus() << endl;
	scooter1.setRentedStatus(true);
	cout << scooter1.checkRentedStatus() << endl;
	scooter1.takeOff();
	*/
	return 0;
}
