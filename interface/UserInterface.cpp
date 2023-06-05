//
// Created by Adrian Murawski on 04/06/2023.
//

#include "UserInterface.h"
#include <iostream>

UserInterface::UserInterface(vector<Station *> stations, User *user) : stations(stations), user(user) {
    Velocity vel(stations, user);
    this->velocity = vel;
}

void UserInterface::mainInterface(){
    while (true){
        cout << endl << "-----------------------------------------------------" << endl;
        bool success;
        int option;
        option = 5;
        try {
            option = getAction();
        }
        catch (invalid_argument) {
            cout << "Wrong number..." << endl;
            continue;
        }

        if (option == 1){ // Show all Stations
            printAllStations();
            continue;
        } else if (option == 2){ // Show Vehicles in Station
            Station* chosenStation;
            try {
                chosenStation = getStation();
            } catch (invalid_argument& err){
                cout << err.what() << endl;
                continue;
            }
            printVehiclesInStation(chosenStation);
            continue;
        } else if (option == 3){ // Show nearest Station
            Station* nearestStation = findNearestStation();
            //TODO jak uzyc metody ostream na wskazniku na klase abstrakcyjna? (nie dziala)
            cout << "Nearest station: " << nearestStation->name << " " << nearestStation->code << endl;
            cout << "Distance: " << user->userLocation.getDistanceBetweenLocations(nearestStation->getStationLocation()) << endl;
            continue;
        } else if (option == 4){ // Rent Vehicle
            Station* chosenStation;
            try {
                chosenStation = getStation();
            } catch (invalid_argument& err){
                cout << err.what() << endl;
                continue;
            }
            Vehicle* chosenVehicle;
            try {
                chosenVehicle = getVehicle(chosenStation);
            } catch (invalid_argument& err){
                cout << err.what() << endl;
                continue;
            }
            success = rentVehicle(chosenVehicle, chosenStation);
        } else if (option == 5){ // Reserve Vehicle
            Station* chosenStation;
            try {
                chosenStation = getStation();
            } catch (invalid_argument& err){
                cout << err.what() << endl;
                continue;
            }
            Vehicle* chosenVehicle;
            try {
                chosenVehicle = getVehicle(chosenStation);
            } catch (invalid_argument& err){
                cout << err.what() << endl;
                continue;
            }
            success = reserveVehicle(chosenVehicle, chosenStation);


        } else if (option == 6){ // Return Vehicle
//            Station* chosenStation;
//            try {
//                chosenStation = getStation();
//            } catch (invalid_argument& err){
//                cout << err.what() << endl;
//                continue;
//            }
//            cout << "Which Vehicle do you want to return?" << endl;
//            printRentedVehicles();
//            Vehicle* chosenVehicle;
//            try {
//                vector<Vehicle*> rentedVehicles = user->getRentedVehicles();
//                chosenVehicle = getVehicle(&rentedVehicles);
//            } catch (invalid_argument& err){
//                cout << err.what() << endl;
//                continue;
//            }
//            success = returnVehicle(chosenVehicle, chosenStation);

        } else if (option == 7){ // Cancel Reservation

        } else if (option == 8){ // Show balance
            cout << "Balance: " << user->checkBalance() << endl;
            cout << "Minimum required balance: " << user->checkMinBalance() << endl;
            continue;
        } else if (option == 9){ // Add credits
            float chosenAmount;
            try{
                chosenAmount = getAmount();
            } catch (invalid_argument& err){
                cout << err.what() << endl;
                continue;
            }
            success = addCredits(chosenAmount);

        } else if (option == 10){ // Show rented Vehicles

        } else if (option == 11){ // Show reserved Vehicles

        } else if (option == 12){ // Add driving license

        } else if (option == 13) { // Exit
            break;
        } else {
            cout << "Wrong option..." << endl;
            continue;
        }
        printSuccess(success);
        cout << endl;
    }
}

int UserInterface::getAction(){
    string action;
    cin.clear();
    cout << " 1. Show all Stations      2. Show Vehicles in Station        3. Show nearest Station" << endl;
    cout << " 4. Rent Vehicle           5. Reserve Vehicle                 6. Return Vehicle" << endl;
    cout << " 7. Cancel Reservation     8. Show balance                    9. Add credits" << endl;
    cout << "10. Show rented Vehicles  11. Show reserved Vehicles         12. Add driving license" << endl;
    cout << "13. Exit" << endl;
    cout << "Enter number to define action > ";
    cin >> action;
    cout << endl;
    int actionInt = stoi(action);
    return actionInt;
}

