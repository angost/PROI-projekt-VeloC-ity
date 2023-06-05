//
// Created by Adrian Murawski on 23/04/2023.
//

#include "Station.h"


using namespace std;

Station::Station(string name, string code, Location location, vector < Vehicle* > currentVehicles, int maxVehicles, int numberOfRentals) {
    this->name = std::move(name);
    this->code = std::move(code);
    this->location = std::move(location);
    this->currentVehicles = std::move(currentVehicles);
    this->maxVehiclesNumber = maxVehicles;
    this->numberOfRentals = numberOfRentals;
}

bool Station::checkIfSpaceAvailable() const{
    if (this->currentVehicles.size() < this->maxVehiclesNumber){
        return true;
    }
    return false;
}


bool Station::addToStation(Vehicle* vehicle) {
    this->currentVehicles.push_back(vehicle);
    return true;
}

bool Station::changeLimit(int newLimit) {
    if (newLimit < 0){
        return false;
    }
    this->maxVehiclesNumber = newLimit;
    return true;
}

bool Station::checkIfVehicleInStation(Vehicle* veh){
    for (int i = 0; i <= currentVehicles.size(); i++){
        if (currentVehicles[i] == veh){
            return true;
        }
    }
    return false;
}

bool Station::deleteVehicle(Vehicle* vehicle) {
    for (int i = 0; i <= currentVehicles.size(); i++){
        if (currentVehicles[i] == vehicle){
            if (deleteVehicleByIndex(i)){
                return true;
            }
            break;
        }
    }
    return false;
}

bool Station::deleteVehicleByIndex(int index) {
    if (index > this->currentVehicles.size() or index < 0){
        return false;
    }
    this->currentVehicles.erase(currentVehicles.begin() + index);
    return true;
}

void Station::incrementCounter() {
    this->numberOfRentals += 1;
}

bool Station::changeLocation(Location newLocation) {
    this->location = std::move(newLocation);
    return true;
}

int Station::countAvailableSpots() const
{
    return this->maxVehiclesNumber - (int) this->currentVehicles.size();
}

bool Station::operator==(Station *other) const {
    return (this->code == other->code);
}

Location Station::getStationLocation() {
    return this->location;
}

void Station::printVehiclesInStation() {
    for (auto i : currentVehicles){
        int targetLength = 25;
        string vehicleType = i->type;
        if (vehicleType.length() < targetLength) {
            vehicleType.resize(targetLength, ' ');
        }
        cout << "Type: " << vehicleType << "       ";
        cout << "ID: " << i->id << "     "  << "Status (reserved): ";
        cout << boolalpha << i->reservedStatus;
        cout << "       NOR: " << i->numberOfRentals << "       TC: " << i->technicalCondition << endl;
    }
    int spots = countAvailableSpots();
    cout << "Available spots: " << spots << endl;
}

vector<Vehicle *>::iterator Station::begin() {
    return currentVehicles.begin();
}


vector < Vehicle* >::iterator Station::end() {
    return currentVehicles.end();
}

ostream &operator<<(ostream &out, const Station &station) {
    string type;
    if (station.code[0] == 'A') {
        type = "MainStation";
    } else if (station.code[0] == 'B') {
        type = "SubStation";
    } else if (station.code[0] == 'C') {
        type = "LocalStation";
    } else {
        type = "Unknown";
    }
    out << type << " " << station.name << " "
    << station.code << " " << station.location.city << " "
    << station.location.district << " " << station.location.street_name
    << " " << station.location.street_number << " " << station.location.x_coord
    << " " << station.location.y_coord << endl;
    for (auto i : station.currentVehicles) {
        out << i->type << " " << i->id << endl;
    }
    return out;
}

istream& operator>>(istream& in, Station& station) {
    string line, type;
    getline(in, line);
    std::istringstream iss(line);
    iss >> type >> station.name >> station.code >> station.location.city
       >> station.location.district >> station.location.street_name
       >> station.location.street_number >> station.location.x_coord
       >> station.location.y_coord;
    while (getline(in, line)) {
        string vehicleType;
        int id;
        std::istringstream is(line);
        is >> vehicleType >> id;
        if (vehicleType == "Bike") {
            auto* vehicle = new Bike(id);
            station.currentVehicles.push_back(vehicle);
        } else if (vehicleType == "Scooter") {
            auto* vehicle = new Scooter(id);
            station.currentVehicles.push_back(vehicle);
        } else if (vehicleType == "ElectricScooter") {
            auto* vehicle = new ElectricScooter(id);
            station.currentVehicles.push_back(vehicle);
        } else {
            throw std::invalid_argument("Wrong vehicle type");
        }
    }
    return in;
}

