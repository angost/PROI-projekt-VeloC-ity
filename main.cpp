#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>


#include "src/vehicle/Vehicle.h"
#include "src/vehicle/Bike.h"
#include "src/vehicle/Scooter.h"
#include "src/vehicle/ElectricScooter.h"

#include "src/station/station/Station.h"
#include "src/station/station/MainStation.h"
#include "src/station/station/SubStation.h"
#include "src/station/station/LocalStation.h"

#include "src/station/service/Service.h"
#include "src/station/service/AdminService.h"

#include "src/user/User.h"
#include "src/user/StandardUser.h"
#include "src/user/SilverUser.h"
#include "src/user/GoldenUser.h"

#include "src/Location.h"

#include "src/Velocity.h"

#include "interface/interface_functions.h"
#include "interface/UserInterface.h"
#include "interface/ServiceInterface.h"

#include "src/InputParser.h"
#include "data/DataParser.h"
#include "data/setup_functions.h"

using namespace std;

const string STATIONS_DATA_PATH = "../data/stationsData";
const string CREDENTIAL_FILE_NAME = "../data/credentials.txt";
const string SERVICE_CREW_FILE_NAME = "../data/serviceCrewAssignment.txt";
const string USER_STATS_FILE_NAME = "../data/userstats.txt";
const string USER_LOCATION_FILE_NAME = "../data/userLocation.txt";
const string FILENAMES[] = {"/station1.txt", "/station2.txt", "/station3.txt", "/station4.txt", "/station5.txt"};

int main(int argc, char **argv) {
    // LOCATIONS DATA
    vector<Location> locations;
    setupMap(locations);

    // DATA
    vector < string > filenames;
    for (const auto& filename : FILENAMES) {
        filenames.push_back(STATIONS_DATA_PATH + filename);
    }
    DataParser data(filenames, locations);
    vector < Station* > stations = data.getAllStations();
    vector < Service > serviceCrews = DataParser::assignStationsToServiceCrews(SERVICE_CREW_FILE_NAME, stations);
    AdminService admin("X01", serviceCrews);
    Location currentUserLocation = data.getUserLocation(USER_LOCATION_FILE_NAME);



    Location userLocation("Warsaw", "Srodmiescie", "Senatorska", "2", 30, 1);

    // ACTUAL MAIN

    InputParser in(argc, argv);
    map<string, string> credentials = getAllCredentials(CREDENTIAL_FILE_NAME);
    vector<UserStats> userStats = getUserStats(USER_STATS_FILE_NAME);
    string username, password;
    if (argc == 1) {
        // login interface
        int logCounter = 0;
        while (true) {
            loginInterface(username, password);
            if (!checkCredentials(credentials, username, password)) {
                cout << "Incorrect credentials..." << endl;
                if (logCounter == 2){
                    break;
                }
                logCounter++;
                continue;
            }
            break;
        }
        //UserInterface userIface;
    } else if (in.cmdOptionExists("-s") && argc == 3) {
        Service serviceTeam;
        try {
            serviceTeam = getServiceTeam(admin.serviceTeams, argv[2]);
        }
        catch (invalid_argument) {
            cout << "Invalid identifier" << endl;
            return 1;
        }
        ServiceInterface iface(serviceTeam);
        iface.mainInterface();
    } else if (argc == 3) {
        // logged user interface
        username = argv[1];
        password = argv[2];
        if (!checkCredentials(credentials, username, password)) {
            cout << "Incorrect credentials" << endl;
        } else {
            int userIndex = findUser(userStats, username);
            if (userStats[userIndex].userClass == "Standard"){
                StandardUser user(username, userLocation);
                initPreviousSession(userStats[userIndex], &user);
                UserInterface userIface(stations, locations, &user);
                userIface.mainInterface();
            }
            else if (userStats[userIndex].userClass == "Silver"){
                SilverUser user(username, userLocation);
                initPreviousSession(userStats[userIndex], &user);
                UserInterface userIface(stations, locations, &user);
                userIface.mainInterface();
            }
            else {
                GoldenUser user(username, userLocation);
                initPreviousSession(userStats[userIndex], &user);
                UserInterface userIface(stations, locations, &user);
                userIface.mainInterface();
            }

        }
    } else {
        cout << "Incorrect init value" << endl;
    }

    // PREVENTING MEMORY LEAK
    for (auto station : stations) {
        for (auto vehicle : *station) {
            delete vehicle;
        }
        delete station;
    }

    return 0;
}
