// Name: German Malikov
// Student ID: 130968191
// Email: gmalikov@myseneca.ca
// Date: 29-11-2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef _CUSTOMERORDER_H
#define _CUSTOMERORDER_H
#include <string>
#include <iostream>
#include "Utilities.h"
#include "Station.h"
struct Item
{
	std::string m_itemName;
	unsigned int m_serialNumber = 0;
	bool m_isFilled = false;
	Item(const std::string& src) : m_itemName(src) {};
};
class CustomerOrder
{
	std::string m_name;
	std::string m_product;
	unsigned int m_cntItem;
	Item** m_lstItem = nullptr;
	static size_t m_widthField;
public:
	CustomerOrder();
	CustomerOrder(std::string& record);
	CustomerOrder(const CustomerOrder&);
	CustomerOrder& operator=(const CustomerOrder&) = delete;
	CustomerOrder(CustomerOrder&& ord) noexcept;
	CustomerOrder& operator=(CustomerOrder&& ord) noexcept;
	~CustomerOrder();
	bool isOrderFilled() const;
	bool isItemFilled(const std::string& itemName) const;
	void fillItem(Station& station, std::ostream& os);
	void display(std::ostream& os) const;
};
#endif // !_CUSTOMERORDER_H


