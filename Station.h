// Name: German Malikov
// Seneca Student ID: 130968191
// Seneca email: gmalikov@myseneca.ca
// Date of completion: 2020-11-10
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>
#include <string>
class Station
{
	unsigned int s_id;
	std::string s_name;
	std::string s_description;
	unsigned int serial_num;
	unsigned int items_left;
	static size_t m_widthField;
	static size_t id_generator;
public:
	Station(const std::string);
	const std::string& getItemName() const;
	unsigned int getNextSerialNumber();
	unsigned int getQuantity() const;
	void updateQuantity();
	void display(std::ostream& os, bool full) const;
};

#endif // !SDDS_UTILITIES_H

