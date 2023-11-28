// *****************************************************************************
// Author  : Clara Verena Brito Battesini
// Student ID(s)#: 143430213
// Email        : cverena-brito-battes@senecacollege.ca
// 28/11/2023
//
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
// *****************************************************************************

#include "Workstation.h"

namespace sdds
{
    Workstation::Workstation(const std::string &str) : Station(str){};

    void Workstation::fill(std::ostream &os)
    {
        CustomerOrder *order = new CustomerOrder();
        order->fillItem(*this, os);
        m_orders.push(std::move(*order));
        delete order;
    };

    bool Workstation::attemptToMoveOrder()
    {
        if (m_orders.empty())
            return false;

        CustomerOrder order = m_orders.front();
        std::string item_name = this->getItemName();
        bool noMoreService = order.isOrderFilled() and order.isItemFilled(item_name);
        bool moved = false;
        if (noMoreService)
        {
            if (!m_pNextStation)
            {
                noMoreService ? g_completed.push_back(std::move(order)) : g_incomplete.push_back(std::move(order));
            }
            else
            {
                *m_pNextStation += std::move(order);
            }
            m_orders.pop();
            moved = true;
        }

        return moved;
    };

    void Workstation::setNextStation(Workstation *station)
    {
        m_pNextStation = station;
    };

    Workstation *Workstation::getNextStation() const
    {
        return m_pNextStation;
    };

    void Workstation::display(std::ostream &os) const {};

    Workstation &Workstation::operator+=(CustomerOrder &&newOrder){};

}