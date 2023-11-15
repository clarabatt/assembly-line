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
    CustomerOrder::CustomerOrder(){

    };

    CustomerOrder::CustomerOrder(const std::string &record)
    {
        Utilities util;
        bool more = true; // if there are more tokens in the input string
        size_t pos = 0u;  // position of the next token in the input string
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
                    m_product = token;
                else
                    addItem(token);
            }
            catch (...)
            {
                std::cout << "   ERROR: No token.\n";
            }
        }
    };

    CustomerOrder::CustomerOrder(CustomerOrder &&other) noexcept
    {
        if (this != &other)
        {
            m_cntItem = other.m_cntItem;

            m_lstItem = other.m_lstItem;

            other.m_lstItem = nullptr;
            other.m_cntItem = 0;
        }
    };

    CustomerOrder &CustomerOrder::operator=(CustomerOrder &&other) noexcept
    {
        if (this != &other)
        {
            delete[] m_lstItem;
            m_cntItem = other.m_cntItem;

            m_lstItem = other.m_lstItem;

            other.m_lstItem = nullptr;
            other.m_cntItem = 0;
        }
        return *this;
    };

    CustomerOrder::~CustomerOrder()
    {
        delete[] m_lstItem;
        m_lstItem = nullptr;
    };

    bool CustomerOrder::isOrderFilled() const
    {
        auto found = std::find_if(m_lstItem, m_lstItem + m_cntItem, [](const Item *item)
                                  { return item->m_isFilled; });

        if (found == m_lstItem + m_cntItem)
            return true;
        return false;
    };
    bool CustomerOrder::isItemFilled(const std::string &itemName) const
    {
        auto found = std::find_if(m_lstItem, m_lstItem + m_cntItem, [&itemName](const Item *item)
                                  { return item->m_itemName == itemName and item->m_isFilled; });

        if (found != m_lstItem + m_cntItem)
            return true;
        return false;
    };
    void CustomerOrder::fillItem(Station &station, std::ostream &os){

    };
    void CustomerOrder::display(std::ostream &os) const {

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