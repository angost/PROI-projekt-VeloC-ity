//
// Created by Adrian Murawski on 04/06/2023.
//

#include "ServiceInterface.h"

#include <iostream>
#include <utility>

ServiceInterface::ServiceInterface(Service service) {
    this->serviceClass = std::move(service);
}


void ServiceInterface::mainInterface() {
    while (true){
        int option = getAction();
        if (option == 1) {
            printSupportedStations();
        } else if (option == 2){
            try {
                Station* station = getStation();
                printVehiclesInStation(station);
            }
            catch (invalid_argument) {
                cout << "Wrong code..." << endl;
                continue;
            }
        } else if (option == 3) {
            int newLimit;
            cout << "Enter new limit > ";
            cin >> newLimit;
            cout << endl;
            try {
                Station* station = getStation();
                bool success = changeStationLimit(newLimit, station);
                printSuccess(success);
            }
            catch (invalid_argument) {
                cout << "Wrong code..." << endl;
                continue;
            }
        } else if (option == 4) {
            cout << "First insert source station code, then vehicle id and finally destination station code" << endl;
            try {
                Station* fromStation = getStation();
                Vehicle* vehicle = getVehicle(fromStation);
                Station* toStation = getStation();
                bool success = moveVehicle(vehicle, fromStation, toStation);
                printSuccess(success);
            }
            catch (invalid_argument){
                cout << "Wrong data..." << endl;
                continue;
            }
        } else if (option == 5) {
            cout << "Insert station code and id of vehicle you want to repair..." << endl;
            try {
                Station* station = getStation();
                Vehicle* vehicle = getVehicle(station);
                bool success = repairVehicle(vehicle);
                printSuccess(success);
            }
            catch (invalid_argument) {
                cout << "Wrong data..." << endl;
                continue;
            }
        } else if (option == 6){
            try {
                Station* station = getStation();
                Location location = getLocation();
                bool success = changeStationLocation(station, location);
                printSuccess(success);
            }
            catch (invalid_argument) {
                cout << "Wrong data..." << endl;
                continue;
            }
        } else if (option == 7) {
            try {
                Station* station = getStation();
                shared_ptr<Vehicle> vehicleSharedPtr = getNewVehicle();
                Vehicle* vehicle = vehicleSharedPtr.get();
                bool success = addVehicle(station, vehicle);
                printSuccess(success);
            }
            catch (invalid_argument) {
                cout << "Wrong data..." << endl;
                continue;
            }
        } else if (option == 8) {
            try {
                Station* station = getStation();
                Vehicle* vehicle = getVehicle(station);
                bool success = removeVehicle(station, vehicle);
                printSuccess(success);
            }
            catch (invalid_argument) {
                cout << "Wrong data..." << endl;
                continue;
            }
        } else if (option == 9) {
            break;
        } else {
            cout << "Wrong option..." << endl;
        }
        cout << endl;
    }
}

int ServiceInterface::getAction() {
    int action;
    cin.clear();
    cout << "1. Print Stations      2. Print Vehicles in Station        3. Change station limit" << endl;
    cout << "4. Move vehicle        5. Repair Vehicle                   6. Change station location" << endl;
    cout << "7. Add new vehicle     8. Remove vehicle                   9. Exit" << endl;
    cout << "Enter number to define action > ";
    cin >> action;
    cout << endl;
    return action;
}


void ServiceInterface::printSupportedStations() {
    cout << "Supported Stations: " << endl;
    serviceClass.printSupportedStations();
}

void ServiceInterface::printVehiclesInStation(Station *station) {
    cout << "Vehicles in given station: " << endl;
    Service::printVehiclesInStation(station);
}

bool ServiceInterface::changeStationLimit(int newLimit, Station* station) {
    return Service::changeStationLimit(newLimit, station);
}

bool ServiceInterface::repairVehicle(Vehicle* vehicle) {
    return Service::repairVehicle(vehicle);
}

bool ServiceInterface::moveVehicle(Vehicle *vehicle, Station *fromStation, Station *toStation) {
    return Service::moveVehicle(vehicle, fromStation, toStation);
}

bool ServiceInterface::changeStationLocation(Station *station, Location location) {
    return Service::changeStationLocation(station, std::move(location));
}

bool ServiceInterface::addVehicle(Station *station, Vehicle *vehicle) {
    return Service::addVehicle(station, vehicle);
}

bool ServiceInterface::removeVehicle(Station *station, Vehicle *vehicle) {
    return Service::removeVehicle(station, vehicle);
}


void ServiceInterface::printSuccess(bool success) {
    if (success) {
        cout << "Operation finished successfully" << endl;
    } else {
        cout << "Something went wrong..." << endl;
    }
}

Station* ServiceInterface::getStation() {
    string code;
    cout << "Enter station code > ";
    cin >> code;
    cout << endl;
    for (auto i : serviceClass){
        if (i->code == code) {
            return i;
        }
    }
    throw invalid_argument("Wrong code");
}

Vehicle* ServiceInterface::getVehicle(Station* station) {
    string id;
    cout << "Enter vehicle id > ";
    cin >> id;
    cout << endl;
    int id_number = stoi(id);
    for (auto vehicle : *station) {
        if (vehicle->id == id_number) {
            return vehicle;
        }
    }
    throw invalid_argument("Wrong vehicle id");
}

Location ServiceInterface::getLocation() {
    string city, district, streetName, streetNumber, xCoordString, yCoordString;
    int xCoord, yCoord;
    cout << "Enter city > ";
    cin >> city;
    cout << "Enter district > ";
    cin >> district;
    cout << "Enter street name > ";
    cin >> streetName;
    cout << "Enter street number > ";
    cin >> streetNumber;
    cout << "Enter x coord > ";
    cin >> xCoordString;
    xCoord = stoi(xCoordString);
    cout << "Enter y coord > ";
    cin >> yCoordString;
    yCoord = stoi(yCoordString);
    Location loc(city, district, streetName, streetNumber, xCoord, yCoord);
    return loc;
}

std::shared_ptr<Vehicle> ServiceInterface::getNewVehicle() {
    string type, id;
    cout << "Enter vehicle id > ";
    cin >> id;
    cout << "Types: Bike, Scooter, ElectricScooter" << endl;
    cout << "Insert type of the new vehicle > ";
    cin >> type;
    int idNumber = stoi(id);
    if (type == "Bike") {
        return std::make_shared<Bike>(idNumber);
    } else if (type == "Scooter") {
        return std::make_shared<Scooter>(idNumber);
    } else if (type == "ElectricScooter") {
        return std::make_shared<ElectricScooter>(idNumber);
    } else {
        throw std::invalid_argument("Wrong type");
    }
}
