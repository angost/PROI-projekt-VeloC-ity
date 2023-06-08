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
    vector<string> filenames;
    for (const auto &filename: FILENAMES) {
        filenames.push_back(STATIONS_DATA_PATH + filename);
    }
    DataParser data(filenames, locations);
    vector<Station *> stations = data.getAllStations();
    vector<Service> serviceCrews = DataParser::assignStationsToServiceCrews(SERVICE_CREW_FILE_NAME, stations,
                                                                            locations);
    AdminService admin(ADMIN_ID, serviceCrews, stations, locations);
    Location currentUserLocation = data.getUserLocation(USER_LOCATION_FILE_NAME);

    bool correctUserData = false;

    // ACTUAL MAIN
    InputParser in(argc, argv);
    map<string, string> credentials;
    vector<UserStats> userStats;
    string username, password;
    char newAccount;
    int mainMenuOption = -1;
    string serviceIdentifier;
    string adminIdentifier;


    // Extra launch options from command line
    if (in.cmdOptionExists("-s") && argc == 3){
        serviceIdentifier = argv[2];
        mainMenuOption = 3;
    }
    else if (in.cmdOptionExists("-a") && argc == 3){
        adminIdentifier = argv[2];
        mainMenuOption = 4;
    }

    // MAIN MENU
    while (true) {
        credentials = getAllCredentials(CREDENTIAL_FILE_NAME);
        userStats = getUserStats(USER_STATS_FILE_NAME);

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
            correctUserData = logInInterface(credentials, username, password);
            if (correctUserData) {
                logUserIn(username, currentUserLocation, userStats, stations, locations);
            } else {
                cout << "Failed to log in..." << endl;
                // Set to default values
                mainMenuOption = -1;
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
                cout << "Invalid identifier" << endl;
                // Set to default values
                mainMenuOption = -1;
                serviceIdentifier = "";
                continue;
            }
            ServiceInterface iface(serviceTeam);
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
                cout << "Invalid identifier" << endl;
                // Set to default values
                mainMenuOption = -1;
                adminIdentifier = "";
                continue;
            }
            AdminInterface iface(admin);
            iface.mainInterface();
        }
        // Exit
        else if (mainMenuOption == 5) {
            cout << "Exiting..." << endl;
            break;
        }
        else {
            cout << "Wrong option number" << endl;
        }

        // Set to default values
        mainMenuOption = -1;
        serviceIdentifier = "";
        adminIdentifier = "";
    }


}
//
//    } else if (argc == 3 || correctUserData) {
//        // logged user interface
//        if (!correctUserData){
//            username = argv[1];
//            password = argv[2];
//        }
//        if (!checkCredentials(credentials, username, password)) {
//            cout << "Incorrect credentials" << endl;
//        } else {
//
//
//        }
//    } else {
//        cout << "Incorrect init value" << endl;
//    }
//
//
//    // PREVENTING MEMORY LEAK
//    for (auto station : stations) {
//        for (auto vehicle : *station) {
//            delete vehicle;
//        }
//        delete station;
//    }
//    return 0;
//}