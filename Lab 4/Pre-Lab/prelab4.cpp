#include <iostream>
#include <string>
using namespace std;

void sizeOfTest() {
	int a = 1;
	unsigned int b = 1;
	float c = 1;
	double d = 1; 
	char e = 1; 
	bool f = 1; 

	int * g = new int(1); 
	char * h = new char(1); 
	double * i = new double(1); 

	cout << "Size of int: " << sizeof(a) << endl;
	cout << "Size of unsigned int: " << sizeof(b) << endl;
	cout << "Size of float: " << sizeof(c) << endl;
	cout << "Size of double: " << sizeof(d) << endl;
	cout << "Size of char: " << sizeof(e) << endl;
	cout << "Size of bool: " << sizeof(f) << endl;

	cout << "Size of int*: " << sizeof(g) << endl;
	cout << "Size of char*: " << sizeof(h) << endl;
	cout << "Size of double*: " << sizeof(i) << endl;

	delete g;
	delete h;
	delete i;
}

void overflow() {
	unsigned int a = 4294967295;

	cout << a << " + 1 = " << a + 1 << endl;
}	

void outputBinary(unsigned int x) { // The method here is to keep dividing the number by the base (2 in this case) and stashing the remainder as a bit in binary. Then, you switch the order in which you stashed and read the program that way.
	if (x == 0) {
		cout << "0000 0000 0000 0000 0000 0000 0000 0000";
		return;
	}

	int binaryArray[32];

	// This graphic helped me understand the conversion process:
	// https://images.saymedia-content.com/.image/t_share/MTc0NjQ3MTg4MjM5MDk5MjU4/how-to-convert-decimal-to-binary-and-binary-to-decimal.jpg
	for (int i = 31; i >= 0; i--) { 
		int remainder = x % 2;
		x = x / 2;
		binaryArray[i] = remainder;
	}

	for (int i = 0; i < 32; i++) {
		if ((i % 4) == 0 && !(i == 0)) {
			cout << " ";
		}

		cout << binaryArray[i];
	}

	cout << endl;
}

int main() {
	int x; 
	cin >> x;

	sizeOfTest();
	overflow();
	outputBinary(x);

	cout << endl;

	return 0;
}