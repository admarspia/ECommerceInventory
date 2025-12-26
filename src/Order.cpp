./include/Order.h
#ifndef ORDER_H
#define ORDER_H

#include "Product.h"
#include <string>
#include <vector>

struct OrderItem {
    int productId;
    std::string productName;
    int quantity;
    double unitPrice;
};

struct OrderNode {
    int orderId;
    std::string customer;
    std::string date; // simple string date
    std::vector<OrderItem> items;
    double total;
    OrderNode* next; // for linked list
    OrderNode(int id, const std::string &cust, const std::string &date)
        : orderId(id), customer(cust), date(date), total(0.0), next(nullptr) {}
};

class OrderHistory {
    public:
        OrderHistory();
        ~OrderHistory();

        void addOrder(OrderNode* order);
        std::vector<OrderNode*> toVector() const; // newest first
        void printAll() const;

    private:
        OrderNode* head; // most recent
};

#endif 
