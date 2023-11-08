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
    Station::Station(){};
    Station::Station(const std::string &record){};
    const std::string &Station::getItemName() const {};
    size_t Station::getNextSerialNumber(){};
    size_t Station::getQuantity() const {};
    void Station::updateQuantity(){};
    void Station::display(std::ostream &os, bool full) const {};

}