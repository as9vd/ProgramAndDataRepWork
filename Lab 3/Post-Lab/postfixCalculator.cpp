// postfixCalculator.cpp
// September 16th, 2021
// Asadbek Shamsiev, as9vd@virginia.edu

#include <iostream>
#include <cstdlib>

#include "postfixCalculator.h"
#include "stack.h"

using namespace std;

postfixCalculator::postfixCalculator() {
}

postfixCalculator::~postfixCalculator() {}

void postfixCalculator::add() {
	if (this->isEmpty()) {
		exit(-1);
	}

	int num1 = calcStack.top();
	calcStack.pop();

	int num2 = calcStack.top();
	calcStack.pop();

	calcStack.push(num1 + num2);
}

void postfixCalculator::subtract() {
	if (this->isEmpty()) {
		exit(-1);
	}

	int num1 = calcStack.top();
	calcStack.pop();

	int num2 = calcStack.top();
	calcStack.pop();

	calcStack.push(num2 - num1);
}

void postfixCalculator::multiply() {
	if (this->isEmpty()) {
		exit(-1);
	}

	int num1 = calcStack.top();
	calcStack.pop();

	int num2 = calcStack.top();
	calcStack.pop();

	calcStack.push(num1 * num2);
}

void postfixCalculator::divide() {
	if (this->isEmpty()) {
		exit(-1);
	}

	int num1 = calcStack.top();
	calcStack.pop();

	int num2 = calcStack.top();
	calcStack.pop();

	calcStack.push(num2 / num1);
	
}

void postfixCalculator::negate() {
	if (this->isEmpty()) {
		exit(-1);
	}

	int num1 = calcStack.top();
	calcStack.pop();

	calcStack.push(-1 * num1);
	
}

bool postfixCalculator::isEmpty() {
	if (calcStack.empty()) {
		return true;
	}

	return false;
}