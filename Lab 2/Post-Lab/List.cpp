// List.cpp
// September 8th, 2021
// Asadbek Shamsiev, as9vd@virginia.edu

// Source: https://www.youtube.com/watch?v=o5wJkJJpKtM
// This video greatly helped me with the insert methods.

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
	makeEmpty();
	delete head;
	delete tail;
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
	if (count > 0) {
		return false;
	}

	return true;
}

void List::makeEmpty() { // Edit this.
	// ListNode * temp = new ListNode();
	ListItr listPosition = first();

	while (!(listPosition.isPastEnd())) {
		if (listPosition.current == tail || listPosition.current == head) {
			// delete temp;
			break;
		}

		// temp = listPosition.current;
		listPosition.moveForward();

		if (listPosition.current->previous == head) {
			listPosition.moveForward();
		} 

		delete listPosition.current->previous;

		// delete temp;
	}

	head->next = tail; // Only the dummy nodes remain.
	tail->previous = head;

	count = 0;
} 

ListItr List::first() { 
	ListItr temp(head->next); 

	if (temp.isPastEnd()) { 
		temp.moveBackward();

		return temp;
	}

	return temp; 
}

ListItr List::last() {
	ListItr temp(tail->previous); // opposite of first();

	if (temp.isPastBeginning()) {
		temp.moveForward();
		return temp;
	}

	return temp;
}

void List::insertAfter(int x, ListItr position) {
	ListNode * newNode = new ListNode;

	newNode->value = x;

	position.current->next->previous = newNode;
	newNode->next = position.current->next;
	position.current->next = newNode;
	newNode->previous = position.current;

	count++;
} 

void List::insertBefore(int x, ListItr position) {
	ListNode * newNode = new ListNode; // opposite of insertBefore()

	newNode->value = x;

	position.current->previous->next = newNode;
	newNode->previous = position.current->previous;
	position.current->previous = newNode;
	newNode->next = position.current;

	count++;
}

void List::insertAtTail(int x) {
	ListNode * newNode = new ListNode;

	newNode->value = x;

 	newNode->next = tail;
	newNode->previous = tail->previous;
	
	tail->previous->next = newNode;
	tail->previous = newNode; 

	count++;
}

ListItr List::find(int x) {
	// ListItr * temp = new ListItr(this->first()); Leakey

	ListItr temp(first());

	while (!(temp.isPastEnd())) {
		if (temp.retrieve() == x) {
			return temp;
		} else {
			temp.moveForward();
		}
	}

	return temp; // If the node doesn't exist. Returning null doesn't work if a number is requested outside range.

}

void List::remove(int x) {
	// ListItr * temp = new ListItr(find(x)); Leakey

	ListItr temp = (find(x));

	if (!(temp.isPastEnd())) { // Make sure to change properties of node to the left and to the right of the thing.
		count--;

		temp.current->next->previous = temp.current->previous; 
		temp.current->previous->next = temp.current->next;
	}

	delete temp.current;
}

int List::size() const {
	return count;
}


void printList(List& source, bool forward) { // Make it so it prints nothing if the list is empty.
	if (forward) {
		ListItr * itr = new ListItr(source.first());

		while (!(itr->isPastEnd())) {
			if (source.size() == 0) {
				cout << "\n";
				break;
			}

			cout << itr->retrieve() << " ";

			itr->moveForward();

			if (itr->isPastEnd()) {
				cout << "\n";
			}
		}

		delete itr;
	} else {
		ListItr * itr = new ListItr(source.last());

		while (!(itr->isPastBeginning())) {
			if (source.size() == 0) {
				cout << "\n";
				break;
			}

			cout << itr->retrieve() << " ";

			itr->moveBackward();

			if (itr->isPastBeginning()) {
				cout << "\n";
			}
		}

		delete itr;
	}


}