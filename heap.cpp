// Code written by Professor Aaron Bloomfield, 2014
// Released under a CC BY-SA license

#include <iostream>
#include "heap.h"
using namespace std;

// default constructor
heap::heap() : heap_size(0) {
    my_heap.push_back(0);
}

// builds a heap from an unsorted vector
heap::heap(vector<huffNode*> vec) : heap_size(vec.size()) {
    my_heap = vec;
    my_heap.push_back(my_heap[0]);
    
    my_heap[0] = 0;

    for (int i = heap_size/2; i > 0; i--) {
        percolateDown(i);
    }
}

heap::~heap() {
}

void heap::insert(huffNode* some_node) {
    // a vector push_back will resize as necessary
    my_heap.push_back(some_node);
    // move it up into the right position
    percolateUp(++heap_size);
}

void heap::percolateUp(int hole) {
    // get the value just inserted
    huffNode* node = my_heap[hole];
    int fre = node -> frequency;
    // while we haven't run off the top and while the
    // value is less than the parent...
    for ( ; (hole > 1) && (fre < my_heap[hole/2] -> frequency); hole /= 2) {
        my_heap[hole] = my_heap[hole/2]; // move the parent down
    }
    // correct position found!  insert at that spot
    my_heap[hole] = node;
}

huffNode* heap::deleteMin() {
    // make sure the heap is not empty
    if (heap_size == 0) {
        throw "deleteMin() called on empty heap";
    }

    // save the value to be returned
    huffNode* ret = my_heap[1];
    // move the last inserted position into the root
    my_heap[1] = my_heap[heap_size--];
    // make sure the vector knows that there is one less element
    my_heap.pop_back();
    // percolate the root down to the proper position
    if (!isEmpty()) {
        percolateDown(1);
    }
    // return the old root node
    return ret;
}

void heap::percolateDown(int hole) {
    // get the value to percolate down
    int x = my_heap[hole] -> frequency;
    huffNode* node = my_heap[hole];
    // while there is a left child...
    while (hole*2 <= heap_size) {
        int child = hole*2; // the left child
        // is there a right child?  if so, is it lesser?
        if ((child+1 <= heap_size) && ((my_heap[child+1] -> frequency) < (my_heap[child] -> frequency))) {
            child++;
        }
        // if the child is greater than the node...
        if (x > my_heap[child] -> frequency) {
            my_heap[hole] = my_heap[child]; // move child up
            hole = child;             // move hole down
        } else {
            break;
        }
    }
    // correct position found! insert at that spot
    my_heap[hole] = node;
}

huffNode* heap::findMin() {
    if (heap_size == 0) {
        throw "findMin() called on empty heap";
    }
    return my_heap[1];
}

unsigned int heap::size() {
    return heap_size;
}

void heap::makeEmpty() {
    for (int i = 1; i < heap_size; i++){
        delete my_heap[i];
    }
    heap_size = 0;
    my_heap.resize(1);
}

bool heap::isEmpty() {
    return heap_size == 0;
}

void heap::print() {
    for (int i = 1; i <= heap_size; i++) {
        cout << my_heap[i] -> c << my_heap[i] -> frequency << endl;
        //next line from http://tinyurl.com/mf9tbgm
        bool isPow2 = (((i+1) & ~(i))==(i+1))? i+1 : 0;
        if (isPow2) {
            cout << endl << "\t";
        }
    }
    cout << endl;
}