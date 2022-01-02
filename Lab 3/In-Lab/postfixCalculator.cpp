// postfixCalculator.cpp
// September 11th, 2021
// Asadbek Shamsiev, as9vd@virginia.edu

#include <iostream>
#include <stack>
#include <cstdlib>

#include "postfixCalculator.h"

using namespace std;

postfixCalculator::postfixCalculator() {
	calcStack = stack<int>();
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
	if (calcStack.size() == 0) {
		return true;
	}

	return false;
}