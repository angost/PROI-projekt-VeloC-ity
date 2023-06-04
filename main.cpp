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
    vector<Vehicle *> vec;
    MainStation myMainStation("testname", "A01", Location("Warsaw", "Mokotow", "Ogrodowa", "1A", 0, 10), vec);
    Bike bike(1);
    Scooter scooter(2);
    myMainStation.addToStation(&bike);
    myMainStation.addToStation(&scooter);

    vector<Vehicle *> vecSub;
    SubStation mySubStation("testnameSub", "B01", Location("Warsaw", "Mokotow", "Ogrodowa", "1B", 0, 20), vecSub);
    Bike bikeSub(3);
    Scooter scooterSub(4);
    mySubStation.addToStation(&bikeSub);
    mySubStation.addToStation(&scooterSub);

    vector<Vehicle *> vecLocal;
    LocalStation myLocalStation("testnameLoc", "C01", Location("Warsaw", "Mokotow", "Ogrodowa", "1C", 0, 30), vecLocal);
    Bike bikeLocal(5);
    Scooter scooterLocal(6);
    myLocalStation.addToStation(&bikeLocal);
    myLocalStation.addToStation(&scooterLocal);

    vector < Station* > stations = {&myMainStation, &mySubStation, &myLocalStation};
    Service serviceTeam("S01", stations);




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
    } else if (in.cmdOptionExists("-s")) {
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
