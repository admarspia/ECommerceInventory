#include "HashTable.h"
#include "Utils.h"
#include <functional>


// separating interface froom implementation.
HashTable::HashTable(size_t capacity): capacity(capacity), table(capacity) {}
HashTable::~HashTable() {}

// wrapping the hash function from functional to restrinct capacity.
size_t HashTable::hash(const std::string &s) const { // ensure that method doesn't modify the object.
    std::hash<std::string> h;
    return h(toLower(s)) % capacity;
}

// adding new itemm(Product) using the hash from its name.
void HashTable::insert(const Product &p) {
    auto &bucket = table[hash(p.name)]; // get a list from the vector of lists (1 list contains products with the same name hash).
    bucket.push_back(p); // add the new product to that list
}

// searching for an item(Product) by name
std::vector<Product> HashTable::searchByName(const std::string &name) {
    std::vector<Product> res;
    auto &bucket = table[hash(name)]; // get list of products that have the same hash with the provided name.
    std::string lowered = toLower(name);
    for (const auto &p : bucket) {
        if (toLower(p.name).find(lowered) != std::string::npos) res.push_back(p); // get sepecific product with the given name.
    }
    return res;
}

// find item(Product) by name, id and remove
void HashTable::removeByName(const std::string &name, int id) {
    auto &bucket = table[hash(name)];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) { // iterate through all products of the hash(name) 
        if (it->id == id) { bucket.erase(it); return; } // find the one that mach the id and remove it.
    }
}

// show get all products from the products table.
std::vector<Product> HashTable::allProducts() {
    std::vector<Product> out;
    for (auto &bucket : table) for (auto &p : bucket) out.push_back(p);
    return out;
}



