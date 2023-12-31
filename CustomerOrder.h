#ifndef SDDS_CUSTOMER_ORDER_H
#define SDDS_CUSTOMER_ORDER_H

#include <iomanip>
#include <iostream>
#include <algorithm>
#include "Utilities.h"
#include "Station.h"

namespace sdds
{
    struct Item
    {
        std::string m_itemName;
        size_t m_serialNumber{0};
        bool m_isFilled{false};

        Item(const std::string &src) : m_itemName(src){};
    };

    class CustomerOrder
    {
        std::string m_name;
        std::string m_product;
        size_t m_cntItem;
        Item **m_lstItem = {};

        static size_t m_widthField;

    public:
        CustomerOrder();
        CustomerOrder(const std::string &);
        CustomerOrder(CustomerOrder &&) noexcept;
        CustomerOrder &operator=(CustomerOrder &&) noexcept;
        ~CustomerOrder();
        bool isOrderFilled() const;
        bool isItemFilled(const std::string &itemName) const;
        void fillItem(Station &station, std::ostream &os);
        void display(std::ostream &os) const;
        void addItem(const std::string &itemName);
        bool itemExists(const std::string &itemName) const;

        // Delete copy operations
        CustomerOrder(const CustomerOrder &);
        CustomerOrder &operator=(const CustomerOrder &) = delete;
    };
}
#endif