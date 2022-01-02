// stacknode.cpp
// September 16th, 2021
// Asadbek Shamsiev, as9vd@virginia.edu

#include "stacknode.h"
#include <iostream>

using namespace std;

stacknode::stacknode() {
	value = 0;
	next = NULL;
	previous = NULL;
}