//
// Created by Adrian Murawski on 04/06/2023.
//

#include "ServiceInterface.h"

ServiceInterface::ServiceInterface(Service service) {
    this->serviceClass = std::move(service);
}


void ServiceInterface::mainInterface() {
    while (true){
        cout << "-----------------------------------------------------" << endl;
        bool success;
        int option;
        try {
            option = getAction();
        }
        catch (invalid_argument) {
            cout << "Wrong number..." << endl;
            continue;
        }
        if (option == 1) {
            printSupportedStations();
            continue;
        } else if (option == 2){
            Station* station;
            try {
                station = getStation();
            }
            catch (invalid_argument) {
                cout << "Wrong code..." << endl;
                continue;
            }
            printVehiclesInStation(station);
            continue;
        } else if (option == 3) {
            int newLimitInt;
            Station* station;
            try {
                string newLimit;
                cout << "Enter new limit > ";
                cin >> newLimit;
                cout << endl;
                newLimitInt = stoi(newLimit);
                station = getStation();
            }
            catch (invalid_argument) {
                cout << "Wrong code..." << endl;
                continue;
            }
            success = changeStationLimit(newLimitInt, station);
        } else if (option == 4) {
            cout << "First insert source station code, then vehicle id and finally destination station code" << endl;
            Station* fromStation;
            Vehicle* vehicle;
            Station* toStation;
            try {
                fromStation = getStation();
                vehicle = getVehicle(fromStation);
                toStation = getStation();

            }
            catch (invalid_argument){
                cout << "Wrong data..." << endl;
                continue;
            }
            success = moveVehicle(vehicle, fromStation, toStation);
        } else if (option == 5) {
            cout << "Insert station code and id of vehicle you want to repair..." << endl;
            Vehicle* vehicle;
            try {
                Station* station = getStation();
                vehicle = getVehicle(station);
            }
            catch (invalid_argument) {
                cout << "Wrong data..." << endl;
                continue;
            }
            success = repairVehicle(vehicle);
        } else if (option == 6){
            Station* station;
            Location location;
            try {
                station = getStation();
                location = getLocation();
            }
            catch (invalid_argument) {
                cout << "Wrong data..." << endl;
                continue;
            }
            success = changeStationLocation(station, location);
        } else if (option == 7) {
            Station* station;
            Vehicle* vehicle;
            try {
                station = getStation();
                vehicle = getNewVehicle();
            }
            catch (invalid_argument) {
                cout << "Wrong data..." << endl;
                continue;
            }
            success = addVehicle(station, vehicle);
        } else if (option == 8) {
            Station* station;
            Vehicle* vehicle;
            try {
                station = getStation();
                vehicle = getVehicle(station);
            }
            catch (invalid_argument) {
                cout << "Wrong data..." << endl;
                continue;
            }
            success = removeVehicle(station, vehicle);
        } else if (option == 9) {
            break;
        } else {
            cout << "Wrong option..." << endl;
            continue;
        }
        printSuccess(success);
        cout << endl;
    }
}

int ServiceInterface::getAction() {
    string action;
    cin.clear();
    cout << "1. Print Stations      2. Print Vehicles in Station        3. Change station limit" << endl;
    cout << "4. Move vehicle        5. Repair Vehicle                   6. Change station location" << endl;
    cout << "7. Add new vehicle     8. Remove vehicle                   9. Exit" << endl;
    cout << "Enter number to define action > ";
    cin >> action;
    cout << endl;
    int actionInt = stoi(action);
    return actionInt;
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

Vehicle* ServiceInterface::getNewVehicle() {
    string type, id;
    cout << "Enter vehicle id > ";
    cin >> id;
    cout << "Types: Bike, Scooter, ElectricScooter" << endl;
    cout << "Insert type of the new vehicle > ";
    cin >> type;
    int idNumber = stoi(id);
    if (type == "Bike") {
        auto* vehicle = new Bike(idNumber);
        return vehicle;
    } else if (type == "Scooter") {
        auto* vehicle = new Scooter(idNumber);
        return vehicle;
    } else if (type == "ElectricScooter") {
        auto* vehicle = new ElectricScooter(idNumber);
        return vehicle;
    } else {
        throw std::invalid_argument("Wrong type");
    }
}
