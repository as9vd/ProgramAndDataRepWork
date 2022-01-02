// AVLTree.cpp
// October 5th, 20201
// Asadbek Shamsiev, as9vd

#include "AVLNode.h"
#include "AVLTree.h"
#include <iostream>
#include <string>
using namespace std;

AVLTree::AVLTree() {
    root = NULL;
}

AVLTree::~AVLTree() {
    delete root;
    root = NULL;
}

// insert finds a position for x in the tree and places it there, rebalancing
// as necessary.
void AVLTree::insert(const string& x) { // ADD BALANCE CHECK
    if (root == NULL) { // Two extraneous cases: if the node already exists, and if the root doesn't exist.
        AVLNode * temp = new AVLNode();
        temp->value = x;
        root = temp; // Points to same pointee as temp.
        return;
    } else if (find(x)) {
        return;
    }

    insert(x, root);
}

void AVLTree::insert(const string&x, AVLNode*& n) {
    if (x > n->value) { // If the string is greater than the current node's value (in the beginning, the root).
        if (n->right == NULL) { // If there is no right node on this node, you insert it.
            AVLNode * temp = new AVLNode();
            temp->value = x;

            n->right = temp;
        } else {
            insert(x, n->right); // Otherwise, you keep recursing down.
        }
    // } else if (x < n->value) {
    } else {
        if (n->left == NULL) {
            AVLNode * temp = new AVLNode();
            temp->value = x;

            n->left = temp;
        } else {
            insert(x, n->left);            
        }
    }

    n->height = 1 + max(height(n->left), height(n->right)); // Copied from the remove method down below.
    balance(n); // Recurses back up as goes down.
}

// remove finds x's position in the tree and removes it, rebalancing as
// necessary.
void AVLTree::remove(const string& x) {
    root = remove(root, x);
}

// pathTo finds x in the tree and returns a string representing the path it
// took to get there.
string AVLTree::pathTo(const string& x) const {
    if (!(find(x))) { // If the string is not in the tree.
        return "";
    } else {
        return pathTo(x, root, "");    
    }   
}

string AVLTree::pathTo(const string& x, AVLNode* n, string temp) const {
    if (x == n->value) {
        return temp + n->value;
    } else if (x > n->value) { // Goes to right.
        temp = temp + n->value + " ";
        return pathTo(x, n->right, temp);
    } else if (x < n->value) {
        temp = temp + n->value + " ";
        return pathTo(x, n->left, temp);
    }

    return "";
}

// find determines whether or not x exists in the tree.
bool AVLTree::find(const string& x) const {
    return find(x, root);
}

bool AVLTree::find(const string& x, AVLNode* n) const {
    if (n == NULL) {
        return false;
    }

    if (x == n->value) {
        return true;
    }

    if (x > n->value) {
        return find(x, n->right);
    } else if (x < n->value) {
        return find(x, n->left);
    }

    return false; // If NULL or not found.
}

// numNodes returns the total number of nodes in the tree.
int AVLTree::numNodes() const {
    return numNodes(root);
}

int AVLTree::numNodes(AVLNode* n) const {
    if (n == NULL) { // If the root doesn't exist.
        return 0;
    }

    if ((n->left == NULL) && (n->right == NULL)) {
        return 1;
    }

    if (!(n->left == NULL) && (n->right == NULL)) {
        return 1 + numNodes(n->left);
    }

    if ((n->left == NULL) && (!(n->right == NULL))) {
        return 1 + numNodes(n->right);
    }

    if (!(n->left == NULL) && !(n->right == NULL)) {
        return 1 + numNodes(n->left) + numNodes(n->right);
    }

    return 1;
}

