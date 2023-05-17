#include "vehicle/Vehicle.h"
#include "vehicle/Bike.h"
#include "vehicle/Scooter.h"
#include "vehicle/ElectricScooter.h"

#include "station/station/MainStation.h"
#include "station/station/SubStation.h"
#include "station/station/LocalStation.h"

#include "station/service/Service.h"
#include "station/service/AdminService.h"

#include "Location.h"
#include <iostream>
#include <vector>
using namespace std;

void testStationService() {
    // MainStation
    vector<Vehicle *> vec;
    MainStation myMainStation("testname", "A01", Location("Warsaw", "Mokotow", "Ogrodowa", "1A", 0, 10), vec);
    myMainStation.getDesc();
    Bike bike(1);
    Scooter scooter(2);
    myMainStation.addToStation(&bike);
    myMainStation.addToStation(&scooter);
    for (auto i: myMainStation) {
        cout << i->id << endl;
    }
    cout << "Repair station: " << myMainStation.repairStation << endl;
    cout << "Wheel pump: " << myMainStation.wheelPump << endl;

    cout << endl;
    // SubStation
    vector<Vehicle *> vecSub;
    SubStation mySubStation("testnameSub", "B01", Location("Warsaw", "Mokotow", "Ogrodowa", "1B", 0, 20), vecSub);
    mySubStation.getDesc();
    Bike bikeSub(3);
    Scooter scooterSub(4);
    mySubStation.addToStation(&bikeSub);
    mySubStation.addToStation(&scooterSub);
    for (auto i: mySubStation) {
        cout << i->id << endl;
    }
    cout << "Vending machine: " << mySubStation.vendingMachine << endl;

    cout << endl;
    // LocalStation
    vector<Vehicle *> vecLocal;
    LocalStation myLocalStation("testnameLoc", "C01", Location("Warsaw", "Mokotow", "Ogrodowa", "1C", 0, 30), vecLocal);
    myLocalStation.getDesc();
    Bike bikeLocal(5);
    Scooter scooterLocal(6);
    myLocalStation.addToStation(&bikeLocal);
    myLocalStation.addToStation(&scooterLocal);
    for (auto i: myLocalStation) {
        cout << i->id << endl;
    }
    cout << "Emergency phone: " << myLocalStation.emergencyPhone << endl;

    cout << endl;
    // -----------------------
    // Service
    vector < Station* > stations = {&myMainStation, &mySubStation, &myLocalStation};
    Service serviceTeam("X01", stations);
    cout << "Service team id: " << serviceTeam.identifier << endl;

    cout << endl;
    // AdminService
    vector < Service > teams = {serviceTeam};
    AdminService admin("S01", stations, teams);
    cout << "Admin id: " << admin.identifier << endl;
    for (auto i : admin){
        cout << i->code << endl;
    }
}

void print(Vehicle* vehicle)
{
	cout << vehicle->id << endl;
}

int main() {

    testStationService();

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
