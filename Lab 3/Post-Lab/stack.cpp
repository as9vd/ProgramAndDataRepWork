// stack.cpp
// September 16th, 2021
// Asadbek Shamsiev, as9vd@virginia.edu

// https://www.youtube.com/watch?v=o5wJkJJpKtM; This video was very useful in the implementation of this class. It used LinkedList principles.

#include "stack.h"
#include "postfixCalculator.h"
#include <iostream>

using namespace std;

Stack::Stack() {
	head = new stacknode;
	tail = new stacknode;
	head->next = tail;
	tail->previous = head;
	count = 0;
}

Stack::~Stack() {
	while (!(count == 0)) { // Need to get rid of non-head/non-tail nodes too.
		pop();
	}

	delete head;
	delete tail;
}

void Stack::push(int e) {
	// ListItr temp = stackList.first();
	// stackList.insertBefore(e, temp);

	stacknode * tempNode = new stacknode;
	tempNode->value = e;
	tempNode->previous = tail->previous;
	tail->previous->next = tempNode; // Doesn't get rid of tail, but severs the tie between the previous node and the next.
	tempNode->next = tail;
	tail->previous = tempNode;

	count++;
}

void Stack::pop() {
	// ListItr temp = stackList.first();	
	// int tempNum = temp.retrieve();
	// stackList.remove(tempNum);

	stacknode * tempNode = new stacknode;	
	tempNode = tail->previous;
	tail->previous->previous->next = tail;
	tail->previous = tail->previous->previous;

	delete tempNode;

	count--;
}

int Stack::top() {
	if (!(empty())) {
		int top = tail->previous->value;
		return top;	
	}

	return 0; // If it doesn't exist.
}

bool Stack::empty() {
	if (count == 0) {
		return true;
	} else {
		return false;		
	}
}