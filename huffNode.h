#ifndef HUFFNODE_H
#define HUFFNODE_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class huffNode {
public:
	huffNode();
	~huffNode();

	int frequency;
    unsigned char c;
    huffNode* left;
    huffNode* right;

    friend class heap;
};

#endif