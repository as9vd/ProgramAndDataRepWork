// topological.cpp
// Asadbek Shamsiev, as9vd
// November 27th, 2021

// https://www.youtube.com/watch?v=guJkbg-gnLM: very useful resource for the creation of this.

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <list>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <set>

#include "topNode.h"

using namespace std;

// What I need:
// 1. A way to store degree/number of edges coming in to a node.
// 2. An adjacency list.
// 3. A queue to push/pop things off of as needed.

/**
    @param argc the number of arguments.
**/
int main(int argc, char** argv) {
    set<string> classes;

    vector<topNode *> nodeVector;

    unordered_map<string, vector<string>> bumStorer; // Stores the things going into the node.
    unordered_map<string, vector<string>> adjacencyStorer;

    vector<topNode *> tempHolder;

    if (argc != 2) {
        cout << "Must supply the input file name as the one and only parameter" << endl;
        exit(1);
    }

    ifstream file(argv[1], ifstream::binary);
    
    /**
    *   Checks if file is open.
    */
    if (!file.is_open()) {
        cout << "Unable to open file '" << argv[1] << "'." << endl;
        exit(2);
    }

    /**
    *   Initialises word string.
    */
    string word;

    string holder0; //!< First holder.
    string holder1; //!< Second holder.

    int i = 0; // This determines whether or not to update the holder. 0 is yes, 1 is no.

    while (file >> word) { // It works.
        if (word == "0") {
            break;
        }

        if (i == 0) {
            holder0 = word; // Word doing the hurting. 

            auto found = bumStorer.find(holder0);

            if (found == bumStorer.end()) { // If it's not in the thing. This is for the case of 1110 and other things with degree 0.
                bumStorer.insert({holder0, vector<string>()});
            }

            // ------------------------------ ^ Attacking | V Adjacency

            auto adjFound = adjacencyStorer.find(holder0); // See if the map has the attacker.

            if (adjFound == adjacencyStorer.end()) { // If the adjacency map doesn't has the attacker, we add it.
                adjacencyStorer.insert({holder0, vector<string>()});
            }
        }

        if (i == 1) {
            holder1 = word; // Word getting hurt.

            auto found = bumStorer.find(holder1);

            if (found == bumStorer.end()) { // If it's not in the thing.
                bumStorer.insert({holder1, vector<string>()});
                bumStorer.at(holder1).push_back(holder0);
            } else { // If it is.
                bumStorer.at(holder1).push_back(holder0);
            }

            // ------------------------------ ^ Attacking | V Adjacency

            auto adjFound = adjacencyStorer.find(holder1);

            if (adjFound == adjacencyStorer.end()) {
                adjacencyStorer.insert({holder1, vector<string>()}); // This is for cases where it touches nothing.
            }

            adjacencyStorer.at(holder0).push_back(holder1);
        }

        classes.insert(word);

        if (i == 1) {
            i = 0;
        } else {
            i++;    
        }
    }

    for (const string & clas : classes) { // The set works.
        topNode * tempBum = new topNode();

        tempBum->name = clas; // Works.
        tempBum->bumCount = bumStorer.at(clas).size(); // Works too. The node has both the name and the bumCount.

        for (string s: adjacencyStorer.at(clas)) { // This adds it successfully to the node's adjacency list.
            topNode * tempAdj = new topNode();

            tempAdj->name = s;
            tempAdj->bumCount = bumStorer.at(s).size();
            tempBum->adjacencyList.push_back(tempAdj);
        }

        nodeVector.push_back(tempBum);
    }
    
    file.close();

    // ------------------------------------------------------------------------------------------------

    queue<string> q;
    string v, w;

    int counter = 0;

    auto it = classes.begin(); // for each vertex v
    while (it != classes.end()) { // https://thispointer.com/different-ways-to-iterate-over-a-set-in-c/
        if (bumStorer.at(*it).size() == 0) { // if (v.indegree == 0)
            q.push(*it); // q.enqueue(v);
        }

        it++; // This shit works. It does push 1110 to top.
    }

    /*
    *   \author Asadbek Shamsiev
    */
    while (!q.empty()) {
        v = q.front(); // get vertex of indegree 0
        q.pop();

        topNode * temp;

        cout << v << " ";

        counter++;

        for (int i = 0; i < nodeVector.size(); i++) {
            if (nodeVector[i]->name == v) { // Assigning the actual node to the temporary node for comparison purposes.
                temp = nodeVector[i]; // This updates the name, bumCount, etc.
            }
        }

        // cout << nodeVector[0]->adjacencyList[0]->name + ": " + to_string(nodeVector[0]->adjacencyList[0]->bumCount) << endl;
        // cout << nodeVector[0]->adjacencyList[1]->name + ": " + to_string(nodeVector[0]->adjacencyList[1]->bumCount) << endl;

        for (int i = 0; i < temp->adjacencyList.size(); i++) {
            temp->adjacencyList[i]->bumCount--;
            if (temp->adjacencyList[i]->bumCount == 0) { // They're all zero because the bumCount isn't updating properly.
                q.push(temp->adjacencyList[i]->name);
                // cout << temp->adjacencyList[i]->name << endl;
            }
        }

        if (!(counter == classes.size())) {
            break;
        }

    }

    // cout << nodeVector[0]->adjacencyList[0]->name + ": " + to_string(nodeVector[0]->adjacencyList[0]->bumCount) << endl;
    // cout << nodeVector[0]->adjacencyList[1]->name + ": " + to_string(nodeVector[0]->adjacencyList[1]->bumCount) << endl;

    cout << endl;     
	
	return 0;
}