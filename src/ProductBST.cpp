#include "Product.h"

#include "ProductBST.h"
#include <iostream>

ProductBST::ProductBST(): root(nullptr) {}

ProductBST::~ProductBST() { destroy(root); }

void ProductBST::destroy(BSTNode *node) { // a private method destroy to crear the bst for start over.
    if (!node) return;
    destroy(node->left);
    destroy(node->right); // destroy evey node recursively.
    delete node;
}


//  inserion implemetation logic used for inserting a node to bst
BSTNode* ProductBST::insertNode(BSTNode* node, const Product &p, bool &inserted) {
    if (!node) {
        inserted = true;
        return new BSTNode(p);// initialize the bst if it was initially empty.
    }
    if (p.id < node->product.id)
        node->left = insertNode(node->left, p, inserted);
    else if (p.id > node->product.id)
        node->right = insertNode(node->right, p, inserted);
    else
        inserted = false; // duplicate id
    return node;
}

// implemet the insert method of bst using the above insertNode method.
bool ProductBST::insert(const Product &p) {
    bool inserted = false;
    root = insertNode(root, p, inserted);
    return inserted;
}

BSTNode* ProductBST::searchByID(int id) {
    BSTNode *cur = root;
    while (cur) { // search the the have of the tree that may contain the product with the given id.
        if (id == cur->product.id) return cur;
        cur = (id < cur->product.id) ? cur->left : cur->right;
    }
    return nullptr;
}

// go to the left most leaf of the bst to find the min
BSTNode* ProductBST::findMin(BSTNode* node) {
    while (node && node->left) node = node->left;
    return node;
}

// use delete by copy to remove the Product from the bst.
BSTNode* ProductBST::removeNode(BSTNode* node, int id, bool &removed) {
    if (!node) return nullptr;
    if (id < node->product.id)
        node->left = removeNode(node->left, id, removed);
    else if (id > node->product.id)
        node->right = removeNode(node->right, id, removed);
    else {
        removed = true;
        if (!node->left) {
            BSTNode* r = node->right; delete node; return r;
        } else if (!node->right) {
            BSTNode* l = node->left; delete node; return l;
        } else {
            BSTNode* mn = findMin(node->right);
            node->product = mn->product;
            node->right = removeNode(node->right, mn->product.id, removed);
        }
    }
    return node;
}

// wrapping the removeNode method to implemet remove.
bool ProductBST::remove(int id) {
    bool removed = false;
    root = removeNode(root, id, removed);
    return removed;
}

// recursively travese through the bst, we used a call back function to make use of the  travese dynamicly on the need.
// based on the defination of the function(fn) it we may want to traverse storing the values to display or do some 
// operation on that node before operation and store the updated (calculated value).
void ProductBST::inorderRec(BSTNode* node, std::function<void(const Product&)> fn) {
    if (!node) return;
    inorderRec(node->left, fn);
    fn(node->product);
    inorderRec(node->right, fn);
}

// use(wrap) inorderRec to implemet inorder.
void ProductBST::inorder(std::function<void(const Product&)> fn) {
    inorderRec(root, fn);
}



