// Name: German Malikov
// Student ID: 130968191
// Email: gmalikov@myseneca.ca
// Date: 29-11-2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"

LineManager::LineManager(std::string file, std::vector<Workstation*>& stations, std::vector<CustomerOrder>& orders)
{
	Utilities util;
	std::ifstream f(file);
	if (f.eof())
		throw std::string("ERROR:  Failed to open the file [") + file + "].";
	size_t next_pos;
	bool more = false;
	std::string next_record;
	std::string station;
	std::string next_station;
	while (f) {
		next_pos = 0;
		std::getline(f, next_record);
		station = util.extractToken(next_record, next_pos, more);
		if (more) {
			next_station = util.extractToken(next_record, next_pos, more = false);
		}
		else{
			next_station = "";
		}
			auto station_pos = std::find_if(stations.begin(), stations.end(), [&](Workstation* currentStation) {
				return currentStation->getItemName() == station;
				});
			if (next_station != "") {
				auto next_station_pos = std::find_if(stations.begin(), stations.end(), [&](Workstation* currentStation) {
					return currentStation->getItemName() == next_station;
					});
				(*station_pos)->setNextStation(*(*next_station_pos));
			}
			if (m_firstStation == nullptr)
				m_firstStation = *station_pos;
	}
	f.close();
	for (auto i = orders.begin(); i != orders.end(); i++) {

		ToBeFilled.push_back(std::move(*i));
	}
	
	m_cntCustomerOrder = ToBeFilled.size();
	AssemblyLine = stations;
}

bool LineManager::run(std::ostream& os)
{
	static size_t counter = 0;
	os << "Line Manager Iteration: " << ++counter << std::endl;

	if (!ToBeFilled.empty()) {
		*m_firstStation += std::move(ToBeFilled.front());
		ToBeFilled.pop_front();
	}

	for (size_t i = 0; i < AssemblyLine.size(); i++)
		AssemblyLine[i]->runProcess(os);

	for (size_t i = 0; i < AssemblyLine.size(); i++)
	{
		AssemblyLine[i]->moveOrder();
		CustomerOrder order;
		if (AssemblyLine[i]->getIfCompleted(order))
			Completed.push_back(std::move(order));
	}

	return Completed.size() == m_cntCustomerOrder;
}

void LineManager::displayCompletedOrders(std::ostream& os) const
{
	for (auto i = Completed.begin(); i != Completed.end(); i++) {
		(*i).display(os);
	}
}

void LineManager::displayStations() const
{
	for (auto i = AssemblyLine.begin(); i != AssemblyLine.end(); i++) {
		(*i)->display(std::cout);
	}
}

void LineManager::displayStationsSorted() const
{
	const Workstation* st1 = m_firstStation;

	do {
		st1->display(std::cout);
		st1 = st1->getNextStation();
	} while (st1 != nullptr);
}
