#include "Location.h"
#include <algorithm>

Location::Location(string city, string district, string street_name, string street_number, int x_coord, int y_coord) {
	this->city = city;
	this->district = district;
	this->street_name = street_name;
	this->street_number = street_number;
	this->x_coord = x_coord;
	this->y_coord = y_coord;
}

int Location::getDistanceBetweenLocations(Location other) {
    int distance = 0;
    int x_distance = other.x_coord - this->x_coord;
    distance += max(x_distance, -x_distance);
    int y_distance = other.y_coord - this->y_coord;
    distance += max(y_distance, -y_distance);
    return distance;
}