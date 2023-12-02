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

        Utilities util;
        bool more = true;
        size_t next_pos = 0;

        std::string line;

        while (getline(file, line))
        {
            try
            {
                next_pos = 0;
                more = true;
                std::string currentStationName = util.extractToken(line, next_pos, more);
                std::string nextStationName = more ? util.extractToken(line, next_pos, more) : "";

                auto currentIt = std::find_if(stations.begin(), stations.end(),
                                              [&currentStationName](const Workstation *ws)
                                              { return ws->getItemName() == currentStationName; });

                auto nextIt = (!nextStationName.empty()) ? std::find_if(stations.begin(), stations.end(),
                                                                        [&nextStationName](const Workstation *ws)
                                                                        { return ws->getItemName() == nextStationName; })
                                                         : stations.end();

                if (currentIt != stations.end())
                {
                    Workstation *currentStation = new Workstation((*currentIt)->generateStringBluePrint());
                    Workstation *nextStation = nullptr;
                    if (nextIt != stations.end())
                    {
                        nextStation = new Workstation((*nextIt)->generateStringBluePrint());
                    }

                    if (!nextStationName.empty())
                        currentStation->setNextStation(nextStation);

                    m_activeLine.push_back(currentStation);
                    //                    if (!nextStationName.empty())
                    //                        m_activeLine.push_back(nextStation);

                    if (m_firstStation == nullptr)
                    {
                        m_firstStation = currentStation;
                    }
                }
            }
            catch (const std::invalid_argument &e)
            {
                std::cerr << "Error in line " << line << " : " << e.what() << '\n';
            }
        }

        m_cntCustomerOrder = g_pending.size();

        file.close();
    };

    void LineManager::reorderStations()
    {
        if (m_activeLine.empty())
            return;

        std::vector<Workstation *> reordered;
        Workstation *currentStation = m_firstStation;
        Workstation *nextStation = currentStation->getNextStation();
        int counter = m_activeLine.size();

        reordered.push_back(currentStation);
        m_activeLine.erase(std::find(m_activeLine.begin(), m_activeLine.end(), currentStation));

        while (counter-- != 0 && nextStation != nullptr)
        {
            auto it = std::find_if(m_activeLine.begin(), m_activeLine.end(),
                                   [&nextStation](Workstation *ws)
                                   {
                                       return ws->getItemName() == nextStation->getItemName();
                                   });

            if (it != m_activeLine.end())
            {
                nextStation = *it;
                reordered.push_back(nextStation);
                m_activeLine.erase(it);
                currentStation = nextStation;
                // std::cout << "1: " << currentStation->getItemName() << std::endl;
                if (currentStation->getNextStation() != nullptr)
                {
                    nextStation = currentStation->getNextStation();
                    // std::cout << "1: " << nextStation->getItemName() << std::endl;
                }
                else
                {
                    currentStation = m_activeLine.front();
                    // std::cout << "2: " << currentStation->getItemName() << std::endl;
                    if (currentStation->getNextStation() != nullptr)
                        nextStation = currentStation->getNextStation();
                    // std::cout << "2: " << nextStation->getItemName() << std::endl;
                }
            }
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