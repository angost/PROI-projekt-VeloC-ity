//
// Created by Adrian Murawski on 05/06/2023.
//

#include "DataParser.h"
using namespace std;
//TODO przekazac do dataparsera locations i potem sprawdzac czy podane wspolrzedne istnieja, w pliku nie podawac nazw ulic tylko koordynaty (?)

DataParser::DataParser(vector<string> stationFilenames, vector <Location> existingLocations) {
    this->stationFilenames = std::move(stationFilenames);
    this->existingLocations = existingLocations;
}

Location DataParser::getLocation(int x, int y){
    for (auto loc : existingLocations) {
        if (loc.x_coord == x && loc.y_coord == y){
            return loc;
        }
    }
    throw invalid_argument("Invalid coordinates");
}

vector<Station *> DataParser::getAllStations() {
    vector < Station* > stations;
    for (const auto& filename : stationFilenames) {
        try {
            Station* station = getStation(filename);
            stations.push_back(station);
        } catch (invalid_argument& err) {
            cout << err.what() << endl;
            continue;
        }

    }
    return stations;
}


Station* DataParser::getStation(const string& filename) {
    std::ifstream file(filename);
    std::string line;
    string vehicleType;

    if (file.is_open()) {
        string type, not_important, x_given, y_given;
        Location recognisedLocation;

        getline(file, line);
        std::istringstream iss(line);
        iss >> type >> not_important >> not_important >> x_given >> y_given;
        file.close();

        try{
            recognisedLocation = getLocation(stoi(x_given), stoi(y_given));
        } catch (invalid_argument& err) {
            cout << err.what() << endl;
            throw invalid_argument("Couldn't create station");
        }

        std::ifstream sameFile(filename);
        if (type == "MainStation") {
            auto* mainStation = new MainStation;
            sameFile >> *mainStation;
            file.close();
            mainStation->changeLocation(recognisedLocation);
            return mainStation;
        } else if (type == "SubStation") {
            auto* subStation = new SubStation;
            sameFile >> *subStation;
            file.close();
            subStation->changeLocation(recognisedLocation);
            return subStation;
        } else if (type == "LocalStation") {
            auto* localStation = new LocalStation;
            sameFile >> *localStation;
            file.close();
            localStation->changeLocation(recognisedLocation);
            return localStation;
        } else {
            file.close();
            throw invalid_argument("Wrong station type");
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


Location DataParser::getUserLocation(const string& filename){
    std::ifstream file(filename);
    string line;
    string city, district, streetName, streetNumber;
    int x, y;
    if (file.is_open()) {
        getline(file, line);
        std::istringstream iss(line);
        iss >> city >> district >> streetName >> streetNumber >> x >> y;
        return {city, district, streetName, streetNumber, x, y};
    }
}