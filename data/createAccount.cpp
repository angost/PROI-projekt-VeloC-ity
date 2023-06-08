//
// Created by k3acp on 06.06.2023.
//

#include "createAccount.h"
#include "interface/interface_functions.h"
const string USER_STATS_FILE_NAME = "../data/inputTxtFiles/userstats.txt";
const string CREDENTIAL_FILE_NAME = "../data/inputTxtFiles/credentials.txt";

int createAccount(){
    string username, password, type;
    cout << "Creating new account" << endl;
    cout << "Enter username >> ";
    cin >> username;

    map <string, string> existingUsers =getAllCredentials(CREDENTIAL_FILE_NAME);
    for (auto credentials : existingUsers){
        if (credentials.first == username){
            cout << "Username already in use...";
            return 0;
        }
    }

    cout << "Enter password >> ";
    cin >> password;
    cout << "Enter profile type (Standard/Silver/Golden) >> ";
    cin >> type;
    if (type != "Standard" && type!="Silver" && type!="Golden"){
        cout << "Incorrect profile type...";
        return 0;
    }
    ofstream file1(USER_STATS_FILE_NAME, ios::app);
    file1 << username+' ' << type+" 0 0 None\n";
    file1.close();
    ofstream file2(CREDENTIAL_FILE_NAME, ios::app);
    file2 << username+' ' << password << '\n';
    file2.close();
    cout << "Account created succesfully!";
    return 1;
}