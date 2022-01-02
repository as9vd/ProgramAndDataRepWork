// Code written by Aaron Bloomfield, 2014
// Released under a CC BY-SA license
// This code is part of the https://github.com/aaronbloomfield/pdr repository

// heap.cpp
// November 20th, 2021
// Asadbek Shamsiev, as9vd

#include <iostream>
#include "heap.h"
// #include "huffNode.h"
using namespace std;

// default constructor
heap::heap() : heap_size(0) { // Heap size will be set to 0, even with the dummy node present.
    huffNode * node = new huffNode;
    node->setValue(0);

    heapVec.push_back(node);
}

// builds a heap from an unsorted vector
heap::heap(vector<huffNode *> vec) : heap_size(vec.size()) {
    heapVec = vec;
    heapVec.push_back(heapVec[0]); // We push it to the back because the vector has something it cares about in spot 0.

    huffNode * node = new huffNode;
    node->setValue(0); // This is a dummy node.

    heapVec[0] = node; // We then make this zero to make it a dummy node. But we kept the actual thing in spot 0.
    for (int i = heap_size / 2; i > 0; i--) { // Half the heap, e.g. until the last internal node (heap_size / 2).
        percolateDown(i); // No PercolateDown on leaves.
    }
}

// the destructor doesn't need to do much
heap::~heap() {

}

void heap::insert(huffNode * node) {
    // a vector push_back will resize as necessarycl
    heapVec.push_back(node); // Push the shit to the end.

    // move it up into the right position
    percolateUp(++heap_size); // "Repeatedly swap with parent until it's in position."
}

void heap::percolateUp(int hole) { // Hole = spot where element is inserted. Keeps track of where actual insertion will occur.
    // get the value just inserted
    huffNode * x = heapVec[hole]; // This initialising a node carry-on doesn't work in this case. Remember that.
    // while we haven't run off the top and while the
    // value is less than the parent...
    for ( ; (hole > 1) && (x->getFrequency() < heapVec[hole/2]->getFrequency()); hole /= 2) { // (Hole / 2) = index of parent.
        heapVec[hole] = heapVec[hole/2]; // move the parent down
    }
    // correct position found!  insert at that spot

    // huffNode * node = new huffNode;
    // node->setValue(x);

    heapVec[hole] = x;
}

huffNode * heap::deleteMin() {
    // make sure the heap is not empty
    if (heap_size == 0) {
        throw "deleteMin() called on empty heap";
    }

    // save the value to be returned
    huffNode * ret = heapVec[1];
    // move the last inserted position into the root
    heapVec[1] = heapVec[heap_size--];
    // make sure the vector knows that there is one less element
    heapVec.pop_back();
    // percolate the root down to the proper position
    if (!isEmpty()) {
        percolateDown(1);
    }
    // return the old root node
    return ret;
}

void heap::percolateDown(int hole) {
    // get the value to percolate down
    // int x = heapVec[hole]->getValue();

    huffNode * x = heapVec[hole]; // The above sh** doesn't work with frequencies, etc.

    // while there is a left child...
    while (hole*2 <= heap_size) {
        int child = hole*2; // the left child
        // is there a right child?  if so, is it lesser?
        if ((child+1 <= heap_size) && (heapVec[child+1]->getFrequency() < heapVec[child]->getFrequency())) {
            child++;
        }
        // if the child is greater than the node...
        if (x->getFrequency() > heapVec[child]->getFrequency()) {
            heapVec[hole] = heapVec[child]; // move child up
            hole = child;             // move hole down
        } else {
            break;
        }
    }
    // correct position found!  insert at that spot

    // huffNode * node = new huffNode;
    // node->setValue(x);

    heapVec[hole] = x;
}

huffNode * heap::findMin() {
    if (heap_size == 0) {
        throw "findMin() called on empty heap";
    }
    return heapVec[1]; // Makes sense, because the smallest value should be at the top.
}

unsigned int heap::size() {
    return heap_size;
}

void heap::makeEmpty(huffNode * root) { // This'll be called for the root node exclusively.
    if (!(root->left == NULL) && !(root->right == NULL)) { // Recurse down both the left and the right.
        makeEmpty(root->left);
        makeEmpty(root->right);
    }

    delete root;

    heap_size = 0;
    heapVec.resize(1); // Reduces to only the dummy node at the beginning.
}

bool heap::isEmpty() {
    return heap_size == 0;
}

void heap::print() {
    // cout << "(" << heapVec[0] << ") ";
    // for (int i = 1; i <= heap_size; i++) {
    //     cout << heapVec[i]->getValue() << " ";
    //     // next line from http://tinyurl.com/mf9tbgm
    //     bool isPow2 = (((i+1) & ~(i))==(i+1))? i+1 : 0;
    //     if (isPow2) {
    //         // cout << endl << "\t"; // Starts printing the next row if is a power of 2.
    //         cout << endl;
    //     }
    // }
    // cout << endl;

    for (int i = 1; i < heapVec.size(); i++) {
        cout << "Value: " + to_string(heapVec[i]->value) + ", Frequency: " + to_string(heapVec[i]->frequency);
        cout << endl;
    }

    // for (int i = 1; i < heapVec.size(); i++) {
}