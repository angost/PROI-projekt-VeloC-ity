//
// Created by Adrian Murawski on 04/06/2023.
//

#include "UserInterface.h"
#include "data/SaveProgress.h"
#include <iostream>
#include <algorithm>

// TODO dodac info dlaczego cos sie nie powiodlo (za maly balans itp)
// TODO lepiej, spojniej wyswietlac lokalizacje, pojazdy itd

UserInterface::UserInterface(vector<Station *> stations, vector<Location> locations, User *user, UserStats &userStats, vector<Vehicle*> &rentedVehiclesBuffer, DataParser &data) : stations(stations), locations(locations), user(user), userStats(userStats), rentedVehiclesBuffer(rentedVehiclesBuffer), data(data) {
    Velocity vel(stations, user);
    this->velocity = vel;
    errorInfo = "";
}

void UserInterface::mainInterface(){
    cin.clear();
    cout << endl << "Welcome " << user->username << "!" << endl;
    user->accountStats();
    while (true){
        cout << endl << "----------------------------------------------------------------------------------------------------------------" << endl;
        bool success;
        int option;
        try {
            option = getAction();
        }
        catch (invalid_argument) {
            cout << "Wrong number..." << endl;
            continue;
        }

        // Show all Stations
        if (option == 1){
            printAllStations();
            continue;

        // Show nearest Station
        } else if (option == 2){
            //TODO jak uzyc metody ostream na wskazniku na klase abstrakcyjna? (nie dziala)
            printNearestStation();
            continue;

        // Show Stations by distance
        } else if (option == 3){
            printDistanceToAllStations();
            continue;

        // Show Vehicles on Station
        } else if (option == 4){
            Station* chosenStation;
            try {
                chosenStation = getStation();
            } catch (invalid_argument& err){
                cout << err.what() << endl;
                continue;
            }
            printVehiclesInStation(chosenStation);
            continue;

        // Rent Vehicle
        } else if (option == 5){
            Station* chosenStation;
            try {
                printNearestStation();
                chosenStation = getStation();
            } catch (invalid_argument& err){
                cout << err.what() << endl;
                continue;
            }
            Vehicle* chosenVehicle;
            try {
                printVehiclesInStation(chosenStation);
                chosenVehicle = getVehicle(chosenStation);
            } catch (invalid_argument& err){
                cout << err.what() << endl;
                continue;
            }
            success = rentVehicle(chosenVehicle, chosenStation);
            saveSessionProgress(user, userStats, stations);
            if (success) {
                rentedVehiclesBuffer.push_back(chosenVehicle);
                data.saveRentedVehiclesBuffer(rentedVehiclesBuffer);
                data.removeVehicle(chosenStation, chosenVehicle);
            }

        // Reserve Vehicle
        } else if (option == 6){
            Station* chosenStation;
            try {
                printNearestStation();
                chosenStation = getStation();
            } catch (invalid_argument& err){
                cout << err.what() << endl;
                continue;
            }
            Vehicle* chosenVehicle;
            try {
                printVehiclesInStation(chosenStation);
                chosenVehicle = getVehicle(chosenStation);
            } catch (invalid_argument& err){
                cout << err.what() << endl;
                continue;
            }
            success = reserveVehicle(chosenVehicle, chosenStation);
            if (success){
                saveSessionProgress(user, userStats, stations);
                data.changeVehicleReservedStatus(chosenStation, chosenVehicle);
            }


        // Return Vehicle
        } else if (option == 7){
            vector<Vehicle*> rentedVehicles = user->getRentedVehicles();
            if (rentedVehicles.size() == 0){
                cout << "You don't have any rented vehicles" << endl;
                continue;
            }
            cout << "Which Vehicle do you want to return?" << endl;
            printRentedVehicles();
            Vehicle* chosenVehicle;
            try {
                chosenVehicle = getVehicle(&rentedVehicles);
            } catch (invalid_argument& err){
                cout << err.what() << endl;
                continue;
            }

            Station* chosenStation;
            try {
                chosenStation = getStation();
            } catch (invalid_argument& err){
                cout << err.what() << endl;
                continue;
            }
            success = returnVehicle(chosenVehicle, chosenStation);
            saveSessionProgress(user, userStats, stations);
            if (success){
                rentedVehiclesBuffer.erase(remove(rentedVehiclesBuffer.begin(), rentedVehiclesBuffer.end(), chosenVehicle), rentedVehiclesBuffer.end());
                data.saveRentedVehiclesBuffer(rentedVehiclesBuffer);
                data.addVehicle(chosenStation, chosenVehicle);
            }

        // Cancel Reservation
        } else if (option == 8){
            vector<Vehicle*> reservedVehicles = user->getReservedVehicles();
            if (reservedVehicles.size() == 0){
                cout << "You don't have any reserved vehicles" << endl;
                continue;
            }
            cout << endl << "Which reservation do you want to cancel?" << endl;
            printReservedVehicles();
            Vehicle* chosenVehicle;
            try {
                chosenVehicle = getVehicle(&reservedVehicles);
            } catch (invalid_argument& err){
                cout << err.what() << endl;
                continue;
            }

            success = cancelReservation(chosenVehicle);
            if (success){
                string stationCode = userStats.reservedVehicles[chosenVehicle->id];
                saveSessionProgress(user, userStats, stations);
                data.changeVehicleReservedStatus(stationCode, chosenVehicle);
            }

        // Show rented Vehicles
        } else if (option == 9){
            printRentedVehicles();
            if (user->rentedVehicles.size() == 0){
                cout << "You don't have any rented Vehicles." << endl;
            }
            continue;

        // Show reserved Vehicles
        } else if (option == 10){
            printReservedVehicles();
            if (user->reservedVehicles.size() == 0){
                cout << "You don't have any reserved Vehicles." << endl;
            }
            continue;

        // Show current coords - TODO add to velocity
        } else if (option == 11){
            Location currentLocation = user->getLocation();
            cout << "Current coords:" << endl;
            cout << "x: " << currentLocation.x_coord << " y: " << currentLocation.y_coord << endl;
            continue;

        // Go to coords - TODO add to velocity - podanie x,y, nie dla kazdego x,y jest stacja
        } else if (option == 12) {
            int chosen_x, chosen_y;
            try{
                chosen_x = getCoord("x");
                chosen_y = getCoord("y");
            } catch (invalid_argument& err){
                cout << err.what() << endl;
                continue;
            }

            for (auto loc : locations){
                if (loc.x_coord == chosen_x && loc.y_coord == chosen_y){
                    success = user->changeLocation(loc);
                    break;
                }
            }
            if (success != true){
                cout << "Wrong coordinates " << endl;
                continue;
            }

        // Go to station - TODO add to velocity - podanie stacji, ustawinie lokacji na lokacje stacji
        } else if (option == 13){
            Station* chosenStation;
            try {
                chosenStation = getStation();
            } catch (invalid_argument& err){
                cout << err.what() << endl;
                continue;
            }
            success = user->changeLocation(chosenStation->getStationLocation());

        // Show account info
        } else if (option == 14){
            user->accountStats();
            continue;

        // Show balance
        } else if (option == 15){
            printBalance();
            continue;

        // Add credits
        } else if (option == 16) {
            float chosenAmount;
            try {
                chosenAmount = getAmount();
            } catch (invalid_argument &err) {
                cout << err.what() << endl;
                continue;
            }
            success = addCredits(chosenAmount);

        // Add driving license
        } else if (option == 17) {
            string drivingLicence;
            try{
                drivingLicence = getDrivingLicence();
            } catch (invalid_argument& err){
                cout << err.what() << endl;
                continue;
            }
            success = addDrivingLicence(drivingLicence);

        // Change profile type
        } else if (option == 18) {
            string profileType;
            try{
                profileType = getProfileType();
            } catch (invalid_argument& err){
                cout << err.what() << endl;
                continue;
            }
            success = addDrivingLicence(profileType);

        // EXIT
        } else if (option == 19) {
            cout << "Thank you for using our services" << endl << endl;
            break;

        } else {
            cout << "Wrong option..." << endl;
            continue;
        }
        //TODO dodac kilka z tych metod do Velocity (?) zeby byly mozliwe do zrobienia nie tylko z poziomu interfejsu
        printSuccess(success);
        if (!success)
            cout << errorInfo << endl;
        cout << endl;
    }
}

