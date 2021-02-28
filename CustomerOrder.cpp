// Name: German Malikov
// Student ID: 130968191
// Email: gmalikov@myseneca.ca
// Date: 29-11-2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <algorithm>
#include <iomanip>
#include "CustomerOrder.h"

CustomerOrder::CustomerOrder()
{
	m_cntItem = 0;
	m_lstItem = nullptr;
}

CustomerOrder::CustomerOrder(std::string& record)
{
	Utilities util;
	bool more = true;
	size_t start = 0, num_of_items = 0;
	try {
		m_name = util.extractToken(record, start, more);
		m_product = util.extractToken(record, start, more);
		std::string left = record.substr(start);
		num_of_items = std::count(left.begin(), left.end(), util.getDelimiter()) + 1;
		m_lstItem = new Item * [num_of_items];
		m_cntItem = num_of_items;
		for (size_t i = 0; i < num_of_items; i++) {
			m_lstItem[i] = new Item(util.extractToken(record, start, more));
		}
		if (m_widthField < util.getFieldWidth())
			m_widthField = util.getFieldWidth();
	}
	catch (const char* msg) {
		std::cerr << msg << std::endl;
	}
}

CustomerOrder::CustomerOrder(const CustomerOrder& order)
{
	throw std::exception();
}

CustomerOrder::CustomerOrder(CustomerOrder&& ord) noexcept
{
	*this = std::move(ord);
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& ord) noexcept
{
	if (this != &ord) {
		if (m_lstItem != nullptr) {
			for (size_t i = 0; i < m_cntItem; i++) {
				if (m_lstItem[i] != nullptr) {
					delete m_lstItem[i];
					m_lstItem[i] = nullptr;
				}
			}
			delete[] m_lstItem;
		}
		this->m_name = ord.m_name;
		this->m_product = ord.m_product;
		this->m_cntItem = ord.m_cntItem;
		this->m_widthField = ord.m_widthField;
		this->m_lstItem = std::move(ord.m_lstItem);
		ord.m_lstItem = nullptr;
	}
	// TODO: insert return statement here
	return *this;
}

CustomerOrder::~CustomerOrder()
{
	if (m_lstItem != nullptr) {
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i] != nullptr) {
				delete m_lstItem[i];
				m_lstItem[i] = nullptr;
			}
		}
		delete[] m_lstItem;
	}
}

bool CustomerOrder::isOrderFilled() const
{
	bool filled = true;
	for (size_t pos = 0; pos < m_cntItem; pos++)
		if (!this->m_lstItem[pos]->m_isFilled) {
			filled = false;
			break;
		}
	return filled;
}

bool CustomerOrder::isItemFilled(const std::string& itemName) const
{
	bool filled = true;
	for (size_t pos = 0; pos < m_cntItem; pos++)
		if (itemName == this->m_lstItem[pos]->m_itemName) {
			filled = this->m_lstItem[pos]->m_isFilled;
			break;
		}
	return filled;
}

void CustomerOrder::fillItem(Station& station, std::ostream& os)
{
	size_t pos = 0;
	if (this->m_lstItem != nullptr) {
		for (pos = 0; pos < m_cntItem; pos++) {
			if (station.getItemName() == m_lstItem[pos]->m_itemName) {
				if (station.getQuantity() > 0) {
					station.updateQuantity();
					this->m_lstItem[pos]->m_serialNumber = station.getNextSerialNumber();
					this->m_lstItem[pos]->m_isFilled = true;
					os << "    Filled " << this->m_name << ", " << this->m_product << " ["
						<< station.getItemName() << "]" << std::endl;
				}
				else {
					os << "Unable to fill " << this->m_name << ", " << this->m_product << " ["
						<< station.getItemName() << "]" << std::endl;
				}
			}
		}
	}

}

void CustomerOrder::display(std::ostream& os) const
{
	os << this->m_name << " - " << this->m_product << std::endl;
	for (size_t i = 0; i < m_cntItem; i++) {
		os << "[" << std::setw(6) << std::setfill('0') << std::right << this->m_lstItem[i]->m_serialNumber << std::setfill(' ') << std::left << "] "
			<< std::setw(this->m_widthField) << this->m_lstItem[i]->m_itemName << " - ";
		this->m_lstItem[i]->m_isFilled ? os << "FILLED" : os << "MISSING";
		os << std::endl;
	}
}

size_t CustomerOrder::m_widthField = 0;