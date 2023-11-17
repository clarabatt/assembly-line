// *****************************************************************************
// Author  : Clara Verena Brito Battesini
// Student ID(s)#: 143430213
// Email        : cverena-brito-battes@senecacollege.ca
// 15/11/2023
//
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
// *****************************************************************************

#include "CustomerOrder.h"

namespace sdds
{
    size_t CustomerOrder::m_widthField = 0;

    CustomerOrder::CustomerOrder()
    {
        m_name = "";
        m_product = "";
        m_cntItem = 0;
        m_lstItem = nullptr;
    };

    CustomerOrder::CustomerOrder(const CustomerOrder &)
    {
        throw "Unable to copy";
    }

    CustomerOrder::CustomerOrder(const std::string &record)
    {
        m_cntItem = 0;
        Utilities util;
        bool more = true;
        size_t pos = 0u;
        int counter = 0;
        while (more)
        {
            counter++;
            try
            {
                std::string token = util.extractToken(record, pos, more);
                if (counter == 1)
                {
                    if (util.getFieldWidth() > m_widthField)
                        m_widthField = util.getFieldWidth();
                    m_name = token;
                }
                else if (counter == 2)
                {
                    m_product = token;
                }
                else
                {
                    addItem(token);
                }
            }
            catch (...)
            {
                more = false;
            }
        }
    };

    CustomerOrder::CustomerOrder(CustomerOrder &&other) noexcept : m_name(std::move(other.m_name)),
                                                                   m_product(std::move(other.m_product)),
                                                                   m_cntItem(other.m_cntItem),
                                                                   m_lstItem(other.m_lstItem)
    {

        other.m_lstItem = nullptr;
        other.m_cntItem = 0;
    };

    CustomerOrder &CustomerOrder::operator=(CustomerOrder &&other) noexcept
    {
        if (this != &other)
        {
            for (size_t i = 0; i < m_cntItem; ++i)
            {
                delete m_lstItem[i];
            }
            delete[] m_lstItem;

            m_name = std::move(other.m_name);
            m_product = std::move(other.m_product);
            m_cntItem = other.m_cntItem;
            m_lstItem = other.m_lstItem;

            other.m_lstItem = nullptr;
            other.m_cntItem = 0;
        }
        return *this;
    };

    CustomerOrder::~CustomerOrder()
    {
        for (size_t i = 0; i < m_cntItem; ++i)
        {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
        m_lstItem = nullptr;
    };

    bool CustomerOrder::isOrderFilled() const
    {
        return std::all_of(m_lstItem, m_lstItem + m_cntItem, [](const Item *item)
                           { return item->m_isFilled; });
    };
    bool CustomerOrder::isItemFilled(const std::string &itemName) const
    {
        auto found = std::find_if(m_lstItem, m_lstItem + m_cntItem, [&itemName](const Item *item)
                                  { return item->m_itemName == itemName && item->m_isFilled; });

        return found != m_lstItem + m_cntItem;
    };
    void CustomerOrder::fillItem(Station &station, std::ostream &os)
    {
        auto it = std::find_if(m_lstItem, m_lstItem + m_cntItem, [&station](const Item *item)
                               { return item->m_itemName == station.getItemName(); });

        if (it != m_lstItem + m_cntItem)
        {
            if (station.getQuantity() > 0)
            {
                (*it)->m_serialNumber = station.getNextSerialNumber();
                (*it)->m_isFilled = true;
                station.updateQuantity();
                os << "    Filled " << m_name << ", " << m_product << " [" << (*it)->m_itemName << "]\n";
            }
            else
            {
                os << "Unable to fill " << m_name << ", " << m_product << " [" << (*it)->m_itemName << "]\n";
            }
        }
    };
    void CustomerOrder::display(std::ostream &os) const
    {
        std::cout << m_name << " - " << m_product << std::endl;
        auto width = m_widthField;
        if (m_lstItem != nullptr)
            std::for_each(m_lstItem, m_lstItem + m_cntItem, [width](const Item *item)
                          { std::cout << "[" << std::setfill('0') << std::setw(6) << item->m_serialNumber << "] ";
                      std::cout << std::setfill(' ')<< std::left << std::setw(width) << item->m_itemName << " - ";
                      std::cout << (item->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl; });
    };

    void CustomerOrder::addItem(const std::string &itemName)
    {
        Item *newItem = new Item(itemName);

        Item **newList = new Item *[m_cntItem + 1];
        for (size_t i = 0; i < m_cntItem; i++)
        {
            newList[i] = m_lstItem[i];
        }
        newList[m_cntItem] = newItem;

        delete[] m_lstItem;
        m_lstItem = newList;
        m_cntItem++;
    }

}