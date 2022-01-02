// xToN.cpp
// August 28th, 2021
// Asadbek Shamsiev, as9vd@virginia.edu

#include <iostream>
using namespace std;

int xton(int num1, int num2) {
	if (num2 == 0) {
		return 1;
	} else {
		return (num1 * xton(num1, num2 - 1));
	}
}

int main() {
	int x, y, z;
	cin >> x;
	cin >> y;
	z = xton(x, y);
	cout << z << endl;
	return 0;
}