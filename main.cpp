
#include "Vehicle.h"
#include "Bike.h"
#include "Scooter.h"
#include "ElectricScooter.h"
#include "station/Station.h"
#include "Location.h"
#include <iostream>
#include <vector>
using namespace std;


void testStation(){
    string city = "Warsaw";
    string district = "Mokotow";
    string street = "Ogrodowa";
    string number = "1A";
    int x = 0;
    int y = 10;
    Location loc(city, district, street, number, x, y);
    vector < Vehicle* > vec;
    string name = "testname";
    string code = "A01";
    Station stat(name, code, loc, vec);

    Bike bike0(0);
    stat.addToStation(&bike0);
    cout << stat.countAvailableSpots() << endl;
}


void print(Vehicle* vehicle)
{
	cout << vehicle->id << endl;
}

int main() {

    testStation();

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
