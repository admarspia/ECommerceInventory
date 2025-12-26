#include "Order.h"
#include <iostream>

OrderHistory::OrderHistory(): head(nullptr) {}
OrderHistory::~OrderHistory() {
    OrderNode* cur = head;
    while (cur) {
        OrderNode* nxt = cur->next;
        delete cur;
        cur = nxt;
    }
}

void OrderHistory::addOrder(OrderNode* order) {
    order->next = head;
    head = order;
}

std::vector<OrderNode*> OrderHistory::toVector() const {
    std::vector<OrderNode*> v;
    OrderNode* cur = head;
    while (cur) { v.push_back(cur); cur = cur->next; }
    return v;
}

void OrderHistory::printAll() const {
    OrderNode* cur = head;
    while (cur) {
        std::cout << "Order ID: " << cur->orderId << " Customer: " << cur->customer << " Date: " << cur->date << " Total: " << cur->total << "\n";
        for (const auto &it : cur->items) {
            std::cout << "  - " << it.productName << " x" << it.quantity << " @ " << it.unitPrice << "\n";
        }
        std::cout << "\n";
        cur = cur->next;
    }
}


