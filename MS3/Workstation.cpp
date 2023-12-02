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
    std::vector<CustomerOrder> g_pending;
    std::vector<CustomerOrder> g_completed;
    std::vector<CustomerOrder> g_incomplete;

    Workstation::Workstation(const std::string &str) : Station(str){};

    void Workstation::fill(std::ostream &os)
    {
        if (!m_orders.empty())
        {
            m_orders.front().fillItem(*this, os);
//             os << "Order filled: " << (m_orders.front().isItemFilled(this->getItemName()) ? "yes" : "no") << std::endl;
        }
//        os << "No Order in this station " << std::endl;
    };

    bool Workstation::attemptToMoveOrder()
    {
        if (m_orders.empty())
            return false;

        std::string item_name = this->getItemName();

        bool serviceTobeDone = false;
        for (const auto& item : m_orders) {
            if (item.isItemFilled(item_name) && getQuantity() > 0) {
                serviceTobeDone = true;
                break;
            }
        }

        // Something needs service here
        if (serviceTobeDone)
        {
            return false;
        }

        // No more service
        if (!m_pNextStation)
        {
            // std::cout << "No next station. Moving order to completed or incomplete." << std::endl;
            if (m_orders.front().isOrderFilled())
                g_completed.push_back(std::move(m_orders.front()));
            else
                g_incomplete.push_back(std::move(m_orders.front()));
            return true;
        }
        else
        {
            // std::cout << "Moving order to next station: " << m_pNextStation->getItemName() << std::endl;
            *m_pNextStation += std::move(m_orders.front());
            m_orders.erase(m_orders.begin());
            return true;
        }
    };

    void Workstation::setNextStation(Workstation *station)
    {
        m_pNextStation = station;
    };

    Workstation *Workstation::getNextStation() const
    {
        return m_pNextStation;
    };

    void Workstation::display(std::ostream &os) const
    {
        std::string item_name = this->getItemName();
        if (m_pNextStation)
        {
            std::string next_item_name = m_pNextStation->getItemName();
            os << item_name << " --> " << next_item_name << std::endl;
        }
        else
        {
            os << item_name << " --> End of Line\n";
        }
    };

    Workstation &Workstation::operator+=(CustomerOrder &&newOrder)
    {
        m_orders.push_back(std::move(newOrder));
        return *this;
    };

    bool Workstation::checkIfAllOrdersAreCompleted() const
    {
        for (const auto &order : m_orders)
        {
            if (!order.isOrderFilled())
            {
                return false;
            }
        }
        return true;
    }

}