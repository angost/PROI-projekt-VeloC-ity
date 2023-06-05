//
// Created by Adrian Murawski on 05/06/2023.
//

#include "DataParser.h"
#include <memory>
#include <utility>
#include <map>
using namespace std;

DataParser::DataParser(vector<string> stationFilenames) {
    this->stationFilenames = std::move(stationFilenames);
}


vector<Station *> DataParser::getAllStations() {
    vector < Station* > stations;
    for (const auto& filename : stationFilenames) {
        Station* station = getStation(filename);
        stations.push_back(station);
    }
    return stations;
}


Station* DataParser::getStation(const string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::string stationType, name, code, city, district, streetName, streetNumber;
    int x, y;
    string vehicleType;
    int id;

    if (file.is_open()) {
        getline(file, line);
        std::istringstream stationData(line);
        stationData >> stationType >> name >> code >> city >> district >> streetName >> streetNumber >> x >> y;
        Location stationLocation(city, district, streetName, streetNumber, x, y);
        vector<Vehicle*> stationVehicles;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            iss >> vehicleType >> id;
            if (vehicleType == "Bike") {
                auto* vehicle = new Bike(id);
                stationVehicles.push_back(vehicle);
            } else if (vehicleType == "Scooter") {
                auto* vehicle = new Scooter(id);
                stationVehicles.push_back(vehicle);
            } else if (vehicleType == "ElectricScooter") {
                auto* vehicle = new ElectricScooter(id);
                stationVehicles.push_back(vehicle);
            } else {
                throw std::invalid_argument("Wrong vehicle type");
            }
        }
        file.close();
        if (stationType == "MainStation") {
            auto* station = new MainStation(name, code, stationLocation, stationVehicles);
            return station;
        } else if (stationType == "SubStation") {
            auto* station = new SubStation(name, code, stationLocation, stationVehicles);
            return station;
        } else if (stationType == "LocalStation") {
            auto* station = new LocalStation(name, code, stationLocation, stationVehicles);
            return station;
        }
    }
    return nullptr;
}

vector<Service> DataParser::assignStationsToServiceCrews(const string& serviceCrewAssignmentFilename, const vector <Station* > stations) {
    vector < Service > serviceCrews;
    std::ifstream file(serviceCrewAssignmentFilename);
    string line;
    map < string, vector < int > > assignment;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            string identifier;
            int number;
            std::istringstream iss(line);
            iss >> number >> identifier;
            assignment[identifier].push_back(number);
        }
    }
    for (const auto& crew : assignment) {
        vector < Station* > thisCrewStations;
        for (auto i : crew.second) {
            thisCrewStations.push_back(stations[i - 1]);
        }
        Service newCrew(crew.first, thisCrewStations);
        serviceCrews.push_back(newCrew);
    }
    return serviceCrews;
}
