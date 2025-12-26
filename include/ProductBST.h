#ifndef PRODUCTBST_H
#define PRODUCTBST_H

#include "Product.h"
#include <memory>
#include <functional>

struct BSTNode {
    Product product;
    BSTNode *left;
    BSTNode *right;
    BSTNode(const Product &p) : product(p), left(nullptr), right(nullptr) {}
};

class ProductBST {
public:
    ProductBST();
    ~ProductBST();

    bool insert(const Product &p); // insert by ID
    BSTNode* searchByID(int id);
    bool remove(int id);
    void inorder(std::function<void(const Product&)> fn);

private:
    BSTNode *root;
    void destroy(BSTNode *node);
    BSTNode* insertNode(BSTNode* node, const Product &p, bool &inserted);
    BSTNode* findMin(BSTNode* node);
    BSTNode* removeNode(BSTNode* node, int id, bool &removed);
    void inorderRec(BSTNode* node, std::function<void(const Product&)> fn);
};

#endif 
