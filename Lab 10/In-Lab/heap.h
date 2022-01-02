// Code written by Aaron Bloomfield, 2014
// Released under a CC BY-SA license
// This code is part of the https://github.com/aaronbloomfield/pdr repository

// heap.h
// November 20th, 2021
// Asadbek Shamsiev, as9vd

#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include "huffNode.h"

using namespace std;

class heap {
public:
    heap();
    heap(vector<huffNode *> vec);
    ~heap();

    void insert(huffNode * node);
    huffNode * findMin();
    huffNode * deleteMin();
    unsigned int size();
    void makeEmpty(huffNode * root);
    bool isEmpty();
    void print();
    vector<huffNode *> heapVec;

private:
    unsigned int heap_size;

    void percolateUp(int hole);
    void percolateDown(int hole);
};

#endif