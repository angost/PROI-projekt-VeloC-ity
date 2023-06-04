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
using namespace std;


#ifndef PROI_PROJEKT_INTERFACE_FUNCTIONS_H
#define PROI_PROJEKT_INTERFACE_FUNCTIONS_H

void loginInterface(string &username, string &password);
bool checkCredentials(const map <string, string >& credentials, const string& username, const string& password);
map < string, string > getAllCredentials();
Service getServiceTeam(const vector < Service >& serviceCrews, const string& id);

#endif //PROI_PROJEKT_INTERFACE_FUNCTIONS_H
