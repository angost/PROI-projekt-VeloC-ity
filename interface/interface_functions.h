//
// Created by Adrian Murawski on 30/05/2023.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include "src/station/service/Service.h"
#include "src/UserStats.h"
#include "src/user/User.h"
#include "interface/UserInterface.h"

using namespace std;


#ifndef PROI_PROJEKT_INTERFACE_FUNCTIONS_H
#define PROI_PROJEKT_INTERFACE_FUNCTIONS_H

int getMainMenuOption();
bool checkCredentials(const map <string, string >& credentials, const string& username, const string& password);
map < string, string > getAllCredentials(const string& credentialFilename);
int logInInterface(const map <string, string >& credentials, string &username, string &password);
Service getServiceTeam(const vector < Service >& serviceCrews, const string& id);
vector<UserStats> getUserStats(const string &userStatFilename);
int findUser(vector<UserStats> &stats, const string &username);
void initPreviousSession(UserStats &stats, User* user);
void startSession(UserStats &stats, User* user, vector<Station*> &stations, vector<Location> &locations);
void logUserIn(string username, Location &currentUserLocation, vector<UserStats> &userStats, vector<Station*> &stations, vector<Location> &locations);

#endif //PROI_PROJEKT_INTERFACE_FUNCTIONS_H
