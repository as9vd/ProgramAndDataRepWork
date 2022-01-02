// TreeCalc.cpp
// October 2nd, 20201
// Asadbek Shamsiev, as9vd
// TreeCalc.cpp:  CS 2150 Tree Calculator method implementations

#include "TreeCalc.h"
#include <iostream>

using namespace std;

// Constructor
TreeCalc::TreeCalc() {
    stack<TreeNode*> expressionStack; // FIX THE SEGFAULT WHEN THERE'S 0 INPUTS
}

// Destructor - frees memory
TreeCalc::~TreeCalc() {
    // if (!(expressionStack.empty())) {
    cleanTree(expressionStack.top());
    // }
    // cleanTree(expressionStack.top());
}

// Deletes tree/frees memory
void TreeCalc::cleanTree(TreeNode* tree) {
    if (tree == NULL) {
        delete tree;
    } else {
        cleanTree(tree->left);
        cleanTree(tree->right);
        delete tree;
    }

    // if (!(tree->left == NULL)) {
        // cleanTree(tree->left);
    // } else if (!(tree->right == NULL)) {
        // cleanTree(tree->right);
    // }

    // delete tree;
}

// Gets data from user
// DO NOT MODIFY
void TreeCalc::readInput() {
    string response;
    cout << "Enter elements one by one in postfix notation" << endl
         << "Any non-numeric or non-operator character,"
         << " e.g. #, will terminate input" << endl;
    cout << "Enter first element: ";
    cin >> response;
    //while input is legal
    while (isdigit(response[0]) || response[0] == '/' || response[0] == '*'
            || response[0] == '-' || response[0] == '+') {
        insert(response);
        cout << "Enter next element: ";
        cin >> response;
    }
}

// Puts value in tree stack

void TreeCalc::insert(const string& val) {
    if (!(val == "*" || val == "+" || val == "/" || val == "-")) { // If it's a number.
        TreeNode * temp = new TreeNode(val);
        expressionStack.push(temp); 
    } else { // Make an expression with the node..
        TreeNode* operand = new TreeNode(val);

        TreeNode* temp1 = expressionStack.top();
        expressionStack.pop();

        TreeNode* temp2 = expressionStack.top();
        expressionStack.pop();

        operand->left = temp2;
        operand->right = temp1;
        // if (!(temp1->value == "*" || temp1->value == "+" || temp1->value == "/" || temp1->value == "-") &&
            // !(temp2->value == "*" || temp2->value == "+" || temp2->value == "/" || temp2->value == "-")) {
            // if (temp1->value > temp2->value) {

            // } else {
                // temp->left = temp1;
                // temp->right = temp2;
            // }
        // }

        // if ((temp1->value == "*" || temp1->value == "+" || temp1->value == "/" || temp1->value == "-") &&
        //     (temp2->value == "*" || temp2->value == "+" || temp2->value == "/" || temp2->value == "-")) {
        //     temp->left = temp2; // Just keep the default ordering if it's an arithmetic command.
        //     temp->right = temp1;
        // }
        expressionStack.push(operand);
    }
}

// Prints data in prefix form
void TreeCalc::printPrefix(TreeNode* tree) const {
    if (!(tree == NULL)) { // Print as you traverse.
        cout << tree->value + " ";

        printPrefix(tree->left);
        printPrefix(tree->right);
    }
}

// Prints data in infix form
void TreeCalc::printInfix(TreeNode* tree) const {
    bool operation = false;

    if (!(tree == NULL)) {
        if (tree->value == "*" || tree->value == "+" || tree->value == "/" || tree->value == "-") {
            operation = true;
        }

        if (operation) {
            cout << "(";
        }

        printInfix(tree->left);

        if (operation) {
            cout << " ";
        }

        cout << tree->value;

        // if (operation) {
        // }

        if (operation) {
            cout << " ";
        }

        printInfix(tree->right);

        if (operation) {
            cout << ")";
        }
    }
}

//Prints data in postfix form
void TreeCalc::printPostfix(TreeNode* tree) const { // https://www.youtube.com/watch?v=gm8DUJJhmY4: Very helpful resource for PostFix.
    if (!(tree == NULL)) {
        printPostfix(tree->left);
        printPostfix(tree->right);

        cout << tree->value + " ";
    }
}

// Prints tree in all 3 (post, in, pre) forms
// DO NOT MODIFY
void TreeCalc::printOutput() const {
    if (expressionStack.size() != 0 && expressionStack.top() != NULL) {
        TreeNode* tree = expressionStack.top();
        cout << "Expression tree in postfix expression: ";
        printPostfix(tree);
        cout << endl;

        cout << "Expression tree in infix expression: ";
        printInfix(tree);
        cout << endl;

        cout << "Expression tree in prefix expression: ";
        printPrefix(tree);
        cout << endl;
    } else {
        cout << "Size is 0." << endl;
    }
}

// Evaluates tree, returns value
// private calculate() method
// int TreeCalc::calculate(TreeNode* tree) const {
//     if (tree->value == "*") {
//         int value = calculate(tree->left) * calculate(tree->right);
//         return value;
//     } else if (tree->value == "+") {
//         int value = calculate(tree->left) + calculate(tree->right);
//         return value; 
//     } else if (tree->value == "/") {
//         int value = calculate(tree->left) / calculate(tree->right);
//         return value;
//     } else if (tree->value == "-") {
//         int value = calculate(tree->left) - calculate(tree->right);
//         return value;
//     } else {
//         int value = stoi(tree->value);
//         return value;
//     }
// }

int TreeCalc::calculate(TreeNode * tree) const {
    if (tree == NULL) {
        return 0;
    }

    if ((tree->left == NULL) && (tree->right == NULL)) {
        return stoi(tree->value);
    } else {
        int left = calculate(tree->left);
        int right = calculate(tree->right);

        if (tree->value == "+") {
            return left + right;
        } else if (tree->value == "*") {
            return left * right;
        } else if (tree->value == "/") {
            return left / right;
        // } else if (tree->value == "-") {
        } else {
            return left - right;
        }
        // }
    }    
}

//Calls calculate, sets the stack back to a blank stack
// public calculate() method. Hides private data from user
int TreeCalc::calculate() {
    int calculation = calculate(expressionStack.top());
    // if (!(expressionStack.empty())) {
    // expressionStack.pop(); // Only one node remaining on the stack (the big tree).    
    // }
    // expressionStack.pop();
        // expressionStack.pop();
    // }

    return calculation;
}