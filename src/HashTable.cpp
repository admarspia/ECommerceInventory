#include "HashTable.h"
#include "Utils.h"
#include <functional>

HashTable::HashTable(size_t capacity): capacity(capacity), table(capacity) {}
HashTable::~HashTable() {}

size_t HashTable::hash(const std::string &s) const {
    std::hash<std::string> h;
    return h(toLower(s)) % capacity;
}

void HashTable::insert(const Product &p) {
    auto &bucket = table[hash(p.name)];
    bucket.push_back(p);
}

std::vector<Product> HashTable::searchByName(const std::string &name) {
    std::vector<Product> res;
    auto &bucket = table[hash(name)];
    std::string lowered = toLower(name);
    for (const auto &p : bucket) {
        if (toLower(p.name).find(lowered) != std::string::npos) res.push_back(p);
    }
    return res;
}

void HashTable::removeByName(const std::string &name, int id) {
    auto &bucket = table[hash(name)];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->id == id) { bucket.erase(it); return; }
    }
}

std::vector<Product> HashTable::allProducts() {
    std::vector<Product> out;
    for (auto &bucket : table) for (auto &p : bucket) out.push_back(p);
    return out;
}


