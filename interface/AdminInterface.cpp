//
// Created by Adrian Murawski on 06/06/2023.
//

#include "AdminInterface.h"

#include <utility>
#include <limits>

using namespace std;


AdminInterface::AdminInterface(AdminService adminService, DataParser &data){
    this->adminService = std::move(adminService);
    this->data = data;
}


void AdminInterface::mainInterface() {
    cout << "               -> Hello Admin " << endl;
    cout << "               -> What are your orders? " << endl;
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
            displayStations();
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
            ServiceInterface::printVehiclesInStation(station);
            continue;
        } else if (option == 3) {
            displayStationAssignment();
            continue;
        } else if (option == 4) {
            try {
                Station* newStation = getNewStation();
                success = addNewStation(newStation);
                data.insertNewStation(newStation);
            }
            catch (invalid_argument &err) {
                cout << "ERROR: " <<err.what() << endl;
                continue;
            }
        } else if (option == 5) {
            Station* station;
            try {
                station = getStation();
            }
            catch (invalid_argument &err) {
                cout << "ERROR: " <<err.what() << endl;
                continue;
            }
            success = removeExistingStation(station);
            if (success) {
                unassignRemovedStation(station);
            }
            try {
                data.deleteAllAssignments(station);
                data.deleteStation(station);
            }
            catch  (invalid_argument &err) {
                cout << "ERROR: " <<err.what() << endl;
                cout << "REFRESH DATA" << endl;
                continue;
            }
            catch (...) {
                cout << "UNEXPECTED ERROR OCCURRED" << endl;
                cout << "MAYBE YOU NEED TO REFRESH DATA" << endl;
                continue;
            }
            delete station;
        } else if (option == 6) {
            Station* station;
            try {
                station = getStation();
            }
            catch (invalid_argument &err) {
                cout << "ERROR: " <<err.what() << endl;
                continue;
            }
            try {
                Service& serviceCrew = getServiceCrew();
                success = assignStation(station, serviceCrew);
                data.assignStation(station, serviceCrew);
            }
            catch (invalid_argument &err) {
                cout << "ERROR: " <<err.what() << endl;
                continue;
            }
        } else if (option == 7) {
            data.refreshData(adminService.stations, adminService.serviceTeams);
            continue;
        } else if (option == 8) {
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
    cout << "                     DISPLAY                       |                   STATION      " << endl;
    cout << "          1. Print all Stations                    |           4. Add new Station  " << endl;
    cout << "          2. Print Vehicles in Station             |           5. Remove current station " << endl;
    cout << "          3. Print Station assignment              |           6. Assign Station                " << endl;
    cout << "                                                   |           7. REFRESH" << endl;
    cout << "                                                   |           8. EXIT" << endl;
    cout << "Enter number to define action > ";
    cin >> action;
    cout << endl;
    int actionInt = stoi(action);
    return actionInt;
}


void AdminInterface::displayStations() {
    adminService.displayStations();
}

void AdminInterface::displayStationAssignment() {
    adminService.displayStationAssignment();
}


Station *AdminInterface::getStation() {
    string code;
    cout << "Enter station code > ";
    cin >> code;
    cout << endl;
    for (auto i : adminService.stations){
        if (i->code == code) {
            return i;
        }
    }
    throw invalid_argument("Wrong code");
}


Service& AdminInterface::getServiceCrew() {
    string identifier;
    cout << "Enter service crew identifier > ";
    cin >> identifier;
    cout << endl;
    for (auto& i : adminService.serviceTeams) {
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
        string line;
        auto* station = new MainStation;
        cout << "Enter new station parameters in this way: " << endl;
        cout << "MainStation station_name station_code x y" << endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, line);
        std::istringstream iss(line);
        string stationType, stationName, stationCode, x, y;
        iss >> stationType >> stationName >> stationCode >> x >> y;
        if (!(stationType == "MainStation")) {
            throw invalid_argument("Wrong station type given");
        }
        if (stationCode[0] != 'A') {
            throw invalid_argument("Wrong station code");
        }
        std::istringstream is(line);
        is >> *station;
        Location currentLocation  = station->getStationLocation();
        Location recognisedLocation = getLocation(adminService.locations, currentLocation.x_coord, currentLocation.y_coord);
        station->changeLocation(recognisedLocation);
        return station;
    } else if (type == "SubStation") {
        string line;
        auto* station = new SubStation;
        cout << "Enter new station parameters in this way: " << endl;
        cout << "SubStation station_name station_code x y" << endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, line);
        std::istringstream iss(line);
        string stationType, stationName, stationCode, x, y;
        iss >> stationType >> stationName >> stationCode >> x >> y;
        if (!(stationType == "SubStation")) {
            throw invalid_argument("Wrong station type given");
        }
        if (stationCode[0] != 'B') {
            throw invalid_argument("Wrong station code");
        }
        std::istringstream is(line);
        is >> *station;
        Location currentLocation  = station->getStationLocation();
        Location recognisedLocation = getLocation(adminService.locations, currentLocation.x_coord, currentLocation.y_coord);
        station->changeLocation(recognisedLocation);
        return station;
    } else if (type == "LocalStation") {
        string line;
        auto* station = new LocalStation;
        cout << "Enter new station parameters in this way: " << endl;
        cout << "LocalStation station_name station_code x y" << endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, line);
        std::istringstream iss(line);
        string stationType, stationName, stationCode, x, y;
        iss >> stationType >> stationName >> stationCode >> x >> y;
        if (!(stationType == "LocalStation")) {
            throw invalid_argument("Wrong station type given");
        }
        if (stationCode[0] != 'C') {
            throw invalid_argument("Wrong station code");
        }
        std::istringstream is(line);
        is >> *station;
        Location currentLocation  = station->getStationLocation();
        Location recognisedLocation = getLocation(adminService.locations, currentLocation.x_coord, currentLocation.y_coord);
        station->changeLocation(recognisedLocation);
        return station;
    } else {
        throw invalid_argument("Wrong station type");
    }
}

Location AdminInterface::getLocation(const vector < Location >& existingLocations, int x, int y) {
    for (auto loc : existingLocations) {
        if (loc.x_coord == x && loc.y_coord == y){
            return loc;
        }
    }
    throw invalid_argument("Invalid coordinates");
}


bool AdminInterface::addNewStation(Station* newStation) {
    return adminService.addNewStation(newStation);
}

bool AdminInterface::removeExistingStation(Station* station) {
    return adminService.removeExistingStation(station);
}

void AdminInterface::unassignRemovedStation(Station* station){
    adminService.unassignRemovedStation(station);
}

bool AdminInterface::assignStation(Station* station, Service& serviceTeam) {
    return AdminService::assignStation(station, serviceTeam);
}
