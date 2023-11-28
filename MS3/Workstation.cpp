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
    Workstation::Workstation(const std::string &str) : Station(str){};

    void Workstation::fill(std::ostream &os){};

    bool Workstation::attemptToMoveOrder(){};

    void Workstation::setNextStation(Workstation *station){};

    Workstation *Workstation::getNextStation() const {};

    void Workstation::display(std::ostream &os) const {};

    Workstation &Workstation::operator+=(CustomerOrder &&newOrder){};

}