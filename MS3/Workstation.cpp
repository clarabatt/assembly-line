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
        }
    };

    bool Workstation::attemptToMoveOrder()
    {
        if (m_orders.empty())
            return false;

        std::string item_name = this->getItemName();

        // std::cout << "--------- attemptToMoveOrder: " << item_name << std::endl;

        // there is stock
        if (getQuantity() == 0)
        {
            // std::cout << " --------- Sem estoque" << std::endl;
            moveOrderToNextStation();
            return true;
        }

        // order can be processed

        if (!m_orders.begin()->itemExists(item_name))
        {
            // std::cout << " --------- Item n está no pedido" << std::endl;
            moveOrderToNextStation();
            return true;
        }

        if (m_orders.begin()->isItemFilled(item_name))
        {
            // std::cout << " --------- Item filled" << std::endl;
            moveOrderToNextStation();
            return true;
        }

        return false;
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

    void Workstation::moveOrderToIncomplete()
    {
        g_incomplete.push_back(std::move(m_orders.front()));
    };
    void Workstation::moveOrderToComplete()
    {
        g_completed.push_back(std::move(m_orders.front()));
    };
    void Workstation::moveOrderToNextStation()
    {
        if (m_pNextStation == nullptr)
        {
            // std::cout << " --------- Mover para global" << std::endl;
            // std::cout << " --------- " << m_orders.empty() << std::endl;
            // m_orders.front().display(std::cout);

            if (m_orders.front().isOrderFilled())
                g_completed.push_back(std::move(m_orders.front()));
            else
                g_incomplete.push_back(std::move(m_orders.front()));
            //            auto it = std::for_each(m_orders.begin(), m_orders.end(), [](CustomerOrder &order)
            //                                    { order.isOrderFilled() ? g_completed.push_back(std::move(order)) : g_incomplete.push_back(std::move(order)); });
        }
        else
        {
            *m_pNextStation += std::move(m_orders.front());
            m_orders.erase(m_orders.begin());
        }
    };

    bool Workstation::checkIfAllOrdersAreCompleted() const
    {
        if (m_orders.empty())
            return true;

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