//
// Created by angel on 06.06.2023.
//

#include "setup_functions.h"

using namespace std;

void setupMap(vector<Location>& locations){
    map<string, int> streetOccurences;
    //map<int, string> districts = {{0, "Ursynow"}, {1, "Wilanow"}, {2, "Mokotow"}, {4, "Wlochy"}, {5, "Ursus"}, {6, "Ochota"}, {7, "Srodmiescie"}, {8, "Wola"}, {9, "Bemowo"}, {10, "Zoliborz"}, {11, "Bielany"}, {12, "Wawer"}, {13, "Wesola"}, {14, "Rembertow"}, {15, "Praga Polodnie"}, {16, "Praga Polnoc"}, {17, "Targowek"}, {18, "Bialoleka"}};

    // (0,0) w lewym dolnym rogu
    for (int y = 0; y < 50; y++){
        for (int x = 0; x < 50; x++){
            string district, street_name, street_number;

            if (x < 10 && y < 20){
                district = "Ursus"; street_name = "Kolorowa";
            }
            else if (x < 15 && y < 20) {
                district = "Wlochy"; street_name = "Aleja Krakowska";
            }
            else if (x < 30 && y < 15) {
                district = "Ursynow"; street_name = "Plaskowicka";
            }
            else if (x < 40 && y < 15) {
                district = "Wilanow"; street_name = "Klimczaka";
            }
            else if (x < 30 && y < 20) {
                district = "Mokotw"; street_name = "Pulawska";
            }
            else if (x < 20 && y < 25) {
                district = "Ochota"; street_name = "Grojewska";
            }
            else if (x < 10 && y < 35) {
                district = "Bemowo"; street_name = "Powstancow Slaskich";
            }
            else if (x < 20 && y < 30) {
                district = "Wola"; street_name = "Kasprzaka";
            }
            else if (x < 25 && y < 30) {
                district = "Srodmiescie"; street_name = "Marszalkowska";
            }
            else if (x < 20 && y < 35) {
                district = "Zoliborz"; street_name = "Mickiewicza";
            }
            else if (x < 15 && y < 50) {
                district = "Bielany"; street_name = "Radiowa";
            }
            else if (x < 50 && y < 25) {
                district = "Wawer"; street_name = "Patriotow";
            }
            else if (x < 35 && y < 30) {
                district = "Praga Polodnie"; street_name = "Ostrobramska";
            }
            else if (x < 25 && y < 35) {
                district = "Praga Polnoc"; street_name = "Targowa";
            }
            else if (x < 35 && y < 40) {
                district = "Targowek"; street_name = "Swiatowida";
            }
            else if (x < 30 && y < 50) {
                district = "Bialoleka"; street_name = "Modlinska";
            }
            else if (x < 40 && y < 40) {
                district = "Rembertow"; street_name = "Stalowa";
            }
            else if (x < 50 && y < 40) {
                district = "Wesola"; street_name = "Radzymiska";
            }
            else if (x >=30 && y >= 40) {
                district = "Bialoleka"; street_name = "Modlinska";
            }
            else{
                district = "Unknown"; street_name = "Unknown";
            }

            if (streetOccurences.count(street_name) == 0){
                streetOccurences[street_name] = 1;
            } else {
                streetOccurences[street_name]++;
            }
            street_number = to_string(streetOccurences[street_name]);

            Location newLocation("Warsaw", district, street_name, street_number, x, y);
            locations.push_back(newLocation);
        }
    }
}