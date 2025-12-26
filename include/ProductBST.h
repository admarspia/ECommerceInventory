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

/* ## Note ## 
 *
 *  Binary Search Tree used to manipulate products using their id.
 *  it has methods for inserting, searching, finding min and max, 
 *  removeing and inorder traversing.all the methods but inorder
 *  use the id for product manipulation.inorder take a function 
 *  that takes Product...(see the .cpp file for more detail).
 *  inorderRec function to make recursive inorder traversing.
 *
 */

