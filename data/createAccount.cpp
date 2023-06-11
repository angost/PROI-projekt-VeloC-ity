//
// Created by k3acp on 06.06.2023.
//

#include "createAccount.h"
#include "interface/interface_functions.h"
const string USER_STATS_DIR = "../data/inputTxtFiles/userStats/";
const string CREDENTIAL_FILE_NAME = "../data/inputTxtFiles/credentials.txt";

int createAccount(){
    bool success;
    string username, password, type;
    cout << "Creating new account" << endl;
    cout << "Enter username >> ";
    cin >> username;
    success = checkUsername(username);
    if (!success){
        return 0;
    }

    cout << "Enter password >> ";
    cin >> password;
    success = checkPassword(password);
    if (!success){
        return 0;
    }


    cout << "Enter profile type (Standard/Silver/Golden) >> ";
    cin >> type;
    if (type != "Standard" && type!="Silver" && type!="Golden"){
        cout << "Incorrect profile type...";
        return 0;
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
