#pragma once

#ifndef PROI_VETURILO_VEHICLE_H
#define PROI_VETURILO_VEHICLE_H

#include <string>

using namespace std;

class Location {
private:
	string city;
	string district;
	string street_name;
	string street_number;
	int x_coord;
	int y_coord;
public:
	Location(string city, string district, string street_name, string street_number, int x_coord, int y_coord);
};

#endif //PROI_VETURILO_VEHICLE_H