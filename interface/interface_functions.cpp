//
// Created by Adrian Murawski on 30/05/2023.
//
#include "interface_functions.h"

string CREDENTIAL_FILE_NAME = "../data/credentials.txt";

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


map < string, string > getAllCredentials(){
    map < string, string > credentials;
    ifstream file(CREDENTIAL_FILE_NAME);
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


Service getServiceTeam(const vector < Service >& serviceCrews, const string& id) {
    for (auto i : serviceCrews) {
        if (i.identifier == id ) {
            return i;
        }
    }
    throw invalid_argument("Invalid identifier");
}