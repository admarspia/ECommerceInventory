#include "Inventory.h"
#include "Utils.h"
#include <algorithm>
#include <iomanip>

Inventory::Inventory(): bst(), htable(103), nextOrderId(1) {}
Inventory::~Inventory() {}

// add the product to both bst and hash table.
bool Inventory::addProduct(const Product &p) {
    bool ok = bst.insert(p);
    if (ok) htable.insert(p);
    return ok;
}

// remove product using id, for removing the product from the hashtable first find 
// the product using the id from bst and then remove it using the name and id.
bool Inventory::removeProductByID(int id) {
    BSTNode* node = bst.searchByID(id);
    if (!node) return false;
    htable.removeByName(node->product.name, id);
    return bst.remove(id);
}

// use bst to search by id.
Product* Inventory::searchByID(int id) {
    BSTNode* node = bst.searchByID(id);
    return node ? &node->product : nullptr;
}

// use hashtable to search by name.
std::vector<Product> Inventory::searchByName(const std::string &name) {
    return htable.searchByName(name);
}

// get all products of the Inventory using the inorder traversal method of the bst.
// here we use arow fucntion(collector) that collects the products to a vector.
std::vector<Product> Inventory::allProducts() {
    std::vector<Product> out;
    bst.inorder([&out](const Product &p){ out.push_back(p); });
    return out;
}

// traverse through the bst store the values that mach the category in the vector "out".
std::vector<Product> Inventory::filterByCategory(const std::string &cat) {
    std::vector<Product> out;
    std::string lowered = toLower(cat);
    bst.inorder([&](const Product &p){ if (toLower(p.category) == lowered) out.push_back(p); });
    return out;
}

// add the Product to stock when the quantity is less(less can be determid based on user rule).
bool Inventory::restock(int id, int qty) {
    BSTNode* node = bst.searchByID(id);
    if (!node) return false;
    node->product.stock += qty;
    return true;
}

// decrease the quantity of the product if there is enough of it.
bool Inventory::reduceStock(int id, int qty) {
    BSTNode* node = bst.searchByID(id);
    if (!node) return false;
    if (node->product.stock < qty) return false;
    node->product.stock -= qty;
    return true;
}

// take customer(just simple string(name)), vector of OrderItem, and existing OrderHistory.
// cheak if the product in an OrderItem is availabile with enough quantity or order quantity.
// create OrderNode by providing orderId, customer and date.
// initialize total for storing the total price then for each item 
// search Product using id form the bst reduce stock of the Product
// make copy of the item store the name  and price of the item to the copy from the 
// result of Product and incremnt total price of order.
// placeOrder, by adding the item to the list of items of THE OrderNode.
// update OrderHistory.
//
bool Inventory::placeOrder(const std::string &customer, const std::vector<OrderItem> &items, OrderHistory &hist) {
    // Check availability
    for (const auto &it : items) {
        BSTNode* node = bst.searchByID(it.productId);
        if (!node) return false;
        if (node->product.stock < it.quantity) return false;
    }
    // Reduce stock and create order node
    OrderNode* order = new OrderNode(nextOrderId++, customer, "2025-12-04");
    double total = 0.0;
    for (const auto &it : items) {
        BSTNode* node = bst.searchByID(it.productId);
        node->product.stock -= it.quantity;
        OrderItem copy = it;
        copy.productName = node->product.name;
        copy.unitPrice = node->product.price;
        order->items.push_back(copy);
        total += copy.unitPrice * copy.quantity;
    }
    order->total = total;
    hist.addOrder(order);
    return true;
}


