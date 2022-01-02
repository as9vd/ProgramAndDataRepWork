// BinarySearchThree.cpp
// October 5th, 20201
// Asadbek Shamsiev, as9vd

#include "BinaryNode.h"
#include "BinarySearchTree.h"
#include <iostream>
#include <string>
#include <stack>
using namespace std;

// 4 default functions to edit: insert(), pathTo(), find(), & numNodes().

BinarySearchTree::BinarySearchTree() {
    root = NULL;
}

BinarySearchTree::~BinarySearchTree() {
    delete root;
    root = NULL;
}

// insert finds a position for x in the tree and places it there.
void BinarySearchTree::insert(const string& x) {
    if (root == NULL) { // Two extraneous cases: if the node already exists, and if the root doesn't exist.
        BinaryNode * temp = new BinaryNode();
        temp->value = x;
        root = temp; // Points to same pointee as temp.
        return;
    } else if (find(x)) {
        return;
    }

    insert(x, root);
}

void BinarySearchTree::insert(const string& x, BinaryNode*& tree) {
    // if (tree == NULL) {
    // 
    // }

    if (x > tree->value) { // If the string is greater than the current node's value (in the beginning, the root).
        if (tree->right == NULL) {
            BinaryNode * temp = new BinaryNode();
            temp->value = x;

            tree->right = temp;
        } else {
            insert(x, tree->right);
        }
    } else if (x < tree->value) {
        if (tree->left == NULL) {
            BinaryNode * temp = new BinaryNode();
            temp->value = x;

            tree->left = temp;
        } else {
            insert(x, tree->left);            
        }
    } else { // Duplicate
        return;
    }
}

// remove finds x's position in the tree and removes it.
void BinarySearchTree::remove(const string& x) {
    root = remove(root, x);
}

// private helper for remove to allow recursion over different nodes. returns
// a BinaryNode* that is assigned to the original node.
BinaryNode* BinarySearchTree::remove(BinaryNode*& n, const string& x) {
    if (n == NULL) {
        return NULL;
    }

    // first look for x
    if (x == n->value) {
        // found
        if (n->left == NULL && n->right == NULL) {
            // no children
            // just delete it :)
            delete n;
            n = NULL;
            return NULL;
        } else if (n->left == NULL) {
            // single child (right)
            // remove current node and return right child node for parent
            BinaryNode* temp = n->right;
            n->right = NULL;
            delete n;
            n = NULL;
            return temp;
        } else if (n->right == NULL) {
            // single child (left)
            // remove current node and return left child node for parent
            BinaryNode* temp = n->left;
            n->left = NULL;
            delete n;
            n = NULL;
            return temp;
        } else {
            // two children
            // replace current node with right child node's minimum, then remove that node
            string value = min(n->right);
            n->value = value;
            n->right = remove(n->right, value);
        }
    } else if (x < n->value) {
        n->left = remove(n->left, x);
    } else {
        n->right = remove(n->right, x);
    }
    return n;
}

// pathTo finds x in the tree and returns a string representing the path it
// took to get there.
string BinarySearchTree::pathTo(const string& x) const {
    if (!(find(x))) { // If the string is not in the tree.
        return "";
    }

    return pathTo(x, root, "");
}

string BinarySearchTree::pathTo(const string& x, BinaryNode* tree, string temp) const { // This stupid temp parameter allows me to have a constant string.
    if (x == tree->value) {
        return temp + tree->value;
    } else if (x > tree->value) { // Goes to right.
        temp = temp + tree->value + " ";
        return pathTo(x, tree->right, temp);
    } else if (x < tree->value) {
        temp = temp + tree->value + " ";
        return pathTo(x, tree->left, temp);
    }

    // if (find(x)) {
        // { // Changing it as it gets deeper in the recursion process..
    
        // }
    // }

    // return temp;
    return "";
}

// find determines whether or not x exists in the tree.
bool BinarySearchTree::find(const string& x) const {
    return find(x, root);
}

bool BinarySearchTree::find(const string& x, BinaryNode* tree) const {
    if (tree==NULL) {
        return false;
    }

    if (x == tree->value) {
        return true;
    }

    if (x > tree->value) {
        return find(x, tree->right);
    } else if (x < tree->value) {
        return find(x, tree->left);
    }

    return false; // If NULL or not found.
}

// numNodes returns the total number of nodes in the tree.
int BinarySearchTree::numNodes() const {
    return numNodes(root);
}

int BinarySearchTree::numNodes(BinaryNode* tree) const {
    if (tree == NULL) { // If the root doesn't exist.
        return 0;
    }

    if ((tree->left == NULL) && (tree->right == NULL)) {
        return 1;
    }

    if (!(tree->left == NULL) && (tree->right == NULL)) {
        return 1 + numNodes(tree->left);
    }

    if ((tree->left == NULL) && (!(tree->right == NULL))) {
        return 1 + numNodes(tree->right);
    }

    if (!(tree->left == NULL) && !(tree->right == NULL)) {
        return 1 + numNodes(tree->left) + numNodes(tree->right);
    }

    return 0;
}

// min finds the string with the smallest value in a subtree.
string BinarySearchTree::min(BinaryNode* node) const {
    // go to bottom-left node
    if (node->left == NULL) {
        return node->value;
    }
    return min(node->left);
}

// Helper function to print branches of the binary tree
// You do not need to know how this function works.
void showTrunks(Trunk* p) {
    if (p == NULL) return;
    showTrunks(p->prev);
    cout << p->str;
}

void BinarySearchTree::printTree() {
    printTree(root, NULL, false);
}

// Recursive function to print binary tree
// It uses inorder traversal
void BinarySearchTree::printTree(BinaryNode* root, Trunk* prev, bool isRight) {
    if (root == NULL) return;

    string prev_str = "    ";
    Trunk* trunk = new Trunk(prev, prev_str);

    printTree(root->right, trunk, true);

    if (!prev)
        trunk->str = "---";
    else if (isRight) {
        trunk->str = ".---";
        prev_str = "   |";
    } else {
        trunk->str = "`---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout << root->value << endl;

    if (prev) prev->str = prev_str;
    trunk->str = "   |";

    printTree(root->left, trunk, false);

    delete trunk;
}