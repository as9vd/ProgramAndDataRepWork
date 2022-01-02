// hashtable.h
// October 18th, 2021
// Asadbek Shamsiev, as9vd@virginia.edu

#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class hashtable {
public:
	hashtable(int size);
	~hashtable();

	void insert(string x);
	bool find(string x);
	int hashCode(string x);

	// void delete(string x);
private:
	vector<list<string>> v; // https://www.geeksforgeeks.org/difference-between-vector-and-list/: Useful resource this.
};