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
            throw std::runtime_error("Error opening the file: " + filename);

        std::vector<std::string> currentStationNames;
        std::vector<std::string> nextStationNames;

        Utilities util;
        bool more = true;
        size_t next_pos = 0;

        std::string line;

        while (getline(file, line))
        {
            try
            {
                std::string currentStationName = util.extractToken(line, next_pos, more);
                std::string nextStationName = more ? util.extractToken(line, next_pos, more) : "";

                currentStationNames.push_back(currentStationName);
                nextStationNames.push_back(nextStationName);
            }
            catch (const std::invalid_argument& e)
            {
                std::cerr << "Error in line " << line << " : " << e.what() << '\n';
            }
            next_pos = 0;
            more = true;
        }

        for (size_t i = 0; i < currentStationNames.size(); ++i) {
            Workstation* currentStation = nullptr;
            Workstation* nextStation = nullptr;

            // Find the current and next stations from the stations vector
            for (auto &station : stations) {
                if (station->getItemName() == currentStationNames[i]) {
                    currentStation = station;
                }
                if (!nextStationNames[i].empty() && station->getItemName() == nextStationNames[i]) {
                    nextStation = station;
                }
            }

            if (currentStation) {
                currentStation->setNextStation(nextStation);
                if (m_firstStation == nullptr) {
                    m_firstStation = currentStation;
                }
            }
        }

        // Assuming g_pending is a global or accessible variable, update m_cntCustomerOrder
        m_cntCustomerOrder = g_pending.size();

        // Now, populate m_activeLine
        for (auto &station : stations) {
            m_activeLine.push_back(station);
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

    bool LineManager::run(std::ostream &os)
    {
        static size_t iterationCount = 0;
        ++iterationCount;
        os << "Line Manager Iteration: " << iterationCount << std::endl;

        if (!g_pending.empty())
        {
            *m_firstStation += std::move(g_pending.front());
            g_pending.erase(g_pending.begin());
        }

        for (auto &station : m_activeLine)
        {
            station->fill(os);
            station->attemptToMoveOrder();
        }

        bool allOrdersProcessed = std::all_of(m_activeLine.begin(), m_activeLine.end(),
                                              [](const Workstation *ws)
                                              { return ws->checkIfAllOrdersAreCompleted(); });

        return allOrdersProcessed;
    };

    void LineManager::display(std::ostream &os) const
    {
        for (auto &st : m_activeLine)
            st->display(os);
    };
}