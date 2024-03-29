//
// Created by Adrian Murawski on 05/06/2023.
//

#ifndef PROI_PROJEKT_DATAPARSER_H
#define PROI_PROJEKT_DATAPARSER_H
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <utility>
#include <map>
#include <cstdio>

#include "src/station/station/Station.h"
#include "src/station/station/MainStation.h"
#include "src/station/station/SubStation.h"
#include "src/station/station/LocalStation.h"
#include "src/station/service/Service.h"
#include "src/Location.h"
#include "src/vehicle/Vehicle.h"
#include "src/vehicle/Bike.h"
#include "src/vehicle/Scooter.h"
#include "src/vehicle/ElectricScooter.h"

using namespace std;

class DataParser {
    string stationFilenamesPath;
    string serviceCrewAssignmentFilename;
    string serviceCrewNamesPath;
    string userLocationFilePath;
    string stationsDataPath;
    vector < string > stationFilenames;
    vector <Location> existingLocations;
public:
    DataParser();
    DataParser(string pathToStationNames, string stationsDataPath, string serviceCrewAssignmentFilepath, string userLocationFilepath, string serviceCrewNamesPath, vector <Location> locations);
    Location getLocation(int x, int y);
    vector < Station* > getAllStations();
    Station* getStation(const string& filename);
    vector < Service > assignStationsToServiceCrews(vector <Station*>& stations);
    Location getUserLocation();

    void refreshData(vector < Station* > &currentStations, vector < Service > &serviceCrews);
    void refreshStationsData(vector < Station* > &currentStations);

    // ADMIN
    void insertNewStation(Station* station);
    void assignStation(Station* station, const Service& serviceCrew);
    bool deleteStation(Station* station);
    void deleteAllAssignments(Station* station);
    void deleteAssignment(Station* station, const Service& serviceCrew);
    void addNewService(string serviceId);
    bool removeCurrentService(Service service);

    // SERVICE
    void changeStationLimit(Station* changedStation);
    void changeStationLocation(Station* changedStation);
    void changeVehicleRentedStatus(Station* station, Vehicle* changedVehicle);
    void changeVehicleReservedStatus(Station* station, Vehicle* changedVehicle);
    void changeVehicleReservedStatus(string stationCode, Vehicle *changedVehicle);
    void changeVehicleTechnicalCondition(Station* station, Vehicle* changedVehicle);
    void changeVehicleNumberOfRentals(Station* station, Vehicle* changedVehicle);
    void removeVehicle(Station* station, Vehicle* vehicle);
    void addVehicle(Station* station, Vehicle* vehicle);
    void refreshServiceData(vector < Station* >& stations, Service &service);

    vector < string > getFilenames();

    // USER
    void saveRentedVehiclesBuffer(vector <Vehicle*>& rentedVehiclesBuffer);
    Vehicle* recreateVehicleInBuffer(string type, int id, int numberOfRentals, int technicalCondition, int rentedStatus, int reservedStatus);
    vector <Vehicle*> getRentedVehiclesBuffer();

};


#endif //PROI_PROJEKT_DATAPARSER_H