int UserInterface::getAction(){
    string action;
    cin.clear();
    cout << "       STATIONS                      RENTING                      LOCATIONS                     ACCOUNT" << endl;
    cout << "1. Show all Stations            5. Rent Vehicle                11. Show current coords   14. Show account info " << endl;
    cout << "2. Show nearest Station         6. Reserve Vehicle             12. Go to coords          15. Show balance " << endl;
    cout << "3. Show Stations by distance    7. Return Vehicle              13. Go to station         16. Add credits " << endl;
    cout << "4. Show Vehicles on Station     8. Cancel reservation                                    17. Add driving license " << endl;
    cout << "                                9. Show rented Vehicles                                  18. EXIT " << endl;
    cout << "                               10. Show reserved Vehicles                                         " << endl;

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
    cout << endl << "Enter vehicle id > ";
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

int UserInterface::getCoord(string coord_type){
    string coord;
    cout << "Enter " << coord_type << " coordinate > ";
    cin >> coord;
    cout << endl;
    int coord_number = stoi(coord);
    return coord_number;
}

string UserInterface::getDrivingLicence(){
    if (user->type != "Golden"){
        throw invalid_argument("You have to be Golden User to add driving licence");
    }
    string drivingLicence;
    cout << "Enter your driving licence data > ";
    cin >> drivingLicence;
    cout << endl;
    return drivingLicence;
}

string UserInterface::getProfileType() {
    string profileType;
    cout << "Enter profile type (Standard/Silver/Golden) >> ";
    cin >> profileType;
    cout << endl;
    if (profileType != "Golden" || profileType != "Silver" || profileType != "Standard"){
        throw invalid_argument("Invalid profile type");
    }
    if (user->type == profileType){
        throw invalid_argument("Profile Type has to be different from current one");
    }
    return profileType;
}

void UserInterface::printSuccess(bool success){
    if (success) {
        cout << "Operation finished successfully" << endl;
    } else {
        cout << "Something went wrong..." << endl;
    }
}

void UserInterface::printAllStations(){
    for (auto station : stations){
        Location currentStationLocation = station->getStationLocation();
        cout << station->code << " " << station->name << " - " <<currentStationLocation.city << " "
        << currentStationLocation.district << " ul. " << currentStationLocation.street_name << " "
        << currentStationLocation.street_number << " - (" << currentStationLocation.x_coord << ", "
        << currentStationLocation.y_coord << ")" << endl;
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
        cout << "Type: " << type << "   ID: " << vehicle->id << endl;
    }
}

void UserInterface::printReservedVehicles(){
    for (auto vehicle : user->getReservedVehicles()) {
        cout << "Type: " << vehicle->type << "   ID: " << vehicle->id << endl;
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
    return this->velocity.rentVehicle(vehicle, station, errorInfo);
}

bool UserInterface::reserveVehicle(Vehicle* vehicle, Station* station){
    return this->velocity.reserveVehicle(vehicle, station, errorInfo);
}

bool UserInterface::returnVehicle(Vehicle* vehicle, Station* station){
    return this->velocity.returnVehicle(vehicle, station, errorInfo);
}

bool UserInterface::addCredits(float amount){
    return this->velocity.addCredits(amount);
}

bool UserInterface::cancelReservation(Vehicle* vehicle){
    return this->velocity.cancelReservation(vehicle, errorInfo);
}

void UserInterface::printNearestStation(){
    Station* nearestStation = this->velocity.findNearestStation();
    cout << "Nearest station: " << nearestStation->name << " " << nearestStation->code << endl;
    cout << "Distance: " << user->userLocation.getDistanceBetweenLocations(nearestStation->getStationLocation()) << endl;
}

 void UserInterface::printDistanceToAllStations(){
    map < int, vector < Station* > > distances = this->velocity.calculateDistanceToAllStations();
    for (auto pair : distances) {
        cout << "Distance: " << pair.first << endl << "Stations: " << endl;
        for (auto station : pair.second) {
            cout << "- " << station->name << " " << station->code << endl;
        }
    }
}

