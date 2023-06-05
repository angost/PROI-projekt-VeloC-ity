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

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;


int main(int argc, char **argv) {
    // DATA
    vector < Vehicle* > mainVeh;
    vector < Vehicle* > subVeh;
    vector < Vehicle* > localVeh;
    MainStation myMainStation("MainStation", "A01", Location("Warsaw", "Mokotow", "Ogrodowa", "1A", 0, 10), mainVeh);
    SubStation mySubStation("SubStation", "B01", Location("Warsaw", "Mokotow", "Ogrodowa", "1B", 0, 20), subVeh);
    LocalStation myLocalStation("LocalStation", "C01", Location("Warsaw", "Mokotow", "Ogrodowa", "1C", 0, 30), localVeh);
    Bike bike1(1);
    Bike bike2(2);
    Bike bike3(3);
    Bike bike4(4);
    Bike bike5(5);
    Bike bike6(6);
    Bike bike7(7);
    Bike bike8(8);
    myLocalStation.addToStation(&bike1);
    myLocalStation.addToStation(&bike2);
    myLocalStation.addToStation(&bike3);
    myLocalStation.addToStation(&bike4);
    myLocalStation.addToStation(&bike5);
    myLocalStation.addToStation(&bike6);
    myLocalStation.addToStation(&bike7);
    myLocalStation.addToStation(&bike8);
    Scooter scooter9(9);
    Scooter scooter10(10);
    Scooter scooter11(11);
    Scooter scooter12(12);
    Scooter scooter13(13);
    Scooter scooter14(14);
    Scooter scooter15(15);
    Scooter scooter16(16);
    mySubStation.addToStation(&scooter9);
    mySubStation.addToStation(&scooter10);
    mySubStation.addToStation(&scooter11);
    mySubStation.addToStation(&scooter12);
    mySubStation.addToStation(&scooter13);
    mySubStation.addToStation(&scooter14);
    mySubStation.addToStation(&scooter15);
    mySubStation.addToStation(&scooter16);
    ElectricScooter elScooter17(17);
    ElectricScooter elScooter18(18);
    ElectricScooter elScooter19(19);
    ElectricScooter elScooter20(20);
    ElectricScooter elScooter21(21);
    ElectricScooter elScooter22(22);
    ElectricScooter elScooter23(23);
    ElectricScooter elScooter24(24);
    myMainStation.addToStation(&elScooter17);
    myMainStation.addToStation(&elScooter18);
    myMainStation.addToStation(&elScooter19);
    myMainStation.addToStation(&elScooter20);
    myMainStation.addToStation(&elScooter21);
    myMainStation.addToStation(&elScooter22);
    myMainStation.addToStation(&elScooter23);
    myMainStation.addToStation(&elScooter24);

    vector < Station* > stations = {&myMainStation, &mySubStation};
    vector < Station* > smallerStations = {&myLocalStation};
    vector < Station* > adminStations;
    Service firstServiceCrew("S01", stations);
    Service secondServiceCrew("S91", smallerStations);
    vector < Service > serviceCrews = {firstServiceCrew, secondServiceCrew};
    AdminService admin("X01", adminStations, serviceCrews);


    // ACTUAL MAIN

    InputParser in(argc, argv);
    map<string, string> credentials = getAllCredentials();
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
        UserInterface userIface;
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
            UserInterface userIface;
        }
    } else {
        cout << "Incorrect init value" << endl;
    }
    return 0;
}
