// stacknode.h
// September 16th, 2021
// Asadbek Shamsiev, as9vd@virginia.edu

#ifndef STACKNODE_H
#define STACKNODE_H

#include <iostream>

using namespace std;

class stacknode {
public:
    stacknode();

private:
    int value;
    stacknode* next;
    stacknode* previous;

    friend class Stack;
    friend class postfixCalculator;
};

#endif