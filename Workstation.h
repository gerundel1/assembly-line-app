// Name: German Malikov
// Student ID: 130968191
// Email: gmalikov@myseneca.ca
// Date: 29-11-2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef _WORKSTATION_H
#define _WORKSTATION_H
#include <iostream>
#include <string>
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"
class Workstation :
    public Station
{
    std::deque<CustomerOrder> m_orders;
    Workstation* m_pnextStation;
public:
    Workstation(const std::string);
    Workstation(const Workstation&) = delete;
    Workstation(Workstation&&) = delete;
    Workstation& operator=(const Workstation&) = delete;
    Workstation& operator=(Workstation&&) = delete;
    void runProcess(std::ostream&);
    bool moveOrder();
    void setNextStation(Workstation& station);
    const Workstation* getNextStation() const;
    bool getIfCompleted(CustomerOrder& order);
    void display(std::ostream&) const;
    Workstation& operator+=(CustomerOrder&&);
};
#endif // !_WORKSTATION_H


