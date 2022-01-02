// stack.h
// September 16th, 2021
// Asadbek Shamsiev, as9vd@virginia.edu

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "stacknode.h"

using namespace std;

class Stack { // Must be upercase, otherwise is "reference to 'stack' is ambiguous".
public:
    Stack();
    ~Stack();
    void push(int e);
    void pop();
    int top();
    bool empty();

private:
	friend class stacknode;
	friend class postfixCalculator;
    
    int count;
    stacknode * head;
    stacknode * tail;
};

#endif