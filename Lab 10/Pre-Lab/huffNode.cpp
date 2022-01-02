// huffNode.cpp
// November 20th, 2021
// Asadbek Shamsiev, as9vd

#include "huffNode.h"
#include <iostream>
#include <string>

using namespace std;

huffNode::huffNode() {
	left = NULL;
	right = NULL;

	value = ' ';
	frequency = 0;
	code = "";

}

huffNode::huffNode(char input) {
	left = NULL;
	right = NULL;

	value = input;
	frequency = 0;
	code = "";
}

huffNode::~huffNode() {

}

char huffNode::getValue() {
	return value;
}

int huffNode::getFrequency() {
	return frequency;
}

string huffNode::getCode() {
	return code;
}

void huffNode::setValue(char input) {
	value = input;
}