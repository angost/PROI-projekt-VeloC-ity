//
// Created by k3acp on 06.06.2023.
//

#include "SaveProgress.h"
#include <iomanip>
const string USER_STATS_FILE_NAME = "../data/inputTxtFiles/userstats.txt";

void saveUserStats(User* user, UserStats &userStats, vector<Station*>& stations){
    userStats.vehicleCounter = user->vehicleCounter;
    userStats.balance = user->balance;
    userStats.drivingLicense = user->drivingLicense;
    userStats.userClass = user->type;
    map<int, string> newReservedVehicles;
    userStats.reservedVehicles = newReservedVehicles;
    for (auto reservedVehicle : user->reservedVehicles){
        for (auto station : stations){
            if (station->checkIfVehicleInStation(reservedVehicle)){
                userStats.reservedVehicles[reservedVehicle->id] = station->code;
                break;
            }
        }
    }





////    allStats[userIndex].reservedVehicles = user->reservedVehicles;
//    ofstream outputFile(USER_STATS_FILE_NAME);
//    for (const auto& stats : allStats) {
//        outputFile << stats.username+' ' << stats.userClass+' ' << to_string(stats.vehicleCounter)+' ' << to_string(stats.balance)+' ' << stats.drivingLicense;
////        for (auto reservedVehicle : allStats[userIndex].reservedVehicles){
////            outputFile << reservedVehicle->type << ' ' << reservedVehicle->id << ' '; // TODO jeszcze stacja na jakiej jest vehicle
////        }
//        outputFile << '\n';
//    }
//    outputFile.close();
}

void saveSessionProgress(User* user, UserStats &userStats, vector<Station*>& stations){
    saveUserStats(user, userStats, stations);
}