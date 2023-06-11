//
// Created by Adrian Murawski on 05/06/2023.
//

#include "DataParser.h"
#include "interface/interface_functions.h"

#include <utility>
#include <algorithm>
using namespace std;

DataParser::DataParser() {
    this->serviceCrewAssignmentFilename = "";
    this->stationFilenamesPath = "";
    this->userLocationFilePath = "";
    this->stationFilenames = vector < string > ();
    this->existingLocations = vector < Location > ();
}


DataParser::DataParser(string pathToStationNames, string stationsDataPath, string serviceCrewAssignmentFilepath, string userLocationFilepath, vector <Location> locations) {
    this->serviceCrewAssignmentFilename = serviceCrewAssignmentFilepath;
    this->stationFilenamesPath = pathToStationNames;
    this->stationsDataPath = stationsDataPath;
    this->userLocationFilePath = userLocationFilepath;
    this->stationFilenames = getFilenames();
    this->existingLocations = locations;
}

void DataParser::refreshData(vector < Station* > &currentStations, vector < Service > &serviceCrews) {
    this->stationFilenames = getFilenames();
    for (auto& station : currentStations) {
        for (auto& vehicle : *station) {
            delete vehicle;
        }
        delete station;
    }
    currentStations.clear();
    currentStations = getAllStations();
    serviceCrews.clear();
    serviceCrews = assignStationsToServiceCrews(currentStations);
}

