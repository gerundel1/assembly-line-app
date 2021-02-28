// Name: German Malikov
// Seneca Student ID: 130968191
// Seneca email: gmalikov@myseneca.ca
// Date of completion: 2020-11-10
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

Station::Station(const std::string str)
{
	Utilities util;
	bool more = false;
	size_t start = 0;
	try {
		s_name = util.extractToken(str, start, more = true);
		serial_num = std::stoi(util.extractToken(str, start, more = false));
		items_left = std::stoi(util.extractToken(str, start, more = false));
		s_description = util.extractToken(str, start, more = false);
		if (m_widthField < util.getFieldWidth())
			m_widthField = util.getFieldWidth();
		s_id = ++id_generator;
	}
	catch (const char* msg) {
		std::cerr << msg << std::endl;
	}
}

const std::string& Station::getItemName() const
{
	// TODO: insert return statement here
	return s_name;
}

unsigned int Station::getNextSerialNumber()
{
	return serial_num++;
}

unsigned int Station::getQuantity() const
{
	return items_left;
}

void Station::updateQuantity()
{
	if (items_left > 0)
		items_left--;
}

void Station::display(std::ostream& os, bool full) const
{
	os << "[" << std::setw(3) << std::setfill('0') << std::right << s_id << std::setfill(' ') << "] Item: ";
	os << std::setw(m_widthField) << std::left << s_name << " [";
	os << std::setw(6) << std::right << std::setfill('0') << serial_num << std::setfill(' ') << "]";
	if (full) {
		os << " Quantity: " << std::setw(m_widthField) << std::left << items_left << " ";
		os << "Description: " << s_description << std::endl;
	}
	else
		os << std::endl;
}

size_t Station::m_widthField = 0;
size_t Station::id_generator = 0;