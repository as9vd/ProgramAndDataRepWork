// List.cpp
// September 4th, 2021
// Asadbek Shamsiev, as9vd@virginia.edu

#include <iostream>
#include "List.h"
#include <string>

using namespace std;

List::List() {
	head=new ListNode();
    tail=new ListNode();

    head->next=tail;
    tail->previous=head;
    head->previous = NULL;
	tail->next = NULL;

    count=0;
}

List::List(const List& source) {
    head=new ListNode();
    tail=new ListNode();
    head->next=tail;
    tail->previous=head;
    count=0;

    // Make a deep copy of the list
    ListItr iter(source.head->next);
    while (!iter.isPastEnd()) {
        insertAtTail(iter.retrieve());
        iter.moveForward();
    }
}

List::~List() {
	head = NULL;
	tail = NULL;
}

// Copy assignment operator
// Called when the code looks something like list2 = list1;
// (In other words, it is called when you are trying to set an **existing** list equal to another one)
List& List::operator=(const List& source) {
    if (this == &source) {
        // The two are the same list; no need to do anything
        return *this;
    } else {
        // Clear out anything this list contained
        // before copying over the items from the other list
        makeEmpty();

        // Make a deep copy of the list
        ListItr iter(source.head->next);
        while (!iter.isPastEnd()) {
            insertAtTail(iter.retrieve());
            iter.moveForward();
        }
    }
    return *this;
}

bool List::isEmpty() const {
	return false;
}

void List::makeEmpty() {}

ListItr List::first() { // temp does not return the correct integer value.
	ListItr * temp = new ListItr(head->next); 

	// int tempInt = temp->retrieve(); 

	if (temp->isPastEnd()) { // Checking for an empty list. 
		temp->moveBackward();
		return * temp;
	}

	return * temp; // Return the node after the empty head node.
}

ListItr List::last() {
	return NULL;
}

void List::insertAfter(int x, ListItr position) {}

void List::insertBefore(int x, ListItr position) {}

// Things are mistakenly being put as next instead of previous.. that's why it's backwards.
// prev value never changes. Next always does though.
// e.g. inputting 30, 40, 50, 60 always has nextValue as 10 less than what you typed in; tailValue does change however.
	// e.g. "30, 40, 50, 60" --> 60, 50, 40, 30.
// PROBLEM: Inputs are going at the head area instead of the tail.

// int prevValue = tail->previous->value;
// int nextValue = tail->next->value;
// int tailValue = tail->value;
void List::insertAtTail(int x) {
	ListNode * newNode = new ListNode;
	// ListNode * tempTail = new ListNode;

	newNode->value = x; // Initialising the value.

 	// Assume the properties of the tail's previous position.
 	newNode->next = tail;
	newNode->previous = tail->previous;

	// newNode->next = tail; // Making it squeeze between previous point and the (dummy) end.
	
	tail->previous->next = newNode; // Changes what the previous tail node (e.g. the last real node) is pointing to. 
	tail->previous = newNode; // Getting rid of the tail's previous position and updating it to the (new) end.

	count++;
}

ListItr List::find(int x) {return NULL;}

void List::remove(int x) {}

int List::size() const {
	return count;
}

void printList(List& source, bool forward) { // Is messed up.
	ListItr * itr = new ListItr(source.first());

	while (!(itr->isPastEnd())) {
		// str.append(" " + to_string(itr->retrieve()));
		cout << itr->retrieve() << " ";

		itr->moveForward();

		if (itr->isPastEnd()) {
			cout << "\n";
		}
	}

	// cout << str;
}