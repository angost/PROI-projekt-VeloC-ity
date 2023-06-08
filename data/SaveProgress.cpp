//
// Created by k3acp on 06.06.2023.
//

#include "SaveProgress.h"
#include <iomanip>
const string USER_STATS_FILE_NAME = "../data/inputTxtFiles/userstats.txt";

void saveUserStats(User* &user, const int &userIndex, vector<UserStats> &allStats){
    allStats[userIndex].vehicleCounter = user->vehicleCounter;
    allStats[userIndex].balance = user->balance;
    allStats[userIndex].drivingLicense = user->drivingLicense;
    allStats[userIndex].userClass = user->type;
    allStats[userIndex].reservedVehicles = user->reservedVehicles;
    allStats[userIndex].reservedVehicles = user->reservedVehicles;
    ofstream outputFile(USER_STATS_FILE_NAME);
    for (const auto& stats : allStats) {
        outputFile << stats.username+' ' << stats.userClass+' ' << to_string(stats.vehicleCounter)+' ' << to_string(stats.balance)+' ' << stats.drivingLicense;
//        for (auto reservedVehicle : allStats[userIndex].reservedVehicles){
//            outputFile << reservedVehicle->type << ' ' << reservedVehicle->id << ' '; // TODO jeszcze stacja na jakiej jest vehicle
//        }
        outputFile << '\n';
    }
    outputFile.close();
}

void saveSessionProgress(User* user, const int &userIndex, vector<UserStats> &stats){
    saveUserStats(user, userIndex, stats);
}