#include <iostream>
#include <climits>
#include <cfloat>
#include <limits>

using namespace std;

void sizeOfTest() {
	int a = 1;
	unsigned int b = 1;
	float c = 1.0;
	double d = 1.0; 
	char e = '1'; 
	bool f = 1; 

	int * g = NULL;
	char * h = NULL;
	double * i = NULL; 

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

int main() { // type format add --format hex int
	sizeOfTest();

	int a0 = 0;
	int a1 = 1;

	unsigned int b0 = 0;
	unsigned int b1 = 1;

	float c0 = 0.0;
	float c1 = 1.0;

	double d0 = 0.0;
	double d1 = 1.0;

	char e0 = '0';
	char e1 = '1';

	bool f0 = false;
	bool f1 = true;

	int * g = NULL;
	char * h = NULL;
	double * i = NULL;

	cout << "CHAR_MAX: " << CHAR_MAX << endl;
	cout << "INT_MAX: " << INT_MAX << endl;
	cout << "UINT_MAX: " << UINT_MAX << endl;
	cout << "DBL_MAX: " << DBL_MAX << endl;
	cout << "Float Max: " << numeric_limits<float>::max() << endl;
	cout << "Bool Max: " << numeric_limits<bool>::max() << endl;
	cout << "Int * Max: " << numeric_limits<int *>::max() << endl;
	// cout << "Char * Max: " << numeric_limits<char *>::max() << endl;
	// cout << "Double * Max: " << numeric_limits<double *>::max() << endl;

	return 0;
}