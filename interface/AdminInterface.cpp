//
// Created by Adrian Murawski on 06/06/2023.
//

#include "AdminInterface.h"

#include <utility>


AdminInterface::AdminInterface(AdminService admin){
    this->admin = std::move(admin);
}


void AdminInterface::mainInterface() {
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
            displayStations();
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
            ServiceInterface::printVehiclesInStation(station);
            continue;
        } else if (option == 3) {
            displayStationAssignment();
            continue;
        } else if (option == 4) {
            try {
                Station* newStation = getNewStation();
                success = addNewStation(newStation);
            }
            catch (invalid_argument) {
                cout << "Wrong data..." << endl;
                continue;
            }
        } else if (option == 5) {
            Station* station;
            try {
                station = getStation();
            }
            catch (invalid_argument) {
                cout << "Wrong code..." << endl;
                continue;
            }
            success = removeExistingStation(station);
            if (success) {
                unassignRemovedStation(station);
            }
        } else if (option == 6) {
            Station* station;
            try {
                station = getStation();
            }
            catch (invalid_argument) {
                cout << "Wrong code..." << endl;
                continue;
            }
            Service serviceCrew;
            try {
                serviceCrew = getServiceCrew();
            }
            catch (invalid_argument) {
                cout << "Wrong identifier..." << endl;
                continue;
            }
            success = assignStation(station, serviceCrew);
        } else if (option == 7) {
            break;
        } else {
            cout << "Wrong option..." << endl;
            continue;
        }
        ServiceInterface::printSuccess(success);
        cout << endl;
    }
}


int AdminInterface::getAction() {
    string action;
    cin.clear();
    cout << "1. Print all Stations      2. Print Vehicles in Station        3. Print station assignment" << endl;
    cout << "4. Add new Station         5. Remove current station           6. Assign Station" << endl;
    cout << "7. Exit" << endl;
    cout << "Enter number to define action > ";
    cin >> action;
    cout << endl;
    int actionInt = stoi(action);
    return actionInt;
}


void AdminInterface::displayStations() {
    admin.displayStations();
}

void AdminInterface::displayStationAssignment() {
    admin.displayStationAssignment();
}


Station *AdminInterface::getStation() {
    string code;
    cout << "Enter station code > ";
    cin >> code;
    cout << endl;
    for (auto i : admin.stations){
        if (i->code == code) {
            return i;
        }
    }
    throw invalid_argument("Wrong code");
}


Service AdminInterface::getServiceCrew() {
    string identifier;
    cout << "Enter service crew identifier > ";
    cin >> identifier;
    cout << endl;
    for (auto i : admin.serviceTeams) {
        if (i.identifier == identifier) {
            return i;
        }
    }
    throw invalid_argument("Wrong identifier");
}

Station *AdminInterface::getNewStation() {
    string type;
    cout << "Available station types: MainStation, SubStation, LocalStation" << endl;
    cout << "Enter Station type > ";
    cin >> type;
    if (type == "MainStation"){
        auto* vehicle = new MainStation;
        cout << "Enter new station parameters in this way: " << endl;
        cout << "MainStation station_name station_code city district street_name street_number x y" << endl;
        cin >> *vehicle;
        return vehicle;
    } else if (type == "SubStation") {
        auto* vehicle = new SubStation;
        cout << "Enter new station parameters in this way: " << endl;
        cout << "SubStation station_name station_code city district street_name street_number x y" << endl;
        cin >> *vehicle;
        return vehicle;
    } else if (type == "LocalStation") {
        auto* vehicle = new LocalStation;
        cout << "Enter new station parameters in this way: " << endl;
        cout << "LocalStation station_name station_code city district street_name street_number x y" << endl;
        cin >> *vehicle;
        return vehicle;
    } else {
        throw invalid_argument("Wrong station type");
    }
}

bool AdminInterface::addNewStation(Station* newStation) {
    admin.stations.push_back(newStation);
    return true;
}

bool AdminInterface::removeExistingStation(Station* station) {
    return admin.removeExistingStation(station);
}

void AdminInterface::unassignRemovedStation(Station* station){
    admin.unassignRemovedStation(station);
}

bool AdminInterface::assignStation(Station* station, Service serviceTeam) {
    return AdminService::assignStation(station, std::move(serviceTeam));
}
