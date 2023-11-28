// *****************************************************************************
// Author  : Clara Verena Brito Battesini
// Student ID(s)#: 143430213
// Email        : cverena-brito-battes@senecacollege.ca
// 28/11/2023
//
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
// *****************************************************************************

#include "LineManager.h"

namespace sdds
{
    LineManager::LineManager(const std::string &filename, const std::vector<Workstation *> &stations)
    {
        std::ifstream file(filename);
        if (!file)
            throw("Error opening the file: " + filename);

        bool more = true;
        int stations_index = 0;

        while (file and more)
        {
            std::string record;
            getline(file, record);

            Utilities util;
            size_t pos = 0u;

            try
            {
                std::string token = util.extractToken(record, pos, more);
                Workstation *station = new Workstation(token);

                m_activeLine.push_back(std::move(station));

                if (stations_index == 0)
                    m_firstStation = station;
                else
                    m_activeLine[stations_index - 1]->setNextStation(station);

                stations_index++;
            }
            catch (...)
            {
                more = false;
            }
        }

        file.close();
    };

    void LineManager::reorderStations()
    {
        std::vector<Workstation *> reordered;
        Workstation *currentStation = m_firstStation;

        while (currentStation != nullptr)
        {
            reordered.push_back(currentStation);
            currentStation = currentStation->getNextStation();
        }
        m_activeLine = std::move(reordered);
    };

    bool LineManager::run(std::ostream &os){};

    void LineManager::display(std::ostream &os) const {};
}