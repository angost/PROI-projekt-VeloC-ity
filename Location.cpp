#include "Location.h"

Location::Location(string city, string district, string street_name, string street_number, int x_coord, int y_coord) {
	this->city = city;
	this->district = district;
	this->street_name = street_name;
	this->street_number = street_number;
	this->x_coord = x_coord;
	this->y_coord = y_coord;
}