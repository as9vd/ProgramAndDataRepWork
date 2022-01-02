// huffNode.h
// November 20th, 2021
// Asadbek Shamsiev, as9vd

#ifndef HUFFNODE_H
#define HUFFNODE_H

#include <iostream>
#include <string>

using namespace std;

class huffNode {
public:
	huffNode();
	huffNode(char input);
	~huffNode();
	
	char getValue();
	int getFrequency();
	string getCode(); // This will create the unique bit code for the huffNode.

	void setValue(char input);

	huffNode* left;
	huffNode* right;

	char value;
	int frequency;
	string code;

private:
	
};

#endif