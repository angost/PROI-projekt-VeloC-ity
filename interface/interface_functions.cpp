//
// Created by Adrian Murawski on 30/05/2023.
//
#include "interface_functions.h"
#include "data/SaveProgress.h"
#include "data/setup_functions.h"

int getMainMenuOption(){
    cout << endl << endl << "VeloC++ity 2023" << endl;
    cout << "-----------------------------" << endl;
    string action;
    cin.clear();
    cout << "       MENU        " << endl;
    cout << "1. Log in (existing User)" << endl;
    cout << "2. Create new account" << endl;
    cout << "3. Service Interface" << endl;
    cout << "4. Admin Interface" << endl;
    cout << "5. EXIT" << endl;

    cout << "Enter number to define action > ";
    cin >> action;
    cout << endl;
    int actionInt = stoi(action);
    return actionInt;
}

bool checkCredentials(const map <string, string >& credentials, const string& username, const string& password){
    for (const auto& pair : credentials){
        if (username == pair.first){
            if (password == pair.second) {
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

map < string, string > getAllCredentials(const string& credentialFilename){
    map < string, string > credentials;
    ifstream file(credentialFilename);
    string line;

    while (getline(file, line)) { // Odczytanie kolejnych linii z pliku
        istringstream iss(line);
        string username, password;
        if (iss >> username >> password) {
            credentials[username] = password;
        }
    }
    return credentials;
}

int logInInterface(const map <string, string >& credentials, string &username, string &password){
    int logCounter = 0;
    while (logCounter < 3){

        cout << "Enter username >> ";
        cin >> username;
        cout << "Enter password >> ";
        cin >> password;

        if (!checkCredentials(credentials, username, password)) {
            cout << "Incorrect credentials..." << endl;
            logCounter++;
        } else{
            return 1;
        }
    }
    return 0;
}

Service getServiceTeam(const vector < Service >& serviceCrews, const string& id) {
    for (auto i : serviceCrews) {
        if (i.identifier == id ) {
            return i;
        }
    }
    throw invalid_argument("Invalid identifier");
}

vector<string> splitString(const string& input) {
    vector<std::string> tokens;
    istringstream iss(input);
    string token;

    while (getline(iss, token, ' ')) {
        tokens.push_back(token);
    }

    return tokens;
}

//TODO przeniesc do DataParser
UserStats getUserStats(const string &userStatFilename){

    ifstream file(userStatFilename);

    string line;
    // User info
    getline(file, line);
    vector<string> partsUserInfo = splitString(line);
    string username = partsUserInfo[0], uClass = partsUserInfo[1], license = partsUserInfo[4];
    float balance = stof(partsUserInfo[3]);
    int vehCounter = stoi(partsUserInfo[2]);

    // Reserved Vehicles
    getline(file, line);
    vector<string> partsReservedVehicles = splitString(line);
    int numberOfResVeh = stoi(partsReservedVehicles[0]);
    map<int, string> reservedVehicles;
    for (int vehNr = 0; vehNr < numberOfResVeh; vehNr++){
        int id = stoi(partsReservedVehicles[1+vehNr*2]);
        string stationCode = partsReservedVehicles[1+vehNr*2+1];

        reservedVehicles[id] = stationCode;
    }
    // Rented Vehicles
    getline(file, line);
    vector<string> partsRentedVehicles = splitString(line);
    vector<int> rentedVehiclesIds;
    for (int i = 0; i < partsRentedVehicles.size(); i++){
        if (i==0)
            continue;
        rentedVehiclesIds.push_back(stoi(partsRentedVehicles[i]));
    }

    getline(file, line);
    vector<string> position = splitString(line);
    int x_position = stoi(position[0]);
    int y_position = stoi(position[1]);

    UserStats userStats(username, uClass, vehCounter, balance, license, reservedVehicles, rentedVehiclesIds, x_position, y_position);
    return userStats;
}

//int findUser(vector<UserStats> &stats, const string &username){
//    for (int i = 0 ; i < stats.size(); i++){
//        if (username == stats[i].username){
//             return i;
//        }
//    }
//    throw invalid_argument("User not found");
//}

void initPreviousSession(UserStats &stats, User* &user, vector<Station*> &stations, vector<Vehicle*> rentedVehiclesBuffer){
    user->drivingLicense = stats.drivingLicense;
    user->balance = stats.balance;
    user->vehicleCounter = stats.vehicleCounter;
    //init location
    vector<Location> locations;
    setupMap(locations);
    for (auto loc : locations) {
        if (loc.x_coord == stats.x_position && loc.y_coord == stats.y_position) {
            user->changeLocation(loc);
        }
    }

    user->reservedVehicles.clear();
    // Adds reserved vehicles to user
    for (auto resVeh : stats.reservedVehicles){
        for (auto station : stations){
            // Reserved Vehicle is on this station
            if (station->code == resVeh.second){
                Vehicle* vehicle = station->getVehicleById(resVeh.first);
                user->reserveVehicle(vehicle);
                break;
            }
        }
    }

    user->rentedVehicles.clear();
    // Adds rented vehicles to user
    for (auto rentedVehicleId : stats.rentedVehiclesIds){
        for (auto vehInBuffer : rentedVehiclesBuffer){
            if (vehInBuffer->id == rentedVehicleId){
                user->addVehicle(vehInBuffer);
                break;
            }
        }
    }
}

void startSession(UserStats &userStats, User* &user, vector<Station*> &stations, vector<Location> &locations, vector<Vehicle*> &rentedVehiclesBuffer, DataParser &data){
    UserInterface userIface(stations, locations, user, userStats, rentedVehiclesBuffer, data);
    userIface.mainInterface();
}

void session(UserStats &userStats, User* user, vector<Station*> &stations, vector<Location> &locations, vector<Vehicle*> &rentedVehiclesBuffer, DataParser &data){
    initPreviousSession(userStats, user, stations, rentedVehiclesBuffer);
    startSession(userStats, user, stations, locations, rentedVehiclesBuffer, data);
    saveSessionProgress(user, userStats, stations);

}

void logUserIn(string username, Location &currentUserLocation, UserStats &userStats, vector<Station*> &stations, vector<Location> &locations, vector<Vehicle*> &rentedVehiclesBuffer, DataParser &data){
    string userClass = userStats.userClass;
    if (userClass == "Standard"){
        StandardUser user(username, currentUserLocation);
        session(userStats, &user, stations, locations, rentedVehiclesBuffer, data);
    }
    else if (userClass == "Silver"){
        SilverUser user(username, currentUserLocation);
        session(userStats, &user, stations, locations, rentedVehiclesBuffer, data);
    }
    else {
        GoldenUser user(username, currentUserLocation);
        session(userStats, &user, stations, locations, rentedVehiclesBuffer, data);
    }
}