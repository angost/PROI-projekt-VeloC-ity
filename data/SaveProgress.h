//
// Created by k3acp on 06.06.2023.
//

#include "src/user/User.h"
#include "src/UserStats.h"

using namespace std;

#ifndef PROI_PROJEKT_SAVEPROGRESS_H
#define PROI_PROJEKT_SAVEPROGRESS_H


void saveUserStats(User* &user, const int &userIndex, vector<UserStats> &stats);
void saveSessionProgress(User* user, const int &userIndex, vector<UserStats> &stats);


#endif //PROI_PROJEKT_SAVEPROGRESS_H
