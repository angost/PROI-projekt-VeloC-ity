//
// Created by k3acp on 06.06.2023.
//

#include "createAccount.h"
const string USER_STATS_FILE_NAME = "../data/userstats.txt";
const string CREDENTIAL_FILE_NAME = "../data/credentials.txt";

void createAccount(){
    string username, password, type;
    cout << "Creating new abbount" << endl;
    cout << "Enter username >> ";
    cin >> username;
    cout << "Enter password >> ";
    cin >> password;
    cout << "Enter profile type (Standard/Silver/Golden) >> ";
    cin >> type;
    if (type != "Standard" && type!="Silver" && type!="Golden"){
        cout << "Incorrect profile type...";
        return;
    }
    ofstream file1(USER_STATS_FILE_NAME, ios::app);
    file1 << username+' ' << type+" 0 0 None\n";
    file1.close();
    ofstream file2(CREDENTIAL_FILE_NAME, ios::app);
    file2 << username+' ' << password;
    file2.close();
}