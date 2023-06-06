//
// Created by Adrian Murawski on 04/06/2023.
//

#include "UserInterface.h"
#include <iostream>

// TODO dodac info dlaczego cos sie nie powiodlo (za maly balans itp)
// TODO lepiej, spojniej wyswietlac lokalizacje, pojazdy itd

UserInterface::UserInterface(vector<Station *> stations, vector<Location> locations, User *user) : stations(stations), locations(locations), user(user) {
    Velocity vel(stations, user);
    this->velocity = vel;
}

void UserInterface::mainInterface(){
    cin.clear();
    cout << endl << "Welcome " << user->username << "!" << endl;
    user->accountStats();
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

        // Show all Stations
        if (option == 1){
            printAllStations();
            continue;

        // Show Vehicles in Station
        } else if (option == 2){
            Station* chosenStation;
            try {
                chosenStation = getStation();
            } catch (invalid_argument& err){
                cout << err.what() << endl;
                continue;
            }
            printVehiclesInStation(chosenStation);
            continue;

        // Show nearest Station
        } else if (option == 3){
            Station* nearestStation = findNearestStation();
            //TODO jak uzyc metody ostream na wskazniku na klase abstrakcyjna? (nie dziala)
            cout << "Nearest station: " << nearestStation->name << " " << nearestStation->code << endl;
            cout << "Distance: " << user->userLocation.getDistanceBetweenLocations(nearestStation->getStationLocation()) << endl;
            continue;

        // Rent Vehicle
        } else if (option == 4){
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

        // Reserve Vehicle
        } else if (option == 5){
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

        // Return Vehicle
        } else if (option == 6){
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

        // Cancel Reservation
        } else if (option == 7){
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

            Station* chosenStation;
            try {
                chosenStation = getStation();
            } catch (invalid_argument& err){
                cout << err.what() << endl;
                continue;
            }
            success = cancelReservation(chosenVehicle, chosenStation);

        // Show rented Vehicles
        } else if (option == 8){
            printRentedVehicles();

        // Show reserved Vehicles
        } else if (option == 9){
            printReservedVehicles();

        // Show balance
        } else if (option == 10){
            cout << "Balance: " << user->checkBalance() << endl;
            cout << "Minimum required balance: " << user->checkMinBalance() << endl;
            continue;

        // Add credits
        } else if (option == 11) {
            float chosenAmount;
            try {
                chosenAmount = getAmount();
            } catch (invalid_argument &err) {
                cout << err.what() << endl;
                continue;
            }
            success = addCredits(chosenAmount);

        // Show current coords
        } else if (option == 12){
            Location currentLocation = user->getLocation();
            cout << "Current coords:" << endl;
            cout << "x: " << currentLocation.x_coord << " y: " << currentLocation.y_coord << endl;
            continue;

        // Show all coords
        } else if (option == 13) {
            for (auto loc : locations){
                cout << "x: " << loc.x_coord << " y: " << loc.y_coord << endl;
            }
            continue;

        // Go to coords
        } else if (option == 14) {
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

        // Go to station
        } else if (option == 15){
            Station* chosenStation;
            try {
                chosenStation = getStation();
            } catch (invalid_argument& err){
                cout << err.what() << endl;
                continue;
            }
            success = user->changeLocation(chosenStation->getStationLocation());

        // Add driving license
        } else if (option == 16) {
            string drivingLicence;
            try{
                drivingLicence = getDrivingLicence();
            } catch (invalid_argument& err){
                cout << err.what() << endl;
                continue;
            }
            success = addDrivingLicence(drivingLicence);

        // Exit
        } else if (option == 17) {
            break;

        } else {
            cout << "Wrong option..." << endl;
            continue;
        }
        //TODO dodac kilka z tych metod do Velocity (?) zeby byly mozliwe do zrobienia nie tylko z poziomu interfejsu
        printSuccess(success);
        cout << endl;
    }
}

int UserInterface::getAction(){
    string action;
    cin.clear();
    cout << " 1. Show all Stations      2. Show Vehicles in Station        3. Show nearest Station" << endl;
    cout << " 4. Rent Vehicle           5. Reserve Vehicle                 6. Return Vehicle" << endl;
    cout << " 7. Cancel Reservation     8. Show rented Vehicles            9. Show reserved Vehicles" << endl;
    cout << "10. Show balance          11. Add credits                    12. Show current coords" << endl;
    cout << "13. Show all coords       14. Go to coords                   15. Go to station" << endl;
    cout << "16. Add driving license   17. Exit" << endl << endl;
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
        cout << "Type: " << type << "   ID: " << vehicle->id << endl;
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
        cout << "Type: " << type << "   ID: " << vehicle->id << endl;
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

 void UserInterface::printDistanceToAllStations(){
    map < int, vector < Station* > > distances = this->velocity.calculateDistanceToAllStations();
    for (auto pair : distances) {
        cout << "Distance: " << pair.first << "Stations: " << endl;
        for (auto station : pair.second) {
            cout << "- " << station->name << " " << station->code << endl;
        }
    }
}

