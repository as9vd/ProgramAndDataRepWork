// testPostfixCalc.cpp
// September 11th, 2021
// Asadbek Shamsiev, as9vd@virginia.edu

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
// #include "postfixCalculator.cpp"
#include "postfixCalculator.h"

using namespace std;

int main() {
	postfixCalculator calc;

	while (true) {
		string token;
		cin >> token;

		if (token == "") {
			break;
		}

		if (token == "+") {
			calc.add();
		} else if (token == "-") {
			calc.subtract();
		} else if (token == "*") {
			calc.multiply();
		} else if (token == "/") {
			calc.divide();
		} else if (token == "~") {
			calc.negate();
		} else { // If it's a number.
			int num = stoi(token); // https://careerkarma.com/blog/c-plus-plus-string-to-int/; this is where I got the stoi() function from.
			calc.calcStack.push(num);
		}
	}

	cout << calc.calcStack.top() << endl;

	return 0;
}