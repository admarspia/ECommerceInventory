#ifndef INVENTORY_H
#define INVENTORY_H

#include "ProductBST.h"
#include "HashTable.h"
#include "Order.h"
#include <vector>

class Inventory {
    public:
        Inventory();
        ~Inventory();

        // product management
        bool addProduct(const Product &p);
        bool removeProductByID(int id);
        Product* searchByID(int id);
        std::vector<Product> searchByName(const std::string &name);
        std::vector<Product> filterByCategory(const std::string &cat);
        std::vector<Product> allProducts();

        // stock management
        bool restock(int id, int qty);
        bool reduceStock(int id, int qty);

        // placing orders
        bool placeOrder(const std::string &customer, const std::vector<OrderItem> &items, OrderHistory &hist);

    private:
        ProductBST bst;
        HashTable htable;
        int nextOrderId;
};

#endif 
