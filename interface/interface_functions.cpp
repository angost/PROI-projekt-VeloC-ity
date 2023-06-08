//
// Created by Adrian Murawski on 30/05/2023.
//
#include "interface_functions.h"

int getMainMenuOption(){
    cout << endl << endl << "VeloC++ity 2023" << endl;
    cout << "-----------------------------" << endl;
    string action;
    cin.clear();
    cout << "       MENU        " << endl;
    cout << "1. Log in (existing User)" << endl;
    cout << "2. Create new account" << endl;
    cout << "3. Service Interface" << endl;
    cout << "3. Admin Interface" << endl;
    cout << "4. EXIT" << endl;

    cout << "Enter number to define action > ";
    cin >> action;
    cout << endl;
    int actionInt = stoi(action);
    return actionInt;
}

void loginInterface(string &username, string &password){
    cout << "Enter username >> ";
    cin >> username;
    cout << "Enter password >> ";
    cin >> password;
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

int log_in(const map <string, string >& credentials, string &username, string &password){
    int logCounter = 0;
    while (logCounter < 3){
        loginInterface(username, password);
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

vector<UserStats> getUserStats(const string &userStatFilename){
    vector<UserStats> stats;

    ifstream file(userStatFilename);

    string line;
    while (getline(file, line)) {
        vector<string> parts = splitString(line);
        string username = parts[0], uClass = parts[1], license = parts[4];
        float balance = stof(parts[3]);
        int vehCounter = stoi(parts[2]);
        UserStats userArguments(username, uClass, vehCounter, balance, license);
        stats.push_back(userArguments);
    }
    return stats;
}

int findUser(vector<UserStats> &stats, const string &username){
    for (int i = 0 ; i < stats.size(); i++){
        if (username == stats[i].username){
             return i;
        }
    }
    throw invalid_argument("User not found");
}

void initPreviousSession(UserStats &stats, User* user){
    user->drivingLicense = stats.drivingLicense;
    user->balance = stats.balance;
    user->vehicleCounter = stats.vehicleCounter;
}

void startSession(UserStats &stats, User* user, vector<Station*> &stations, vector<Location> &locations){
    initPreviousSession(stats, user);
    UserInterface userIface(stations, locations, user);
    userIface.mainInterface();
}
