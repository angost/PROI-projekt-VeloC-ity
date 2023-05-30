#include "vehicle/Vehicle.h"
#include "vehicle/Bike.h"
#include "vehicle/Scooter.h"
#include "vehicle/ElectricScooter.h"

#include "station/station/Station.h"
#include "station/station/MainStation.h"
#include "station/station/SubStation.h"
#include "station/station/LocalStation.h"

#include "station/service/Service.h"
#include "station/service/AdminService.h"

#include "user/User.h"
#include "user/StandardUser.h"
#include "user/SilverUser.h"
#include "user/GoldenUser.h"

#include "Location.h"

#include "Velocity.h"

#include "interface/interface_functions.h"
#include "InputParser.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

int main(int argc, char **argv) {
    InputParser in(argc, argv);
    map<string, string> credentials = getAllCredentials();
    string username, password;
    if (argc == 1) {
        // login interface
        while (true) {
            loginInterface(username, password);
            if (!checkCredentials(credentials, username, password)) {
                cout << "Incorrect credentials" << endl;
                continue;
            }
            break;
        }
        mainScreenInterface();
    } else if (in.cmdOptionExists("-s")) {
        cout << "Service " << endl;
        // service interface
    } else if (argc == 3) {
        // logged user interface
        username = argv[1];
        password = argv[2];
        if (!checkCredentials(credentials, username, password)) {
            cout << "Incorrect credentials" << endl;
        } else {
            mainScreenInterface();
        }
    } else {
        cout << "Incorrect init value" << endl;
    }
    return 0;
}
