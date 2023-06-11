//
// Created by k3acp on 06.06.2023.
//

#include "createAccount.h"
#include "interface/interface_functions.h"
const string USER_STATS_DIR = "../data/inputTxtFiles/userStats/";
const string CREDENTIAL_FILE_NAME = "../data/inputTxtFiles/credentials.txt";

int createAccount(){
    bool success, running = true, nameBool = false, passwordBool = false;
    string username, password, type;
    int tries = 0;
    while (running) {
        if (!nameBool) {
            cout << "Creating new account" << endl;
            cout << "Enter username >> ";
            cin >> username;
            success = checkUsername(username);
            if (!success) {
                tries++;
            } else {
                tries = 0;
                nameBool = true;
            }
        }
        else if (!passwordBool) {
            cout << "Enter password >> ";
            cin >> password;
            success = checkPassword(password);
            if (!success) {
                tries++;
            } else {
                tries = 0;
                passwordBool = true;
            }
        }
        else {
            cout << "Enter profile type (Standard/Silver/Golden) >> ";
            cin >> type;
            if (type != "Standard" && type != "Silver" && type != "Golden") {
                cout << "Incorrect profile type...";
                tries++;
            }
            else {
                running = false;
            }
        }
        if (tries == 3) {
            cout << "Too many tries..." << endl;
            return 0;
        }

    }
    string userStatsFileName = USER_STATS_DIR + username + ".txt";

    ofstream file1(userStatsFileName);
    file1 << username+' ' << type+" 0 0 None\n";
    file1 << "0 \n" << "0 \n";
    file1.close();
    ofstream file2(CREDENTIAL_FILE_NAME, ios::app);
    file2 << username+' ' << password << '\n';
    file2.close();
    cout << "Account created successfully!";
    return 1;
}

bool checkUsername(string &username){
    map <string, string> existingUsers =getAllCredentials(CREDENTIAL_FILE_NAME);
    for (auto credentials : existingUsers){
        if (credentials.first == username){
            cout << "Username already in use...";
            return false;
        }
    }
    int counter = 0;
    for (char sign: username){
        if (sign < 45 || sign > 122){
            cout << "Used forbidden sign in username: '" << sign << "'" << endl;
            return false;
        }
        counter++;
    }
    if (counter < 5){
        cout << "Username should consist of at least 5 characters" << endl;
        return false;
    }
    if (counter > 15){
        cout << "Username should consist of a maximum of 15 characters" << endl;
        return false;
    }
    return true;
}

bool checkPassword(string &password){
    int counter = 0;
    bool upper = false, lower = false, number = false;
    for (char sign: password){
        if (sign > 60 && sign < 123){
            lower = true;
        }
        if (sign > 64 && sign < 91){
            upper = true;
        }
        if (sign > 47 && sign < 58){
            number = true;
        }
        counter++;
    }
    if (!upper) {
        cout << "Password should contain at least one upper letter" << endl;
        return false;
    }
    if (!number) {
        cout << "Password should contain at least one number" << endl;
        return false;
    }
    if (!lower) {
        cout << "Password should contain at least one lower letter" << endl;
        return false;
    }
    if (counter < 8){
        cout << "Password should consist of at least 8 characters" << endl;
        return false;
    }
    if (counter > 25){
        cout << "Password should consist of a maximum of 25 characters" << endl;
        return false;
    }
    return true;
}