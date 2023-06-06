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
#include "interface/AdminInterface.h"

#include "src/InputParser.h"
#include "data/DataParser.h"
#include "data/setup_functions.h"
#include "data/SaveProgress.h"
#include "data/createAccount.h"

using namespace std;

const string STATIONS_DATA_PATH = "../data/inputTxtFiles/stationsData";
const string CREDENTIAL_FILE_NAME = "../data/inputTxtFiles/credentials.txt";
const string SERVICE_CREW_FILE_NAME = "../data/inputTxtFiles/serviceCrewAssignment.txt";
const string USER_STATS_FILE_NAME = "../data/inputTxtFiles/userstats.txt";
const string USER_LOCATION_FILE_NAME = "../data/inputTxtFiles/userLocation.txt";
const string FILENAMES[] = {"/station1.txt", "/station2.txt", "/station3.txt", "/station4.txt", "/station5.txt", "/station6.txt", "/station7.txt", "/station8.txt", "/station9.txt", "/station10.txt", "/station11.txt", "/station12.txt", "/station13.txt", "/station14.txt", "/station15.txt", "/station16.txt", "/station17.txt", "/station18.txt", "/station19.txt", "/station20.txt", "/station21.txt", "/station22.txt", "/station23.txt", "/station24.txt", "/station25.txt", "/station26.txt", "/station27.txt", "/station28.txt", "/station29.txt", "/station30.txt"};
const string ADMIN_ID = "X01";

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
    AdminService admin(ADMIN_ID, serviceCrews, stations);
    Location currentUserLocation = data.getUserLocation(USER_LOCATION_FILE_NAME);

    bool correctUserData = false;

    // ACTUAL MAIN

    InputParser in(argc, argv);
    map<string, string> credentials = getAllCredentials(CREDENTIAL_FILE_NAME);
    vector<UserStats> userStats = getUserStats(USER_STATS_FILE_NAME);
    string username, password;
    char newAccount;
    if (argc == 1) {
        // login interface
        int logCounter = 0;
        bool loginRunning = true;
        while (loginRunning) {
            loginInterface(username, password);
            if (!checkCredentials(credentials, username, password)) {
                cout << "Incorrect credentials..." << endl;
                if (logCounter == 2){
                    loginRunning = false;
                    cout << "Do you want to create account? (y/n) >> ";
                    cin >> newAccount;
                    if (newAccount == 'y'){
                        createAccount();
                        return 0;
                    }
                }
                logCounter++;
            }
            else {
                correctUserData = true;
                loginRunning = false;
            }
        }
    }
    //UserInterface userIface;
    if (in.cmdOptionExists("-s") && argc == 3) {
        Service serviceTeam;
        try {
            serviceTeam = getServiceTeam(admin.serviceTeams, argv[2]);
        }
        catch (invalid_argument& err) {
            cout << "Invalid identifier" << endl;
            return 1;
        }
        ServiceInterface iface(serviceTeam);
        iface.mainInterface();
    } else if (in.cmdOptionExists("-a") && argc == 3) {
        if (!(argv[2] == ADMIN_ID)) {
            cout << "Invalid identifier" << endl;
            return 1;
        }
        AdminInterface iface(admin);
        iface.mainInterface();
    } else if (argc == 3 || correctUserData) {
        // logged user interface
        if (!correctUserData){
            username = argv[1];
            password = argv[2];
        }
        if (!checkCredentials(credentials, username, password)) {
            cout << "Incorrect credentials" << endl;
        } else {
            int userIndex = findUser(userStats, username);
            if (userStats[userIndex].userClass == "Standard"){
                StandardUser user(username, currentUserLocation);
                startSession(userStats[userIndex], &user, stations, locations);
                saveSessionProgress(&user, userIndex, userStats);
            }
            else if (userStats[userIndex].userClass == "Silver"){
                SilverUser user(username, currentUserLocation);
                startSession(userStats[userIndex], &user, stations, locations);
                saveSessionProgress(&user, userIndex, userStats);
            }
            else {
                GoldenUser user(username, currentUserLocation);
                startSession(userStats[userIndex], &user, stations, locations);
                saveSessionProgress(&user, userIndex, userStats);
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
