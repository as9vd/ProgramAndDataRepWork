// wordPuzzle.cpp
// October 18th, 2021
// Asadbek Shamsiev, as9vd@virginia.edu

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "hashtable.h"
#include "timer.h"

#define MAXROWS 500
#define MAXCOLS 500
char grid[MAXROWS][MAXCOLS];

bool readInGrid(string filename, int& rows, int& cols);
string getWordInGrid(int startRow, int startCol, int dir, int len,
                     int numRows, int numCols);

// argc should be 3: ./a.out <dictionary_file> <grid_file>
// argv[0] = ./a.out, argv[1] = <dictionary_file>, argv[2]= <grid_file>

// 4 nested for loops: row, column, direction, length.
int main(int argc, char **argv) { 
	if (!(argc == 3)) {
		cout << "Try again." << endl;
		exit(-1);
	}

	hashtable ht(22963); // Randomly large prime hash number.
	string line;

	string dictionary = argv[1];

	ifstream file (dictionary); // Reading in the dictionary.

	while (getline(file, line)) { // Store all the lines of the dictionary in the hashtable.
		ht.insert(line);
	}

	file.close();

	int rows, cols;
	bool result = readInGrid(argv[2], rows, cols);
	string direction;
	vector<string> temp;

	// cout << "Rows: " + std::to_string(rows) << endl;
	// cout << "Columns: " + std::to_string(cols) << endl;

    timer t;

    t.start();

	int numWords = 0;
	for (int r = 0; r < rows; r++) { // Going through the rows.
		for (int c = 0; c < cols; c++) { // Going through the columns.
			for (int d = 0; d < 8; d++) { // Going through each direction.
				for (int l = 3; l <= 22; l++) { // Going through each length of word(s).
					string word = getWordInGrid(r, c, d, l, rows, cols);

					// This was the problem. If the word is not within the bounds of the grid, it shouldn't count.
					// It would count the same word multiple times.
					if (!(word.length() == l)) { 
						break;
					}

					if ((ht.find(word))) {
						numWords++;

						if (d == 0) {
							direction = "N";
						} else if (d == 1) {
							direction = "NE";
						} else if (d == 2) {
							direction = "E";
						} else if (d == 3) {
							direction = "SE";
						} else if (d == 4) {
							direction = "S";
						} else if (d == 5) {
							direction = "SW";
						} else if (d == 6) {
							direction = "W";
						} else if (d == 7) {
							direction = "NW";
						}

						temp.push_back(direction + "(" + std::to_string(r) + ", " + std::to_string(c) + "):       " + word);
					}
				}
			}
		}
	}

	for (string element : temp) {
		cout << element << endl;
	}

	// https://stackoverflow.com/questions/4668760/converting-an-int-to-stdstring: helped with converting to string.
	cout << std::to_string(numWords) + " words found" << endl;

    t.stop();

    cout << "This took " + std::to_string(t.getTime()) + " seconds" << endl;

	return 0;
}

bool readInGrid(string filename, int& rows, int& cols) {
    // try to open the file
    ifstream file(filename);
    // upon an error, return false
    if (!file.is_open()) {
        return false;
    }

    // first comes the number of rows
    file >> rows;

    // then the columns
    file >> cols;

    // and finally the grid itself
    string data;
    file >> data;

    // close the file
    file.close();

    // convert the string read in to the 2-D grid format into the
    // grid[][] array.
    // In the process, we'll print the grid to the screen as well.
    int pos = 0; // the current position in the input data
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            grid[r][c] = data[pos++];
        }
    }
    return true;
}

string getWordInGrid (int startRow, int startCol, int dir, int len,
                      int numRows, int numCols) {
    // the static-ness of this variable prevents it from being
    // re-declared upon each function invocation.  It also prevents it
    // from being deallocated between invocations.  It's probably not
    // good programming practice, but it's an efficient means to return
    // a value.
    static string output;
    output.clear(); // Since it's static we need to clear it
    output.reserve(256); // Can't set capacity in the constructor so do it the first time here

    // the position in the output array, the current row, and the
    // current column
    int r = startRow, c = startCol;
    // iterate once for each character in the output
    for (int i = 0; i < len; i++) {
        // if the current row or column is out of bounds, then break
        if (c >= numCols || r >= numRows || r < 0 || c < 0) {
            break;
        }

        // set the next character in the output array to the next letter
        // in the grid
        output += grid[r][c];

        // move in the direction specified by the parameter
        switch (dir) { // assumes grid[0][0] is in the upper-left
            case 0:
                r--;
                break; // north
            case 1:
                r--;
                c++;
                break; // north-east
            case 2:
                c++;
                break; // east
            case 3:
                r++;
                c++;
                break; // south-east
            case 4:
                r++;
                break; // south
            case 5:
                r++;
                c--;
                break; // south-west
            case 6:
                c--;
                break; // west
            case 7:
                r--;
                c--;
                break; // north-west
        }
    }

    return output;
}