//
// Created by Adrian Murawski on 04/06/2023.
//

#include "ServiceInterface.h"

#include <utility>

ServiceInterface::ServiceInterface(Service &service, DataParser &data) {
    this->serviceClass = service;
    this->data = data;
}


void ServiceInterface::mainInterface() {
    cout << "               -> Hello Team " << serviceClass.identifier << endl;
    cout << "               -> What can I do for you today?" << endl;
    while (true){
        cout << endl << "----------------------------------------------------------------------------------------------------------------" << endl;
        bool success;
        int option;
        try {
            option = getAction();
        }
        catch (invalid_argument &err) {
            cout << "ERROR: " <<err.what() << endl;
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
            catch (invalid_argument &err) {
                cout << "ERROR: " <<err.what() << endl;
                continue;
            }
            printVehiclesInStation(station);
            continue;
        } else if (option == 3) {
            Station* station;
            Vehicle* vehicle;
            try {
                station = getStation();
                vehicle = getVehicle(station);
            }
            catch (invalid_argument &err) {
                cout << "ERROR: " <<err.what() << endl;
                continue;
            }
            printVehicleDetails(vehicle);
            continue;
        } else if (option == 4) {
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
            catch (invalid_argument &err) {
                cout << "ERROR: " <<err.what() << endl;
                continue;
            }
            success = changeStationLimit(newLimitInt, station);
            data.changeStationLimit(station);
        } else if (option == 5) {
            Station* station;
            Location location;
            try {
                station = getStation();
                location = getLocation();
            }
            catch (invalid_argument &err) {
                cout << "ERROR: " <<err.what() << endl;
                continue;
            }
            success = changeStationLocation(station, location);
            data.changeStationLocation(station);
        } else if (option == 6) {
            cout << "Insert station code and id of vehicle you want to repair..." << endl;
            Vehicle* vehicle;
            Station* station;
            try {
                station = getStation();
                vehicle = getVehicle(station);
            }
            catch (invalid_argument &err) {
                cout << "ERROR: " <<err.what() << endl;
                continue;
            }
            success = repairVehicle(vehicle);
            data.changeVehicleTechnicalCondition(station, vehicle);
        } else if (option == 7){
            cout << "First insert source station code, then vehicle id and finally destination station code" << endl;
            Station* fromStation;
            Vehicle* vehicle;
            Station* toStation;
            try {
                fromStation = getStation();
                vehicle = getVehicle(fromStation);
                toStation = getStation();

            }
            catch (invalid_argument &err) {
                cout << "ERROR: " <<err.what() << endl;
                continue;
            }
            success = moveVehicle(vehicle, fromStation, toStation);
            data.removeVehicle(fromStation, vehicle);
            data.addVehicle(toStation, vehicle);
        } else if (option == 8) {
            Station* station;
            Vehicle* vehicle;
            try {
                station = getStation();
                vehicle = getNewVehicle();
            }
            catch (invalid_argument &err) {
                cout << "ERROR: " <<err.what() << endl;
                continue;
            }
            success = addVehicle(station, vehicle);
            data.addVehicle(station, vehicle);
        } else if (option == 9) {
            Station* station;
            Vehicle* vehicle;
            try {
                station = getStation();
                vehicle = getVehicle(station);
            }
            catch (invalid_argument &err) {
                cout << "ERROR: " <<err.what() << endl;
                continue;
            }
            success = removeVehicle(station, vehicle);
            data.removeVehicle(station, vehicle);
        } else if (option == 10) {
            data.refreshServiceData(serviceClass.supportedStations, serviceClass);
            continue;
        } else if (option == 11) {
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
    cout << "          DISPLAY                      |               STATION                 |           VEHICLE          " << endl;
    cout << "  1. Print Stations                    |       4. Change station limit         |     6. Repair Vehicle     " << endl;
    cout << "  2. Print Vehicles in Station         |       5. Change station location      |     7. Move Vehicle   " << endl;
    cout << "  3. Print Vehicle details             |                                       |     8. Add new Vehicle  " << endl;
    cout << "                                       |                                       |     9. Remove Vehicle" << endl;
    cout << "                                       |                                       |     10. REFRESH" << endl;
    cout << "                                       |                                       |     11. EXIT" << endl;
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

void ServiceInterface::printVehicleDetails(Vehicle* vehicle){
    cout << "ID:                    " << vehicle->id << endl;
    cout << "Rental price:          " << vehicle->rentalPrice << endl;
    cout << "Max speed:             " << vehicle->maxSpeed << endl;
    cout << "Number of rentals:     " << vehicle->numberOfRentals << endl;
    cout << "Technical condition:   " << vehicle->technicalCondition << endl;
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
    string xCoordString, yCoordString;
    int xCoord, yCoord;
    cout << "Enter x coord > ";
    cin >> xCoordString;
    xCoord = stoi(xCoordString);
    cout << "Enter y coord > ";
    cin >> yCoordString;
    yCoord = stoi(yCoordString);
    Location loc = getRealLocation(xCoord, yCoord);
    return loc;
}

Location ServiceInterface::getRealLocation(int x, int y) {
    for (auto loc : serviceClass.locations) {
        if (loc.x_coord == x && loc.y_coord == y){
            return loc;
        }
    }
    throw invalid_argument("Invalid coordinates");
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
