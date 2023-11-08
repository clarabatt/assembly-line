// *****************************************************************************
// Author  : Clara Verena Brito Battesini
// Student ID(s)#: 143430213
// Email        : cverena-brito-battes@senecacollege.ca
// 26/10/2023
//
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
// *****************************************************************************

#include "Station.h"

namespace sdds
{
    Station::Station(const std::string &record){};
    const std::string &Station::getItemName() const
    {
        return m_name;
    };
    size_t Station::getNextSerialNumber()
    {
        return m_next_serial_num;
    };
    size_t Station::getQuantity() const
    {
        return m_stock;
    };
    void Station::updateQuantity()
    {
        m_stock > 0 && --m_stock;
    };
    void Station::display(std::ostream &os, bool full) const {};

}