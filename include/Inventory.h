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

    // Products
    bool addProduct(const Product &p); 
    bool removeProductByID(int id); 
    Product* searchByID(int id);
    std::vector<Product> searchByName(const std::string &name);
    std::vector<Product> filterByCategory(const std::string &cat);
    std::vector<Product> allProducts();

    // Stock management
    bool restock(int id, int qty);
    bool reduceStock(int id, int qty);

    // Orders
    bool placeOrder(const std::string &customer, const std::vector<OrderItem> &items, OrderHistory &hist);

private:
    ProductBST bst;
    HashTable htable;
    int nextOrderId;
};

#endif

/* ## Note ##
 *
 * Here We have the defination of the inventory class the Inventory class is used to for
 * handling Procuct storing removeing , searching by nameor filtering by category, 
 * restocking and reduce Stock on tarnsaction, and finaly handling Orders.
 *
 * it makes use of the data structures bst and hash table and stors next order id.
 * we used hashtable to manipulate product using name and bst using id.
 *
 *
 */
