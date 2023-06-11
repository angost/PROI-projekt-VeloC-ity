#include <iostream>
#include <vector>

#include "src/vehicle/Vehicle.h"

#include "src/station/station/Station.h"

#include "src/station/service/Service.h"
#include "src/station/service/AdminService.h"

#include "src/user/StandardUser.h"
#include "src/user/SilverUser.h"
#include "src/user/GoldenUser.h"

#include "src/Location.h"

#include "interface/interface_functions.h"
#include "interface/ServiceInterface.h"
#include "interface/AdminInterface.h"

#include "data/InputParser.h"
#include "data/DataParser.h"
#include "data/setup_functions.h"
#include "data/SaveProgress.h"
#include "data/createAccount.h"

using namespace std;

const string STATIONS_DATA_PATH = "../data/inputTxtFiles/stationsData";
const string CREDENTIAL_FILE_NAME = "../data/inputTxtFiles/credentials.txt";
const string SERVICE_CREW_FILE_NAME = "../data/inputTxtFiles/serviceCrewAssignment.txt";
const string USER_STATS_DIR = "../data/inputTxtFiles/userStats/";
const string USER_LOCATION_FILE_NAME = "../data/inputTxtFiles/userLocation.txt";
const string STATION_NAMES_FILE_PATH = "../data/inputTxtFiles/stationNames.txt";
const string ADMIN_ID = "X01";

int main(int argc, char **argv) {
    // LOCATIONS DATA
    vector<Location> locations;
    setupMap(locations);

    // DATA

    DataParser data(STATION_NAMES_FILE_PATH, STATIONS_DATA_PATH, SERVICE_CREW_FILE_NAME, USER_LOCATION_FILE_NAME, locations);
    vector < Station* > stations = data.getAllStations();
    vector < Service > serviceCrews = data.assignStationsToServiceCrews(stations);

    AdminService admin(ADMIN_ID, serviceCrews, stations, locations);
    Location currentUserLocation = data.getUserLocation();

    vector<Vehicle*> rentedVehiclesBuffer = data.getRentedVehiclesBuffer();

    bool correctUserData = false;

    // ACTUAL MAIN
    InputParser in(argc, argv);
    map<string, string> credentials;
    string username, password;
    char newAccount;
    int mainMenuOption = -1;
    string serviceIdentifier;
    string adminIdentifier;


    // Extra launch options from command line
    // Service
    if (in.cmdOptionExists("-s") && argc == 3){
        serviceIdentifier = argv[2];
        mainMenuOption = 3;
    }
    // Admin
    else if (in.cmdOptionExists("-a") && argc == 3){
        adminIdentifier = argv[2];
        mainMenuOption = 4;
    }
    // Login
    else if (argc == 3) {
        username = argv[1];
        password = argv[2];
        mainMenuOption = 1;
    }

    // MAIN MENU
    while (true) {

        // No extra launch option used
        if (mainMenuOption == -1){
            try{
                mainMenuOption = getMainMenuOption();
            } catch (invalid_argument) {
                cout << "Wrong option number" << endl;
                // Set to default values
                mainMenuOption = -1;
                continue;
            }
        }

        // Log in
        if (mainMenuOption == 1) {

            credentials = getAllCredentials(CREDENTIAL_FILE_NAME);
            // No extra launch option used
            if (username == ""){
                correctUserData = logInInterface(credentials, username, password);
            } else {
                correctUserData = checkCredentials(credentials, username, password);
            }

            if (correctUserData) {
                string userStatsFileName = USER_STATS_DIR + username + ".txt";
                UserStats userStats = getUserStats(userStatsFileName);
                rentedVehiclesBuffer = data.getRentedVehiclesBuffer();
                logUserIn(username, currentUserLocation, userStats, stations, locations, rentedVehiclesBuffer, data);
                data.saveRentedVehiclesBuffer(rentedVehiclesBuffer);
//                data.refreshStationsData(stations); TODO odkomntowac

            } else {
                cout << "Failed to log in..." << endl;
                // Set to default values
                mainMenuOption = -1;
                username = "";
                password = "";
                continue;
            }
        }
        // Create new account
        else if (mainMenuOption == 2) {
            createAccount();
        }
        // Service Interface
        else if (mainMenuOption == 3) {
            // No extra launch option used
            if (serviceIdentifier == ""){
                cout << "Enter service identifier > ";
                cin >> serviceIdentifier;
            }

            Service serviceTeam;
            try {
                serviceTeam = getServiceTeam(admin.serviceTeams, serviceIdentifier);
            }
            catch (invalid_argument& err) {
                cout << "Invalid service identifier" << endl;
                // Set to default values
                mainMenuOption = -1;
                serviceIdentifier = "";
                continue;
            }
            ServiceInterface iface(serviceTeam, data);
            iface.mainInterface();
        }
        // Admin Interface
        else if (mainMenuOption == 4){
            // No extra launch option used
            if (adminIdentifier == ""){
                cout << "Enter admin identifier > ";
                cin >> adminIdentifier;
            }

            if (adminIdentifier != ADMIN_ID) {
                cout << "Invalid admin identifier" << endl;
                // Set to default values
                mainMenuOption = -1;
                adminIdentifier = "";
                continue;
            }
            AdminInterface iface(admin, data);
            iface.mainInterface();
        }
        // Exit
        else if (mainMenuOption == 5) {
            cout << "Exiting..." << endl;
            break;
        }
        else {
            cout << "Wrong option number..." << endl;
        }

        // Set to default values
        mainMenuOption = -1;
        serviceIdentifier = "";
        adminIdentifier = "";
        username = "";
        password = "";
    }

    //data.refreshStationsData(stations);
    // PREVENTING MEMORY LEAK
    for (auto station : stations) {
        for (auto vehicle : *station) {
            delete vehicle;
        }
        delete station;
    }


    return 0;
}
