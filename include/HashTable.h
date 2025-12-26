#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Product.h"
#include <vector>
#include <list>
#include <string>

class HashTable {
public:
    explicit HashTable(size_t capacity = 103);  // prevent implicit conversion since HashTable has 1 arg
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

/*## note ##
 * here we have the hash table to store Product using Product name it includes
 *      insert Product using the hash of the namespace
 *      remove Product by name
 *      get a vector that contains all products
 *
 * we used 2 dimentional matrix for storing the products and a hash function that is used for 
 * insert, search, remove operatins. each row of the vector is a list of products.
 * capacity determines max value of the hash from the hash function. 
 * 
 *
 * /


