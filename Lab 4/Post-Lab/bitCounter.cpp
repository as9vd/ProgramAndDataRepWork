// bitCounter.cpp
// September 21st, 2021
// Asadbek Shamsiev, as9vd@virginia.edu

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

string stringReverser(string input);

// 1. Take in a string of something (e.g. numbers and letters).
// 2. Iterating through the string (starting at the end).
string baseConverter(string input, int startBase, int endBase) {
	int length = input.length();
	string answer = "";

	int base = 0;
	int decimal = 0;

	for (int i = length - 1; i >= 0; i--) { // This converts it to decimal.
		int temp = (int) input[i]; // https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c: this helped with the conversion of char to int.

		if (temp > 57) { // '9' = 57 in ascii; anything higher than 57 is a letter.
		 	// https://www.cisco.com/c/en/us/td/docs/ios/12_4/cfg_fund/command/reference/cfnapph.html: 55 is the magic number.
			// The ASCII codes for A, B, C, etc. are 65, 66, 67, etc. respectively. This will convert the char into the appropriate int.
			temp = temp - 55;
		} else { 
			temp = temp - '0'; // Turns it into a normal int.
		}

		// Multiply each number in its respective digit spot by the power of the base. E.g. converting 101 to decimal, 1 * 2^0, 0 * 2^1, 1 * 2^2.
		decimal = decimal + (temp * pow(startBase, base)); 
		base++; // The base increases with every iteration (e.g. 2^0, 2^1, etc.).
	}

	// https://barronwasteland.files.wordpress.com/2015/01/example.png: this is how you use the remainder to create the appropriate base representation.
	while (!(decimal == 0)) {
		int remainder = decimal % endBase; // Divide the base 10 by the desired base; the remainder will go into the representation.
		decimal = decimal / endBase; // Automatically floors for you.
		char c = '0' + remainder; // https://stackoverflow.com/questions/4629050/convert-an-int-to-ascii-character: helped with conversion of int to char.
		answer = answer + c; // Add this character to the earlier string.
	}

	string forwardDec = stringReverser(answer);

	return forwardDec;
}

string stringReverser(string input) {
	int x = input.length() - 1;

	for (int i = 0; i < (input.length())/2; i++) {
		swap(input[i], input[x]);
		x--;
	}

	return input;
}

int bitCounter(int x) {
	if (x == 0) { // Base case; if is at rock bottom (implicitly floors results).
		return 0;
	}

	if (x % 2 == 0) {
		return bitCounter(x / 2); // Dividing by the base (2).
	} else if (!(x % 2 == 0)) {
		return 1 + bitCounter(x / 2);
	}

	return 0;
}

int main(int argc, char **argv) {
	if (argv[1] == NULL || argv[2] == NULL || argv[3] == NULL || argv[4] == NULL) {
		cout << "No input given. Program will terminate now." << endl;
		exit(-1);
		// return 0;
	}
	
	string input = argv[2];
	int argv3 = atoi(argv[3]); // Otherwise error about char * and int.
	int argv4 = atoi(argv[4]);

	int x = stoi(argv[1]);
	string xString = to_string(bitCounter(x));
	cout << x << " has " << xString << " bit(s)" << endl;
	// cout << baseConverter(input, argv3, argv4) << endl;

	cout << input << " (base " << argv3 << ") = " << baseConverter(input, argv3, argv4) << " (base " << argv[4] << ")" << endl;

	return 0;
}

// int baseTenConversion(string x, int startBase) {
// 	int length = x.size();
// 	int temp = 1;

// 	// First step: convert to base 10 (always).
// 	for (int i = 0; i <= length ; i++) { // 16 - 9 = 7 for hexadecimal; '_ - 0' converts a character to an int.
// 		char numBit = x[i];

// 		if (numBit > '9') {
// 			numBit = numBit - 'A' + 10; // Turns into int, and then readds the 10 for a net zero change.
// 		} else {
// 		}
// 	}
// 
//
// 	return answer;
// }

//