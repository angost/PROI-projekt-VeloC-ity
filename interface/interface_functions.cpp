//
// Created by Adrian Murawski on 30/05/2023.
//
#include "interface_functions.h"
#include "data/SaveProgress.h"

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
        string type = partsReservedVehicles[1+vehNr*3];
        int id = stoi(partsReservedVehicles[1+vehNr*3+1]);
        string stationCode = partsReservedVehicles[1+vehNr*3+2];

        reservedVehicles[id] = stationCode;
    }

    UserStats userStats(username, uClass, vehCounter, balance, license, reservedVehicles);
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

void initPreviousSession(UserStats &stats, User* user, vector<Station*> stations){
    user->drivingLicense = stats.drivingLicense;
    user->balance = stats.balance;
    user->vehicleCounter = stats.vehicleCounter;

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

}

void startSession(UserStats &stats, User* user, vector<Station*> &stations, vector<Location> &locations){
    initPreviousSession(stats, user, stations);
    UserInterface userIface(stations, locations, user);
    userIface.mainInterface();
}

void logUserIn(string username, Location &currentUserLocation, UserStats &userStats, vector<Station*> &stations, vector<Location> &locations){
    if (userStats.userClass == "Standard"){
        StandardUser user(username, currentUserLocation);
        startSession(userStats, &user, stations, locations);
        saveSessionProgress(&user, userStats, stations);
    }
    else if (userStats.userClass == "Silver"){
        SilverUser user(username, currentUserLocation);
        startSession(userStats, &user, stations, locations);
        saveSessionProgress(&user, userStats, stations);
    }
    else {
        GoldenUser user(username, currentUserLocation);
        startSession(userStats, &user, stations, locations);
        saveSessionProgress(&user, userStats, stations);
    }
}