// Asadbek Shamsiev
// October 31st, 2021
// as9vd

#include <iostream>
#include <cstdlib>

using namespace std;

extern "C" int product(int, int);
extern "C" int power(int, int);

int main() {
	int num1, num2;

	cout << "Enter integer 1: ";
	cin >> num1;

	cout << "Enter integer 2: ";
	cin >> num2;

	int prod = product(num1, num2);
	int pow = power(num1, num2);

	// cout << "Product: " + std::(product(num1, num2)) << endl;
	// cout << "Power: " + std::to_string(power(num1, num2)) << endl;

	cout << "Product: " << prod << endl;
	cout << "Power: " << pow << endl;

	return 0;
}