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
    Workstation *LineManager::getFirstStation() const
    {
        for (auto &station : m_activeLine)
        {
            bool isNextStation = false;
            for (auto &otherStation : m_activeLine)
            {
                if (otherStation->getNextStation() != nullptr &&
                    otherStation->getNextStation()->getItemName() == station->getItemName())
                {
                    isNextStation = true;
                    break;
                }
            }
            if (!isNextStation)
            {
                return station;
            }
        }
        return nullptr;
    }

    LineManager::LineManager(const std::string &filename, const std::vector<Workstation *> &stations)
    {
        std::ifstream file(filename);
        if (!file)
            throw std::runtime_error("Error opening the file: " + filename);

        Utilities util;
        std::string line;

        while (getline(file, line))
        {
            try
            {
                size_t next_pos = 0;
                bool more = true;

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
                    Workstation *currentStation = *currentIt;
                    Workstation *nextStation = nullptr;

                    if (nextIt != stations.end())
                    {
                        nextStation = *nextIt;
                        currentStation->setNextStation(nextStation);
                    }

                    m_activeLine.push_back(currentStation);
                }
            }
            catch (const std::invalid_argument &e)
            {
                std::cerr << "Error in line: " << line << " : " << e.what() << '\n';
            }
        }

        m_firstStation = getFirstStation();
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
            //            os << "Filling station: " << station->getItemName() << std::endl;
            station->fill(os);
        }

        for (auto &station : m_activeLine)
        {
            //             os << "Moving station: " << station->getItemName() << std::endl;
            station->attemptToMoveOrder();
        }

        bool allStocksAreZero = std::all_of(m_activeLine.begin(), m_activeLine.end(),
                                            [](const Workstation *ws)
                                            {
                                                return ws->getQuantity() == 0;
                                            });

        bool allOrdersFilled = std::all_of(m_activeLine.begin(), m_activeLine.end(),
                                           [](const Workstation *ws)
                                           {
                                               return ws->checkIfAllOrdersAreCompleted();
                                           });

        bool noItemsInPendingQueue = g_pending.empty();

        bool allOrdersProcessed = (allStocksAreZero or allOrdersFilled) && noItemsInPendingQueue;

        // os << "All orders processed: " << (allOrdersProcessed ? "yes" : "no");

         if (iterationCount > 5)
             return true;

        return allOrdersProcessed;
    };

    void LineManager::display(std::ostream &os) const
    {
        for (auto &st : m_activeLine)
            st->display(os);
    };
}