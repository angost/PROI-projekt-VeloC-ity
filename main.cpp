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

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

const string STATIONS_DATA_PATH = "../data/stationsData";
const string CREDENTIAL_FILE_NAME = "../data/credentials.txt";

int main(int argc, char **argv) {
    // DATA
    vector < string > filenames = {STATIONS_DATA_PATH + "/station1.txt",
                                   STATIONS_DATA_PATH + "/station2.txt",
                                   STATIONS_DATA_PATH + "/station3.txt",
                                   STATIONS_DATA_PATH + "/station4.txt",
                                   STATIONS_DATA_PATH + "/station5.txt"};
    DataParser data(filenames);
    vector < Station* > stations = data.getAllStations();
    vector < Station* > bigCrew = {stations[0], stations[1], stations[2], stations[3], stations[4]};
    vector < Station* > smallCrew = {stations[2]};
    vector < Station* > adminStations;

    Service firstServiceCrew("S01", bigCrew);
    Service secondServiceCrew("S91", smallCrew);
    vector < Service > serviceCrews = {firstServiceCrew, secondServiceCrew};
    AdminService admin("X01", adminStations, serviceCrews);


    // ACTUAL MAIN

    InputParser in(argc, argv);
    map<string, string> credentials = getAllCredentials(CREDENTIAL_FILE_NAME);
    string username, password;
    if (argc == 1) {
        // login interface
        while (true) {
            loginInterface(username, password);
            if (!checkCredentials(credentials, username, password)) {
                cout << "Incorrect credentials..." << endl;
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
            Location userLocation("Warsaw", "Srodmiescie", "Senatorska", "2", 30, 1);
            StandardUser user1("test_username", userLocation);
            UserInterface userIface(stations, &user1);
        }
    } else {
        cout << "Incorrect init value" << endl;
    }
    return 0;
}
