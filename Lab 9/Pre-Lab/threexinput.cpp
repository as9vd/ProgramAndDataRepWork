// Asadbek Shamsiev
// November 13th, 2021
// as9vd

#include <iostream>
#include "timer.h"
using namespace std;

extern "C" int threexplusone(int input);

int testFunc(int input, int callNum, int tracker);

int main() {
	int in;
	int cNum;
	int steps;

	cout << "Enter a number: ";
    cin >> in;

    cout << "Enter iterations of subroutine: ";
    cin >> cNum;

    steps = threexplusone(in);

    for (int x = 0; x < cNum; x++) {
    	threexplusone(in);
    }

    cout << "Steps: " << steps << endl;

	return 0;
}

int testFunc(int input, int callNum, int tracker) { // This is how it should be programmed in x86, minus the latter two parameters.
	if (input == 1) {
		return tracker;
	}

	if (input % 2 == 0) {
		tracker++;
		return testFunc(input / 2, callNum, tracker);
	} else if (!(input % 2 == 0)) {
		tracker++;
		return testFunc((3 * input) + 1, callNum, tracker);
	}

	return 0;
}