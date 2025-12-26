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
    std::string date; 
    std::vector<OrderItem> items;
    double total;
    OrderNode* next; 
    OrderNode(int id, const std::string &cust, const std::string &date)
        : orderId(id), customer(cust), date(date), total(0.0), next(nullptr) {}
};

class OrderHistory {
public:
    OrderHistory();
    ~OrderHistory();

    void addOrder(OrderNode* order);
    std::vector<OrderNode*> toVector() const; 
    void printAll() const;

private:
    OrderNode* head; 
};

#endif

/*## Note ##
 *
 *  Data structures to help Order Managment and Track Order History
 *  We got 
 *      OrderItem: for storing single OrderItem info
 *      OrderNode: for wrapping all order and facilitate Order Managment.
 *      OrderHistory: to store and display all order History.
 *
 *      head: the History Managment make use of stack data type oreders are added and removed to  and from the end 
 *      so we head is the most recent Order.
 */
