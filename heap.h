// Code written by Professor Aaron Bloomfield, 2014
// Released under a CC BY-SA license

#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include "huffNode.h"
using namespace std;

class heap {
public:
    heap();
    heap(vector<huffNode*> vec);
    ~heap();

    void insert(huffNode* some_node);
    huffNode* findMin();
    huffNode* deleteMin();
    unsigned int size();
    void makeEmpty();
    bool isEmpty();
    void print();

private:
    vector<huffNode*> my_heap;
    unsigned int heap_size;

    void percolateUp(int hole);
    void percolateDown(int hole);
};

#endif