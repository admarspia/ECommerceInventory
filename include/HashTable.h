#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Product.h"
#include <vector>
#include <list>
#include <string>

class HashTable {
    public:
        explicit HashTable(size_t capacity = 103);
        ~HashTable();

        void insert(const Product &p); // by name
        std::vector<Product> searchByName(const std::string &name);
        void removeByName(const std::string &name, int id);
        std::vector<Product> allProducts();

    private:
        size_t capacity;
        std::vector<std::list<Product>> table;
        size_t hash(const std::string &s) const;
};

#endif 
