#ifndef TOPNODE_H
#define TOPNODE_H

#include <vector>
#include <string>

using namespace std;

class topNode {
public:

	/*	\addtogroup nodeGroup
	*
	* 
	*/
	topNode();

	string name;
    int bumCount;
    bool visited;

    vector<topNode *> adjacencyList;
};

#endif