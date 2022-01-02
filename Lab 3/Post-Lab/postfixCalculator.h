// postfixCalculator.h
// September 16th, 2021
// Asadbek Shamsiev, as9vd@virginia.edu

#ifndef POSTFIXCALCULATOR_H
#define POSTFIXCALCULATOR_H

#include <iostream>
#include "stack.h"

using namespace std;

class postfixCalculator {
public:
	postfixCalculator();
	~postfixCalculator();
	void add();
	void subtract();
	void multiply();
	void divide();
	void negate();
	bool isEmpty();

	Stack calcStack;
};

#endif