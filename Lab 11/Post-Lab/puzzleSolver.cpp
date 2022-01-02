// puzzleSolver.cpp
// Asadbek Shamsiev, as9vd
// December 1st, 2021

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// 1. Take in input.
// 2. 

/* \author Asadbek Shamsiev 
*/

/* \fn int main()
*/ 
int main() {
	cout << "Enter puzzle" << endl;

	string holder;
	string temp;

	int count = 0;

	while (count < 9) {
		cin >> temp;

		if (temp == "0") {
			temp = " ";
		}

		holder = holder + temp;

		count++;
	}
	
	string goal = "12345678 ";

	int GUNNA[3][3] = {{holder.at(0), holder.at(1), holder.at(2)}, {holder.at(3), holder.at(4), holder.at(5)}, {holder.at(6), holder.at(7), holder.at(8)}}; // The input array.
	// int IDEAL[3][3] = 

	// --------------------------------------------------

	return 0;
}

int computeDifference(const string& input, const string& goal) {
	return 0;
}

// void swap(int & GUNNA[][], int startRow, int startColumn, int endRow, int endColumn) {
// 
// }