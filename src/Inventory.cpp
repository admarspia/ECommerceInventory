#include "Inventory.h"
#include "Utils.h"
#include <algorithm>
#include <iomanip>

Inventory::Inventory(): bst(), htable(103), nextOrderId(1) {}
Inventory::~Inventory() {}

bool Inventory::addProduct(const Product &p) {
    bool ok = bst.insert(p);
    if (ok) htable.insert(p);
    return ok;
}

bool Inventory::removeProductByID(int id) {
    BSTNode* node = bst.searchByID(id);
    if (!node) return false;
    htable.removeByName(node->product.name, id);
    return bst.remove(id);
}

Product* Inventory::searchByID(int id) {
    BSTNode* node = bst.searchByID(id);
    return node ? &node->product : nullptr;
}

std::vector<Product> Inventory::searchByName(const std::string &name) {
    return htable.searchByName(name);
}

std::vector<Product> Inventory::allProducts() {
    std::vector<Product> out;
    bst.inorder([&out](const Product &p){ out.push_back(p); });
    return out;
}

std::vector<Product> Inventory::filterByCategory(const std::string &cat) {
    std::vector<Product> out;
    std::string lowered = toLower(cat);
    bst.inorder([&](const Product &p){ if (toLower(p.category) == lowered) out.push_back(p); });
    return out;
}

bool Inventory::restock(int id, int qty) {
    BSTNode* node = bst.searchByID(id);
    if (!node) return false;
    node->product.stock += qty;
    return true;
}

bool Inventory::reduceStock(int id, int qty) {
    BSTNode* node = bst.searchByID(id);
    if (!node) return false;
    if (node->product.stock < qty) return false;
    node->product.stock -= qty;
    return true;
}

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

