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
    CustomerOrder::CustomerOrder(const CustomerOrder &&) noexcept {

    };
    CustomerOrder &CustomerOrder::operator=(const CustomerOrder &&) noexcept {

    };
    CustomerOrder::~CustomerOrder(){

    };
    bool CustomerOrder::isOrderFilled() const {

    };
    bool CustomerOrder::isItemFilled(const std::string &itemName) const {

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