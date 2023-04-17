#include <iostream>
#include <string>
#include <vector>
#include "huffNode.h"
using namespace std;

huffNode::huffNode() {
    left = NULL;
    right = NULL;
}

huffNode::~huffNode() {

    left = NULL;
    right = NULL;
}