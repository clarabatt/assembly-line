// *****************************************************************************
// Author  : Clara Verena Brito Battesini
// Student ID(s)#: 143430213
// Email        : cverena-brito-battes@senecacollege.ca
// 28/11/2023
//
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
// *****************************************************************************

#ifndef SDDS_LINE_MANAGER_H
#define SDDS_LINE_MANAGER_H

#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "Utilities.h"
#include "Workstation.h"

namespace sdds
{
    class LineManager
    {
        std::vector<Workstation *> m_activeLine;
        size_t m_cntCustomerOrder;
        Workstation *m_firstStation;

    public:
        LineManager(const std::string &file, const std::vector<Workstation *> &stations);
        void reorderStations();
        bool run(std::ostream &os);
        void display(std::ostream &os) const;
    };
}

#endif