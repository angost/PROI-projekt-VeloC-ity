//
// Created by Adrian Murawski on 05/06/2023.
//

#ifndef PROI_PROJEKT_DATAPARSER_H
#define PROI_PROJEKT_DATAPARSER_H
#include <fstream>
#include <sstream>
#include <vector>
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
    vector < string > stationFilenames;
public:
    explicit DataParser(vector < string > stationFilenames);
    vector < Station* > getAllStations();
    Station* getStation(const string& filename);
    vector < Service > assignStationsToServiceCrews(const string& serviceCrewAssignmentFilename, const vector <Station*> stations);
};


#endif //PROI_PROJEKT_DATAPARSER_H