void DataParser::refreshStationsData(vector < Station* > &currentStations) {
    this->stationFilenames = getFilenames();
    for (auto& station : currentStations) {
        for (auto& vehicle : *station) {
            delete vehicle;
        }
        delete station;
    }
    currentStations.clear();
    currentStations = getAllStations();
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

vector<Service> DataParser::assignStationsToServiceCrews(vector <Station* >& stations) {
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
    for (auto& crew : assignment) {
        vector < Station* > thisCrewStations;
        for (auto& code : crew.second) {
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
    stationNames.close();
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
    changedFile.close();
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
    changedFile.close();
    return true;
}


void DataParser::changeStationLimit(Station *changedStation) {
    ifstream file(stationsDataPath + "/" + changedStation->code + ".txt");
    string line, newFile;
    getline(file, line);
    std::istringstream iss(line);
    string type, name, code;
    int x, y, maxVehiclesNumber, numberOfRentals;
    iss >> type >> name >> code >> x
        >> y >> maxVehiclesNumber >> numberOfRentals;
    newFile += type + " " + name + " " + code + " " + to_string(x) + " " + to_string(y) + " " + to_string(changedStation->maxVehiclesNumber) + " " + to_string(numberOfRentals);
    newFile += "\n";
    while (getline(file, line)) {
        newFile += line;
        newFile += "\n";
    }
    file.close();
    std::ofstream changedFile(stationsDataPath + "/" + changedStation->code + ".txt");
    changedFile << newFile;
    changedFile.close();
}


void DataParser::changeStationLocation(Station *changedStation) {
    ifstream file(stationsDataPath + "/" + changedStation->code + ".txt");
    string line, newFile;
    getline(file, line);
    std::istringstream iss(line);
    string type, name, code;
    int x, y, maxVehiclesNumber, numberOfRentals;
    iss >> type >> name >> code >> x
        >> y >> maxVehiclesNumber >> numberOfRentals;
    Location loc = changedStation->getStationLocation();
    newFile += type + " " + name + " " + code + " " + to_string(loc.x_coord) + " " + to_string(loc.y_coord) + " " + to_string(maxVehiclesNumber) + " " + to_string(numberOfRentals);
    newFile += "\n";
    while (getline(file, line)) {
        newFile += line;
        newFile += "\n";
    }
    file.close();
    std::ofstream changedFile(stationsDataPath + "/" + changedStation->code + ".txt");
    changedFile << newFile;
    changedFile.close();
}


void DataParser::changeVehicleRentedStatus(Station *station, Vehicle *changedVehicle) {
    ifstream file(stationsDataPath + "/" + station->code + ".txt");
    string line, newFile;
    getline(file, line);
    newFile += line + "\n";
    string vehicleType;
    int id, technicalCondition, numberOfRentals;
    bool reservedStatus, rentedStatus;
    while (getline(file, line)) {
        std::istringstream iss(line);
        iss >> vehicleType >> id >> rentedStatus >> reservedStatus >> technicalCondition >> numberOfRentals;
        if (id != changedVehicle->id) {
            newFile += line;
            newFile += "\n";
        } else {
            newFile += vehicleType + " " + to_string(id) + " " + to_string(changedVehicle->rentedStatus) + " " + to_string(reservedStatus) + " " + to_string(technicalCondition) + " " + to_string(numberOfRentals);
            newFile += "\n";
        }
    }
    file.close();
    std::ofstream changedFile(stationsDataPath + "/" + station->code + ".txt");
    changedFile << newFile;
    changedFile.close();
}

void DataParser::changeVehicleReservedStatus(Station *station, Vehicle *changedVehicle) {
    ifstream file(stationsDataPath + "/" + station->code + ".txt");
    string line, newFile;
    getline(file, line);
    newFile += line + "\n";
    string vehicleType;
    int id, technicalCondition, numberOfRentals;
    bool reservedStatus, rentedStatus;
    while (getline(file, line)) {
        std::istringstream iss(line);
        iss >> vehicleType >> id >> rentedStatus >> reservedStatus >> technicalCondition >> numberOfRentals;
        if (id != changedVehicle->id) {
            newFile += line;
            newFile += "\n";
        } else {
            newFile += vehicleType + " " + to_string(id) + " " + to_string(rentedStatus) + " " + to_string(changedVehicle->reservedStatus) + " " + to_string(technicalCondition) + " " + to_string(numberOfRentals);
            newFile += "\n";
        }
    }
    file.close();
    std::ofstream changedFile(stationsDataPath + "/" + station->code + ".txt");
    changedFile << newFile;
    changedFile.close();
}

void DataParser::changeVehicleReservedStatus(string stationCode, Vehicle *changedVehicle) {
    ifstream file(stationsDataPath + "/" + stationCode + ".txt");
    string line, newFile;
    getline(file, line);
    newFile += line + "\n";
    string vehicleType;
    int id, technicalCondition, numberOfRentals;
    bool reservedStatus, rentedStatus;
    while (getline(file, line)) {
        std::istringstream iss(line);
        iss >> vehicleType >> id >> rentedStatus >> reservedStatus >> technicalCondition >> numberOfRentals;
        if (id != changedVehicle->id) {
            newFile += line;
            newFile += "\n";
        } else {
            newFile += vehicleType + " " + to_string(id) + " " + to_string(rentedStatus) + " " + to_string(changedVehicle->reservedStatus) + " " + to_string(technicalCondition) + " " + to_string(numberOfRentals);
            newFile += "\n";
        }
    }
    file.close();
    std::ofstream changedFile(stationsDataPath + "/" + stationCode + ".txt");
    changedFile << newFile;
    changedFile.close();
}


void DataParser::changeVehicleTechnicalCondition(Station *station, Vehicle *changedVehicle) {
    ifstream file(stationsDataPath + "/" + station->code + ".txt");
    string line, newFile;
    getline(file, line);
    newFile += line + "\n";
    string vehicleType;
    int id, technicalCondition, numberOfRentals;
    bool reservedStatus, rentedStatus;
    while (getline(file, line)) {
        std::istringstream iss(line);
        iss >> vehicleType >> id >> rentedStatus >> reservedStatus >> technicalCondition >> numberOfRentals;
        if (id != changedVehicle->id) {
            newFile += line;
            newFile += "\n";
        } else {
            newFile += vehicleType + " " + to_string(id) + " " + to_string(rentedStatus) + " " + to_string(reservedStatus) + " " + to_string(changedVehicle->technicalCondition) + " " + to_string(numberOfRentals);
            newFile += "\n";
        }
    }
    file.close();
    std::ofstream changedFile(stationsDataPath + "/" + station->code + ".txt");
    changedFile << newFile;
    changedFile.close();
}


void DataParser::changeVehicleNumberOfRentals(Station *station, Vehicle *changedVehicle) {
    ifstream file(stationsDataPath + "/" + station->code + ".txt");
    string line, newFile;
    getline(file, line);
    newFile += line + "\n";
    string vehicleType;
    int id, technicalCondition, numberOfRentals;
    bool reservedStatus, rentedStatus;
    while (getline(file, line)) {
        std::istringstream iss(line);
        iss >> vehicleType >> id >> rentedStatus >> reservedStatus >> technicalCondition >> numberOfRentals;
        if (id != changedVehicle->id) {
            newFile += line;
            newFile += "\n";
        } else {
            newFile += vehicleType + " " + to_string(id) + " " + to_string(rentedStatus) + " " + to_string(reservedStatus) + " " + to_string(technicalCondition) + " " + to_string(changedVehicle->numberOfRentals);
            newFile += "\n";
        }
    }
    file.close();
    std::ofstream changedFile(stationsDataPath + "/" + station->code + ".txt");
    changedFile << newFile;
    changedFile.close();
}


void DataParser::removeVehicle(Station *station, Vehicle *vehicle) {
    ifstream file(stationsDataPath + "/" + station->code + ".txt");
    string line, newFile;
    getline(file, line);
    newFile += line + "\n";
    string vehicleType;
    int id, technicalCondition, numberOfRentals;
    bool reservedStatus, rentedStatus;
    while (getline(file, line)) {
        std::istringstream iss(line);
        iss >> vehicleType >> id >> rentedStatus >> reservedStatus >> technicalCondition >> numberOfRentals;
        if (id != vehicle->id) {
            newFile += line;
            newFile += "\n";
        }
    }
    file.close();
    std::ofstream changedFile(stationsDataPath + "/" + station->code + ".txt");
    changedFile << newFile;
    changedFile.close();
}


void DataParser::addVehicle(Station *station, Vehicle *vehicle) {
    std::ofstream changedFile(stationsDataPath + "/" + station->code + ".txt", std::ios::app);
    changedFile << vehicle->type << " " << vehicle->id << " " << vehicle->rentedStatus << " " << vehicle->reservedStatus << " " << vehicle->technicalCondition << " " << vehicle->numberOfRentals << endl;
    changedFile.close();
}


void DataParser::refreshServiceData(vector<Station *>& stations, Service &service) {
    for (auto& station : stations) {
        for (auto& vehicle : *station) {
            delete vehicle;
        }
        delete station;
    }
    ifstream file(serviceCrewAssignmentFilename);
    string line, code, identifier;
    vector < string > codes;
    while (getline(file, line)) {
        std::istringstream iss(line);
        iss >> code >> identifier;
        if (identifier == service.identifier) {
            codes.push_back(code);
        }
    }
    vector < Station* > newStations;
    for (auto& stationCode : codes) {
        newStations.push_back(getStation(stationsDataPath + "/" + stationCode + ".txt"));
    }
    stations = newStations;
}

void DataParser::saveRentedVehiclesBuffer(vector <Vehicle*>& rentedVehiclesBuffer){
    const string RENTED_VEHICLES_BUFFER_FILE_PATH = "../data/inputTxtFiles/rentedVehiclesBuffer.txt";
    ofstream file(RENTED_VEHICLES_BUFFER_FILE_PATH);
    for (auto vehicle: rentedVehiclesBuffer) {
        file << vehicle->type << ' ' << to_string(vehicle->id) << ' ' << to_string(vehicle->rentedStatus) << ' '
             << to_string(vehicle->reservedStatus) << ' ' << to_string(vehicle->technicalCondition) << ' '
             << to_string(vehicle->numberOfRentals) << '\n';
    }
    file.close();
}

Vehicle* DataParser::recreateVehicleInBuffer(string type, int id, int numberOfRentals, int technicalCondition, int rentedStatus, int reservedStatus){
    if (type == "Bike"){
        auto* newVehicle = new Bike(id, numberOfRentals, technicalCondition);
        newVehicle->setRentedStatus(rentedStatus);
        newVehicle->setReservedStatus(reservedStatus);
        return newVehicle;
    } else if (type == "Scooter"){
        auto* newVehicle = new Scooter(id, numberOfRentals, technicalCondition);
        newVehicle->setRentedStatus(rentedStatus);
        newVehicle->setReservedStatus(reservedStatus);
        return newVehicle;
    } else {
        auto* newVehicle = new ElectricScooter(id, numberOfRentals, technicalCondition);
        newVehicle->setRentedStatus(rentedStatus);
        newVehicle->setReservedStatus(reservedStatus);
        return newVehicle;
    }
    return nullptr;
}

vector <Vehicle*> DataParser::getRentedVehiclesBuffer(){
    //TODO tworz obiekty z listy danych o wypozyczonych pojazdach
    const string RENTED_VEHICLES_BUFFER_FILE_PATH = "../data/inputTxtFiles/rentedVehiclesBuffer.txt";
    string line;
    ifstream file(RENTED_VEHICLES_BUFFER_FILE_PATH);

    vector<Vehicle*> rentedVehicles;
    while (getline(file, line)){
        vector<string> parts = splitString(line);
        string type = parts[0];
        int id = stoi(parts[1]);
        int rentedStatus = stoi(parts[2]);
        int reservedStatus = stoi(parts[3]);
        int technicalCondition = stoi(parts[4]);
        int numberOfRentals = stoi(parts[5]);
        Vehicle* newVehicle = recreateVehicleInBuffer(type, id, numberOfRentals, technicalCondition, rentedStatus, reservedStatus);
        rentedVehicles.push_back(newVehicle);
    }
    return rentedVehicles;
}