// balance makes sure that the subtree with root n maintains the AVL tree
// property, namely that the balance factor of n is either -1, 0, or 1.
void AVLTree::balance(AVLNode*& n) { // https://www.softwaretestinghelp.com/avl-trees-and-heap-data-structure-in-cpp/
    // Double rotation: Left-right, right-left.
    // Single rotation: Left-left, right-right.

    // YOUR IMPLEMENTATION GOES HERE

    if (balanceFactor(n) == 2) { // if balance factor of node is 2 we will need to rotate left:
        if (balanceFactor(n->right) < 0) { // first, see if we should also rotate right (i.e., do a double rotation)
            // if balance factor of right child is negative:
            AVLNode * temp = rotateRight(n->right); // rotate right on the right child
            // rotateRight(n->right);
            n->right = temp;
        }

        n = rotateLeft(n); // rotate left on node
    } else if (balanceFactor(n) == -2) {
        if (balanceFactor(n->left) > 0) { // Check if we need to rotateRight as well.
            AVLNode * temp = rotateLeft(n->left);
            // rotateLeft(n->left);
            n->left = temp;
        }

        n = rotateRight(n);
    }
}

// rotateLeft performs a single rotation on node n with its right child.
AVLNode* AVLTree::rotateLeft(AVLNode*& n) {
    // YOUR IMPLEMENTATION GOES HERE
    AVLNode * rightNode = n->right;
    AVLNode * child = rightNode->left;

    rightNode->left = n;
    n->right = child;

    n->height = max(height(n->left), height(n->right)) + 1;
    rightNode->height = max(height(rightNode->left), height(rightNode->right)) + 1;

    return rightNode;
}

// rotateRight performs a single rotation on node n with its left child.
AVLNode* AVLTree::rotateRight(AVLNode*& n) {
    // YOUR IMPLEMENTATION GOES HERE
    AVLNode * leftNode = n->left;
    AVLNode * child = leftNode->right;

    leftNode->right = n;
    n->left = child;

    n->height = max(height(n->left), height(n->right)) + 1;
    leftNode->height = max(height(leftNode->left), height(leftNode->right)) + 1;

    return leftNode;
}

int AVLTree::balanceFactor(AVLNode* n) const { 
    if (n == NULL) {
        return 0;
    }

    return height(n->right) - height(n->left);
}

// private helper for remove to allow recursion over different nodes.
// Returns an AVLNode* that is assigned to the original node.
AVLNode* AVLTree::remove(AVLNode*& n, const string& x) {
    if (n == NULL) {
        return NULL;
    }

    // first look for x
    if (x == n->value) {
        // found
        if (n->left == NULL && n->right == NULL) {
            // no children
            delete n;
            n = NULL;
            return NULL;
        } else if (n->left == NULL) {
            // Single child (left)
            AVLNode* temp = n->right;
            n->right = NULL;
            delete n;
            n = NULL;
            return temp;
        } else if (n->right == NULL) {
            // Single child (right)
            AVLNode* temp = n->left;
            n->left = NULL;
            delete n;
            n = NULL;
            return temp;
        } else {
            // two children -- tree may become unbalanced after deleting n
            string sr = min(n->right);
            n->value = sr;
            n->right = remove(n->right, sr);
        }
    } else if (x < n->value) {
        n->left = remove(n->left, x);
    } else {
        n->right = remove(n->right, x);
    }

    // Recalculate heights and balance this subtree
    n->height = 1 + max(height(n->left), height(n->right));
    balance(n);

    return n;
}

// min finds the string with the smallest value in a subtree.
string AVLTree::min(AVLNode* node) const {
    // go to bottom-left node
    if (node->left == NULL) {
        return node->value;
    }
    return min(node->left);
}

// height returns the value of the height field in a node.
// If the node is null, it returns -1.
int AVLTree::height(AVLNode* node) const {
    if (node == NULL) {
        return -1;
    }
    return node->height;
}

// max returns the greater of two integers.
int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

// Helper function to print branches of the binary tree
// You do not need to know how this function works.
void showTrunks(Trunk* p) {
    if (p == NULL) return;
    showTrunks(p->prev);
    cout << p->str;
}

// Recursive function to print binary tree
// It uses inorder traversal
void AVLTree::printTree(AVLNode* root, Trunk* prev, bool isRight) {
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

void AVLTree::printTree() {
    printTree(root, NULL, false);
}