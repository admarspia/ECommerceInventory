#ifndef PRODUCT_H
#define PRODUCT_H


#include <string>


struct Product {
    int id;
    std::string name;
    std::string category;
    double price;
    int stock;


    Product() : id(0), name(""), category(""), price(0.0), stock(0) {}
    Product(int id, const std::string &name, const std::string &category, double price, int stock)
        : id(id), name(name), category(category), price(price), stock(stock) {}
};


#endif


/* ## note ##
 * 
 * Product has id, name, category, price and stock 
 * We have overloaded constractor one No-argument and one with arugments of the properties of the Product.
 *
 * /
