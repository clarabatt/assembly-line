// *****************************************************************************
// Author  : Clara Verena Brito Battesini
// Student ID(s)#: 143430213
// Email        : cverena-brito-battes@senecacollege.ca
// 28/11/2023
//
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
// *****************************************************************************

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include <iomanip>
#include <vector>
#include <queue>
#include <iostream>
#include "Utilities.h"
#include "CustomerOrder.h"

namespace sdds
{
    extern std::vector<CustomerOrder> g_pending;
    extern std::vector<CustomerOrder> g_completed;
    extern std::vector<CustomerOrder> g_incomplete;

    class Workstation : public Station
    {
        std::vector<CustomerOrder> m_orders = {};
        Workstation *m_pNextStation = nullptr;

    public:
        Workstation(const std::string &);
        void fill(std::ostream &os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation *station);
        Workstation *getNextStation() const;
        void display(std::ostream &os) const;
        Workstation &operator+=(CustomerOrder &&newOrder);
        bool checkIfAllOrdersAreCompleted() const;
    };
}

#endif