//
// Created by k3acp on 06.06.2023.
//

#include "src/user/User.h"
#include "UserStats.h"

using namespace std;

#ifndef PROI_PROJEKT_SAVEPROGRESS_H
#define PROI_PROJEKT_SAVEPROGRESS_H


void saveUserStats(User* user, UserStats &userStats, vector<Station*>& stations);
void saveSessionProgress(User* user, UserStats &userStats, vector<Station*>& stations);

#endif //PROI_PROJEKT_SAVEPROGRESS_H
