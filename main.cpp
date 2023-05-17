#include "vehicle/Vehicle.h"
#include "vehicle/Bike.h"
#include "vehicle/Scooter.h"
#include "vehicle/ElectricScooter.h"

#include "station/station/Station.h"
#include "station/station/MainStation.h"

#include "Location.h"
#include <iostream>
#include <vector>
using namespace std;


void testInhStation(){
    vector < Vehicle* > vec;
    MainStation myMainStation("testname", "A01", Location("Warsaw", "Mokotow", "Ogrodowa", "1B", 0, 10), vec);
    myMainStation.getDesc();
    Bike bike(1);
    Scooter scooter(2);
    myMainStation.addToStation(&bike);
    myMainStation.addToStation(&scooter);
    for (auto i : myMainStation){
        cout << i->id << endl;
    }
}


void print(Vehicle* vehicle)
{
	cout << vehicle->id << endl;
}

int main() {

    testInhStation();

//	Bike bike0(0);
//	print(&bike0);
//	Scooter scooter1(1);
//
//	vector<Vehicle*> rentedVehicles;
//	rentedVehicles.push_back(&bike0);
//	rentedVehicles.push_back(&scooter1);
//
//	cout << endl;


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