Station* UserInterface::getStation(){
    string code;
    cout << "Enter station code > ";
    cin >> code;
    cout << endl;
    for (auto i : stations){
        if (i->code == code) {
            return i;
        }
    }
    throw invalid_argument("Wrong station code");
}

Vehicle* UserInterface::getVehicle(Station* station){
    string id;
    cout << "Enter vehicle id > ";
    cin >> id;
    cout << endl;
    int id_number = stoi(id);
    for (auto vehicle : *station) {
        if (vehicle->id == id_number) {
            return vehicle;
        }
    }
    throw invalid_argument("Wrong vehicle id");
}

Vehicle* UserInterface::getVehicle(vector<Vehicle*>* vehicles){
    string id;
    cout << "Enter vehicle id > ";
    cin >> id;
    cout << endl;
    int id_number = stoi(id);
    for (auto vehicle : *vehicles) {
        if (vehicle->id == id_number) {
            return vehicle;
        }
    }
    throw invalid_argument("Wrong vehicle id");
}

float UserInterface::getAmount(){
    string amount;
    cout << "Enter amount to add to your account > ";
    cin >> amount;
    cout << endl;
    float amount_number = stof(amount);
    if (amount_number <= 0){
        throw invalid_argument("Amount has to be greater than 0");
    }
    return amount_number;
}

string UserInterface::getDrivingLicence(){
    string drivingLicence;
    cout << "Enter your driving licence data > ";
    cin >> drivingLicence;
    cout << endl;
    return drivingLicence;
}

void UserInterface::printSuccess(bool success){
    if (success) {
        cout << "Operation finished successfully" << endl;
    } else {
        cout << "Something went wrong..." << endl;
    }
}

void UserInterface::printAllStations(){
    for (auto i : stations){
        cout << i->code << " " << i->name << endl;
    }
}

void UserInterface::printVehiclesInStation(Station* station){
    station->printVehiclesInStation();
}

void UserInterface::printBalance(){
    cout << "Your balance: " << user->checkBalance() << endl;
    cout << "Minimum required balance: " << user->checkMinBalance() << endl;
}

void UserInterface::printRentedVehicles() {
    for (auto vehicle : user->getRentedVehicles()) {
        string type;
        if (vehicle->id > 300) {
            type = "ElectricScooter";
        } else if (vehicle->id > 200) {
            type = "Scooter";
        } else if (vehicle->id > 100) {
            type = "Bike";
        } else {
            type = "Unknown";
        }
        cout << "Type: " << type << "   ID: " << vehicle->id;
    }
}

void UserInterface::printReservedVehicles(){
    for (auto vehicle : user->getReservedVehicles()) {
        string type;
        if (vehicle->id > 300) {
            type = "ElectricScooter";
        } else if (vehicle->id > 200) {
            type = "Scooter";
        } else if (vehicle->id > 100) {
            type = "Bike";
        } else {
            type = "Unknown";
        }
        cout << "Type: " << type << "   ID: " << vehicle->id;
    }
}

bool UserInterface::addDrivingLicence(string drivingLicense){
    if (user->type == "Golden"){
        GoldenUser*  goldenUser = dynamic_cast<GoldenUser*>(user);
        goldenUser->addDrivingLicense(drivingLicense);
        return true;
    }
    return false;
}

bool UserInterface::rentVehicle(Vehicle* vehicle, Station* station) {
    return this->velocity.rentVehicle(vehicle, station);
}

bool UserInterface::reserveVehicle(Vehicle* vehicle, Station* station){
    return this->velocity.reserveVehicle(vehicle, station);
}

bool UserInterface::returnVehicle(Vehicle* vehicle, Station* station){
    return this->velocity.returnVehicle(vehicle, station);
}

bool UserInterface::addCredits(float amount){
    return this->velocity.addCredits(amount);
}

bool UserInterface::cancelReservation(Vehicle* vehicle, Station* station){
    return this->velocity.cancelReservation(vehicle, station);
}

Station* UserInterface::findNearestStation(){
    return this->velocity.findNearestStation();
}

map < int, vector < Station* > > UserInterface::calculateDistanceToAllStations(){
    return this->velocity.calculateDistanceToAllStations();
}

