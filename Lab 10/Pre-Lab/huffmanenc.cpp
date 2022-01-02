// huffmanenc.cpp
// November 20th, 2021
// Asadbek Shamsiev, as9vd

// Shoutout to Marcus Mann for helping me break down the pre-lab into managable steps.

// included so we can use cout
#include <iostream>
// file I/O
#include <fstream>
// cstdlib is where exit() lives
#include <cstdlib>
#include "heap.h"
#include <unordered_map>
#include <string>

using namespace std;

void encode(huffNode * node, unordered_map<char, string> & keycodeMap, string code);

// we want to use parameters
int main(int argc, char** argv) {
    // verify the correct number of parameters
    if (argc != 2) {
        cout << "Must supply the input file name as the one and only parameter" << endl;
        exit(1);
    }

    // attempt to open the supplied file
    // ifstream stands for "input file stream"
    ifstream file(argv[1]);

    // if the file wasn't found, output an error message and exit
    if (!file.is_open()) {
        cout << "Unable to open '" << argv[1] << "' for reading" << endl;
        exit(2);
    }

    // read in characters one by one, until reading fails (we hit the end of the file)
    unordered_map<char, int> freqMap; // Shoutout to Nick Mohammed on Piazza for this one.
    unordered_map<char, string> keycodeMap;
    heap huffHeap;

    char g;
    while (file.get(g)) { // This works.
        if (g >= 32) {
            if (freqMap.find(g) == freqMap.end()) { // https://www.geeksforgeeks.org/check-key-present-cpp-map-unordered_map/: if it's not in the thing.
                freqMap.insert({g, 1});
                continue;
            }

            freqMap.at(g)++;
        }   
    }

    // once we hit the end of the file we are marked as "failed", so clear that
    // then "seek" to the beginning of the file to start again
    file.clear(); // Clears the _state_ of the file, not its contents!
    file.seekg(0);

    // https://www.geeksforgeeks.org/traversing-a-map-or-unordered_map-in-cpp-stl/: Very useful tool.
    for (auto i = freqMap.begin(); i != freqMap.end(); i++) {
        huffNode * node = new huffNode();
        node->value = i->first; // https://en.cppreference.com/w/cpp/container/unordered_map: Second is the value.
        node->frequency = i->second;

        huffHeap.insert(node); // This works, and it orders them properly.
    } 

    while (huffHeap.size() > 1) { // Making this into one item on the array because it is just one big tree.
        huffNode * temp = new huffNode('%');

        huffNode * left = huffHeap.deleteMin();
        huffNode * right = huffHeap.deleteMin();

        temp->right = right;
        temp->left = left;

        temp->frequency = left->frequency + right->frequency;        

        huffHeap.insert(temp);
    }

    encode(huffHeap.findMin(), keycodeMap, "");

    // for (int i = 1; i < huffHeap.heapVec.size(); i++) {
    //     if (huffHeap.heapVec[i]->value == ' ') {
    //         cout << "space " << keycodeMap[huffHeap.heapVec[i]->value] << endl;
    //     }

    //     cout << huffHeap.heapVec[i]->value << " " << keycodeMap[huffHeap.heapVec[i]->value] << endl;
    // }

    cout << "----------------------------------------" << endl;

    // string temp;

    int i = 0;
    string tempS = "";

    // g;

    while (file.get(g)) {
        // if (g == )
        i++;

        tempS = tempS + keycodeMap[g]; 
        cout << keycodeMap[g] + " ";
    }

    cout << endl;

    cout << "----------------------------------------" << endl;

    cout << "There are a total of " + to_string(i - 1) + " symbols that are encoded." << endl;
    cout << "There are " + to_string(keycodeMap.size() - 1) + " distinct symbols used." << endl;
    cout << "There were " + to_string(8 * (i - 1)) + " bits in the original file." << endl;
    cout << "There were " + to_string(tempS.length()) + " bits in the compressed file." << endl;
    cout << "This gives a compression ratio of " + to_string((float (8 * (i - 1)) / tempS.length())) + "." << endl;
    cout << "The cost of the Huffman tree is " + to_string((float (tempS.length()) / (i - 1))) + " bits per character." << endl;

    // huffHeap.print();

    huffHeap.makeEmpty(huffHeap.findMin());

    // close the file
    file.close();

    // huffHeap.print();

    return 0;
}

void encode(huffNode * node, unordered_map<char, string> & keycodeMap, string code) {
    if ((!(node->left == NULL)) && (!(node->right == NULL))) {
        encode(node->left, keycodeMap, code + "1");
        encode(node->right, keycodeMap, code + "0");
    }

    if (node->value == ' ') {
        cout << "space " << code << endl;
        keycodeMap[node->value] = code;
    }

    if ((node->left == NULL) && (node->right == NULL) && !(node->value == ' ')) {
    // if ((node->left == NULL) && (node->right == NULL)) {
        cout << node->value << " " << code << endl;
        keycodeMap[node->value] = code;
    }

    // for (int i = 0; i < freqMap.size(); i++) {
}