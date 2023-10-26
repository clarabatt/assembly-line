// *****************************************************************************
// Author  : Clara Verena Brito Battesini
// Student ID(s)#: 143430213
// Email        : cverena-brito-battes@senecacollege.ca
// 26/10/2023
//
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
// *****************************************************************************

#include "Utilities.h"

namespace sdds
{
    void Utilities::setFieldWidth(size_t newWidth)
    {
        m_widthField = newWidth;
    };

    size_t Utilities::getFieldWidth() const
    {
        return m_widthField;
    };

    std::string Utilities::extractToken(const std::string &str, size_t &next_pos, bool &more){

    };

    void Utilities::setDelimiter(char newDelimiter)
    {
        m_delimiter = newDelimiter;
    };

    char Utilities::getDelimiter()
    {
        return m_delimiter[0];
    };

}