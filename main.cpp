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

using namespace std;

const string STATIONS_DATA_PATH = "../data/stationsData";
const string CREDENTIAL_FILE_NAME = "../data/credentials.txt";
const string SERVICE_CREW_FILE_NAME = "../data/serviceCrewAssignment.txt";
const string FILENAMES[] = {"/station1.txt", "/station2.txt", "/station3.txt", "/station4.txt", "/station5.txt"};

int main(int argc, char **argv) {
    // DATA
    vector < string > filenames;
    for (const auto& filename : FILENAMES) {
        filenames.push_back(STATIONS_DATA_PATH + filename);
    }
    DataParser data(filenames);
    vector < Station* > stations = data.getAllStations();
    vector < Service > serviceCrews = DataParser::assignStationsToServiceCrews(SERVICE_CREW_FILE_NAME, stations);
    AdminService admin("X01", serviceCrews);

    // roboczo - LOCATIONS DATA
    vector<Location> locations;
    //map<int, string> districts = {{0, "Ursynow"}, {1, "Wilanow"}, {2, "Mokotow"}, {4, "Wlochy"}, {5, "Ursus"}, {6, "Ochota"}, {7, "Srodmiescie"}, {8, "Wola"}, {9, "Bemowo"}, {10, "Zoliborz"}, {11, "Bielany"}, {12, "Wawer"}, {13, "Wesola"}, {14, "Rembertow"}, {15, "Praga Polodnie"}, {16, "Praga Polnoc"}, {17, "Targowek"}, {18, "Bialoleka"}};
    map<string, int> streetOccurences;

    // (0,0) w lewym dolnym rogu
    for (int y = 0; y < 50; y++){
        for (int x = 0; x < 50; x++){
            string district, street_name, street_number;

            if (x < 10 && y < 20){
                district = "Ursus"; street_name = "Kolorowa";
            }
            else if (x < 15 && y < 20) {
                district = "Wlochy"; street_name = "Aleja Krakowska";
            }
            else if (x < 30 && y < 15) {
                district = "Ursynow"; street_name = "Plaskowicka";
            }
            else if (x < 40 && y < 15) {
                district = "Wilanow"; street_name = "Klimczaka";
            }
            else if (x < 30 && y < 20) {
                district = "Mokotw"; street_name = "Pulawska";
            }
            else if (x < 20 && y < 25) {
                district = "Ochota"; street_name = "Grojewska";
            }
            else if (x < 10 && y < 35) {
                district = "Bemowo"; street_name = "Powstancow Slaskich";
            }
            else if (x < 20 && y < 30) {
                district = "Wola"; street_name = "Kasprzaka";
            }
            else if (x < 25 && y < 30) {
                district = "Srodmiescie"; street_name = "Marszalkowska";
            }
            else if (x < 20 && y < 35) {
                district = "Zoliborz"; street_name = "Mickiewicza";
            }
            else if (x < 15 && y < 50) {
                district = "Bielany"; street_name = "Radiowa";
            }
            else if (x < 50 && y < 25) {
                district = "Wawer"; street_name = "Patriotow";
            }
            else if (x < 35 && y < 30) {
                district = "Praga Polodnie"; street_name = "Ostrobramska";
            }
            else if (x < 25 && y < 35) {
                district = "Praga Polnoc"; street_name = "Targowa";
            }
            else if (x < 35 && y < 40) {
                district = "Targowek"; street_name = "Swiatowida";
            }
            else if (x < 30 && y < 50) {
                district = "Bialoleka"; street_name = "Modlinska";
            }
            else if (x < 40 && y < 40) {
                district = "Rembertow"; street_name = "Stalowa";
            }
            else if (x < 50 && y < 40) {
                district = "Wesola"; street_name = "Radzymiska";
            }
            else if (x >=30 && y >= 40) {
                district = "Bialoleka"; street_name = "Modlinska";
            }
            else{
                district = "Unknown"; street_name = "Unknown";
            }

            if (streetOccurences.count(street_name) == 0){
                streetOccurences[street_name] = 1;
            } else {
                streetOccurences[street_name]++;
            }
            street_number = to_string(streetOccurences[street_name]);

            Location newLocation("Warsaw", district, street_name, street_number, x, y);
            locations.push_back(newLocation);
        }
    }

//    Location loc1("Warsaw", "Mokotow", "Ogrodowa", "1A", 20, 10);
//    Location loc2("Warsaw", "Mokotow", "Ogrodowa", "10B", 20, 20);
//    Location loc3("Warsaw", "Mokotow", "Ogrodowa", "20C", 20, 30);
//    Location loc4("Warsaw", "Mokotow", "Ogrodowa", "30C", 20, 40);
//    Location loc5("Warsaw", "Mokotow", "Ogrodowa", "40C", 20, 50);
//    Location userLocation("Warsaw", "Srodmiescie", "Senatorska", "2", 30, 1);
//    vector<Location> locations = {loc1, loc2, loc3, loc4, loc5, userLocation};
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
              cout << "x";
//            StandardUser user1("test_username", userLocation);
//            UserInterface userIface(stations, locations, &user1);
//            userIface.mainInterface();
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
