// *****************************************************************************
// Author  : Clara Verena Brito Battesini
// Student ID(s)#: 143430213
// Email        : cverena-brito-battes@senecacollege.ca
// 26/10/2023
//
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
// *****************************************************************************

#include "Utilities.h"
#include <string>

namespace sdds
{
    std::string Utilities::m_delimiter = "";

    void Utilities::setFieldWidth(size_t newWidth)
    {
        m_widthField = newWidth;
    };

    size_t Utilities::getFieldWidth() const
    {
        return m_widthField;
    };

    std::string Utilities::extractToken(const std::string &str, size_t &next_pos, bool &more)
    {
        if (str.substr(next_pos, 1) == m_delimiter)
        {
            throw "Delimiter at next_pos";
        }

        size_t nextDelimiter = str.find(m_delimiter, next_pos);
        std::string content = str.substr(next_pos, nextDelimiter - next_pos);

        size_t trimStart = content.find_first_not_of(' ');
        size_t trimEnd = content.find_last_not_of(' ');
        content = content.substr(trimStart, trimEnd - trimStart + 1);

        next_pos = nextDelimiter + 1;
        more = nextDelimiter != std::string::npos;

        if (content.size() > m_widthField)
        {
            m_widthField = content.size();
        }
        return content;
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