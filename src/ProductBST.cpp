#include "Product.h"

#include "ProductBST.h"
#include <iostream>

ProductBST::ProductBST(): root(nullptr) {}

ProductBST::~ProductBST() { destroy(root); }

void ProductBST::destroy(BSTNode *node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

BSTNode* ProductBST::insertNode(BSTNode* node, const Product &p, bool &inserted) {
    if (!node) {
        inserted = true;
        return new BSTNode(p);
    }
    if (p.id < node->product.id)
        node->left = insertNode(node->left, p, inserted);
    else if (p.id > node->product.id)
        node->right = insertNode(node->right, p, inserted);
    else
        inserted = false; // duplicate id
    return node;
}

bool ProductBST::insert(const Product &p) {
    bool inserted = false;
    root = insertNode(root, p, inserted);
    return inserted;
}

BSTNode* ProductBST::searchByID(int id) {
    BSTNode *cur = root;
    while (cur) {
        if (id == cur->product.id) return cur;
        cur = (id < cur->product.id) ? cur->left : cur->right;
    }
    return nullptr;
}

BSTNode* ProductBST::findMin(BSTNode* node) {
    while (node && node->left) node = node->left;
    return node;
}

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

bool ProductBST::remove(int id) {
    bool removed = false;
    root = removeNode(root, id, removed);
    return removed;
}

void ProductBST::inorderRec(BSTNode* node, std::function<void(const Product&)> fn) {
    if (!node) return;
    inorderRec(node->left, fn);
    fn(node->product);
    inorderRec(node->right, fn);
}

void ProductBST::inorder(std::function<void(const Product&)> fn) {
    inorderRec(root, fn);
}


