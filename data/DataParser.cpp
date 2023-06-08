//
// Created by Adrian Murawski on 05/06/2023.
//

#include "DataParser.h"

#include <utility>
using namespace std;

DataParser::DataParser() {
    this->serviceCrewAssignmentFilename = "";
    this->stationFilenamesPath = "";
    this->userLocationFilePath = "";
    this->stationFilenames = vector < string > ();
    this->existingLocations = vector < Location > ();
}


DataParser::DataParser(string pathToStationNames, string stationsDataPath, string serviceCrewAssignmentFilepath, string userLocationFilepath, vector <Location> locations) {
    this->serviceCrewAssignmentFilename = std::move(serviceCrewAssignmentFilepath);
    this->stationFilenamesPath = std::move(pathToStationNames);
    this->stationsDataPath = std::move(stationsDataPath);
    this->userLocationFilePath = std::move(userLocationFilepath);
    this->stationFilenames = getFilenames();
    this->existingLocations = std::move(locations);
}

void DataParser::refreshData(vector < Station* > &currentStations, vector < Service > &serviceCrews) {
    this->stationFilenames = getFilenames();
    for (auto& station : currentStations) {
        for (auto& vehicle : *station) {
            delete vehicle;
        }
        delete station;
    }
    currentStations = getAllStations();
    serviceCrews = assignStationsToServiceCrews(currentStations);
}


vector < string > DataParser::getFilenames() {
    std::ifstream file(stationFilenamesPath);
    std::string line, filename;
    vector < string > filenames;

    if (file.is_open()) {
        while (getline(file, line)) {
            std::istringstream iss(line);
            iss >> filename;
            filenames.push_back(filename);
        }
    }
    file.close();
    return filenames;
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
            Station* station = getStation(stationsDataPath + filename);
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

vector<Service> DataParser::assignStationsToServiceCrews(const vector <Station* >& stations) {
    vector < Service > serviceCrews;
    std::ifstream file(serviceCrewAssignmentFilename);
    string line;
    map < string, vector < string > > assignment;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            string identifier;
            string code;
            std::istringstream iss(line);
            iss >> code >> identifier;
            assignment[identifier].push_back(code);
        }
    }
    file.close();
    for (const auto& crew : assignment) {
        vector < Station* > thisCrewStations;
        for (const auto& code : crew.second) {
            for (auto &station : stations) {
                if (station->code == code) {
                    thisCrewStations.push_back(station);
                    break;
                }
            }
        }
        Service newCrew(crew.first, thisCrewStations, existingLocations);
        serviceCrews.push_back(newCrew);
    }
    return serviceCrews;
}


Location DataParser::getUserLocation(){
    std::ifstream file(userLocationFilePath);
    string line;
    string city, district, streetName, streetNumber;
    int x, y;
    if (file.is_open()) {
        getline(file, line);
        std::istringstream iss(line);
        iss >> city >> district >> streetName >> streetNumber >> x >> y;
        return {city, district, streetName, streetNumber, x, y};
    }
    file.close();
    throw invalid_argument("Could not open the file");
}

void DataParser::insertNewStation(Station *station) {
    std::ofstream file(stationsDataPath + "/" + station->code + ".txt");
    Location loc = station->getStationLocation();
    file << station->type << " " << station->name << " " << station->code << " "
    << loc.x_coord << " " << loc.y_coord << endl;
    for (auto &vehicle : *station) {
        file << vehicle->type << " " << vehicle->id << endl;
    }
    file.close();
    std::ofstream stationNames(stationFilenamesPath, std::ios::app);
    stationNames << "/" + station->code + ".txt" << endl;
}


void DataParser::assignStation(Station *station, const Service& serviceCrew) {
    std::ofstream file(serviceCrewAssignmentFilename, std::ios::app);
    file << station->code << " " << serviceCrew.identifier << endl;
    file.close();
}


void DataParser::deleteAllAssignments(Station *station) {
    std::ifstream file(serviceCrewAssignmentFilename);
    string line, stationCode, serviceId;
    string newFile;
    while (getline(file, line)) {
        std::istringstream iss(line);
        iss >> stationCode >> serviceId;
        if (!(stationCode == station->code)) {
            newFile += line;
            newFile += "\n";
        }
    }
    file.close();
    std::ofstream changedFile(serviceCrewAssignmentFilename);
    changedFile << newFile;
    changedFile.close();
}

void DataParser::deleteAssignment(Station *station, const Service& serviceCrew) {
    std::ifstream file(serviceCrewAssignmentFilename);
    string line, stationCode, serviceId;
    string newFile;
    while (getline(file, line)) {
        std::istringstream iss(line);
        iss >> stationCode >> serviceId;
        if (!(stationCode == station->code) && !(serviceId == serviceCrew.identifier)) {
            newFile += line;
            newFile += "\n";
        }
    }
    file.close();
    std::ofstream changedFile(serviceCrewAssignmentFilename);
    changedFile << newFile;
}

bool DataParser::deleteStation(Station *station) {
    if (std::remove((stationsDataPath + "/" + station->code + ".txt").c_str()) != 0) {
        throw invalid_argument("Could not find station file");
    }
    std::ifstream file(stationFilenamesPath);
    string line, filename;
    string newFile;
    while (getline(file, line)) {
        std::istringstream iss(line);
        iss >> filename;
        if (!(filename == "/" + station->code + ".txt")) {
            newFile += line;
            newFile += "\n";
        }
    }
    file.close();
    std::ofstream changedFile(stationFilenamesPath);
    changedFile << newFile;
    return true;
}
