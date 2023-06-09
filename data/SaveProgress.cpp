//
// Created by k3acp on 06.06.2023.
//

#include "SaveProgress.h"
#include <iomanip>
const string USER_STATS_DIR = "../data/inputTxtFiles/userStats/";


void updateUserStats(User* user, UserStats &userStats, vector<Station*>& stations){
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
}

void saveUserStats(User* user, UserStats &userStats, vector<Station*>& stations){
    string userStatsFileName = USER_STATS_DIR + userStats.username + ".txt";
    ofstream outputFile(userStatsFileName);
    outputFile << userStats.username+' ' << userStats.userClass+' ' << to_string(userStats.vehicleCounter)+' ' << to_string(userStats.balance)+' ' << userStats.drivingLicense<< '\n';
    // Reserved Vehciles
    outputFile << to_string(userStats.reservedVehicles.size()) << ' ';
    for (auto resVeh : userStats.reservedVehicles){
        string type;
        if (100 <= resVeh.first <= 199)
            type = "Bike";
        else if (200 <= resVeh.first <= 299)
            type = "Scooter";
        else
            type = "Electric Scooter";
        outputFile << type << ' ' << resVeh.first << ' ' << resVeh.second << ' ';
    }
    outputFile << '\n';
    // Rented Vehicles
    outputFile << '0';

    outputFile.close();
}

void saveSessionProgress(User* user, UserStats &userStats, vector<Station*>& stations){
    updateUserStats(user, userStats, stations);
    saveUserStats(user, userStats, stations);
}