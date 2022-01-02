// ListItr.cpp
// September 8th, 2021
// Asadbek Shamsiev, as9vd@virginia.edu

#include "ListItr.h"

using namespace std;

ListItr::ListItr() {
	current = NULL;
}

ListItr::ListItr(ListNode* theNode) {
	current = theNode;
}

bool ListItr::isPastEnd() const {
	if (current->next == NULL) { // If there is not a node past the current one, e.g. if it is the tail.
		return true;
	}

	return false;
}

bool ListItr::isPastBeginning() const {
	if (current->previous == NULL) { // If there is not a node behind the current one, e.g. if it is the head.
		return true;
	}

	return false;
}

void ListItr::moveForward() {
	if (!(isPastEnd())) { // If it isn't pointing at the tail, then move forward.
		current = current->next;
	}
}

void ListItr::moveBackward() { // If it isn't pointing at the head, then move backward.
	if (!(isPastBeginning())) {
		current = current->previous;
	}
}

int ListItr::retrieve() const {
	return current->value;
}