#include "HashTable.h"
#include "Utils.h"
#include <functional>

HashTable::HashTable(size_t capacity): capacity(capacity), table(capacity) {}
HashTable::~HashTable() {}

// used std::hash to get the hash from the name
size_t HashTable::hash(const std::string &s) const {
    std::hash<std::string> h;
    return h(toLower(s)) % capacity;
}

//using the value of the hash(which is int) we can make insertion O(1)
void HashTable::insert(const Product &p) {
    auto &bucket = table[hash(p.name)];
    bucket.push_back(p);
}

//to search from the table of products the hasing algorithm redueses the search from  O(n^2) to O(n)
std::vector<Product> HashTable::searchByName(const std::string &name) {
    std::vector<Product> res;
    auto &bucket = table[hash(name)];
    std::string lowered = toLower(name);
    for (const auto &p : bucket) {
        if (toLower(p.name).find(lowered) != std::string::npos) res.push_back(p);
    }
    return res;
}

// search takes O(n)
void HashTable::removeByName(const std::string &name, int id) {
    auto &bucket = table[hash(name)];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->id == id) { bucket.erase(it); return; }
    }
}

//listing listing all products O(n^2)
std::vector<Product> HashTable::allProducts() {
    std::vector<Product> out;
    for (auto &bucket : table) for (auto &p : bucket) out.push_back(p);
    return out;
}


