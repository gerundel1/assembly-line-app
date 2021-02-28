// Name: German Malikov
// Student ID: 130968191
// Email: gmalikov@myseneca.ca
// Date: 29-11-2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Workstation.h"

Workstation::Workstation(const std::string str) : Station(str)
{
	m_pnextStation = nullptr;
}

void Workstation::runProcess(std::ostream& os)
{
	if (m_orders.empty())
		return;
	m_orders.front().fillItem(*this, os);
}

bool Workstation::moveOrder()
{
	bool isFilled = false;
		if (!m_orders.empty() && m_orders.front().isItemFilled(getItemName()) && m_pnextStation) {
			*m_pnextStation += std::move(m_orders.front());
			m_orders.pop_front();
			isFilled = true;
		}
	return isFilled;
}

void Workstation::setNextStation(Workstation& station)
{
	m_pnextStation = &station;
} 

const Workstation* Workstation::getNextStation() const
{
	return m_pnextStation;
}

bool Workstation::getIfCompleted(CustomerOrder& order)
{
	bool isFilled = false;
	if (!this->m_orders.empty() && m_orders.back().isOrderFilled()) {
			order = std::move(this->m_orders.front());
			m_orders.pop_front();
			isFilled = true;
	}
	return isFilled;
}

void Workstation::display(std::ostream& os) const
{
	os << this->getItemName() << " --> ";
	m_pnextStation == nullptr ? os << "END OF LINE" : os << m_pnextStation->getItemName();
	os << std::endl;

}

Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
{
	m_orders.push_back(std::move(newOrder));
	// TODO: insert return statement here
	return *this;
}
