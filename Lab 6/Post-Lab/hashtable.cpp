// hashtable.cpp
// October 18th, 2021
// Asadbek Shamsiev, as9vd@virginia.edu

#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "hashtable.h"

using namespace std;

hashtable::hashtable(unsigned int size) {
	// v = vector<list<string>>(250000); // 500^2.
	v.resize(size);
}

hashtable::~hashtable() {}

// Insert a string at the list in the appropriate index; 
void hashtable::insert(string x) { 
	int hash = hashCode(x); // The hash indicates where the element should go, e.g. which bucket.

	v[hash].push_back(x);
}

bool hashtable::find(string x) {
	int hash = hashCode(x);

	for (string element : v[hash]) { // For each element in the appropriate bucket.
		if (element == x) {
			return true;
		}
	}

	return false;
}

// https://www.baeldung.com/java-hashcode: A useful resource re: hashcode functions. A good throwback to the days of Java too.
unsigned int hashtable::hashCode(string x) {
	unsigned int temp = 0;

	for (unsigned int i = 0; i < x.length(); i++) {
		temp = (temp * 37) + x[i];
	}

	return (temp) % v.size();
}