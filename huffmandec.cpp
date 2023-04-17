#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "huffNode.h"
using namespace std;

void create_path (huffNode* node, char leaf, string prefix_code);
huffNode* root = new huffNode();
void makeEmpty(huffNode* n);

int main (int argc, char** argv) {
    // verify the correct number of parameters
    if (argc != 2) {
        cout << "Must supply the input file name as the only parameter" << endl;
        exit(1);
    }

    // attempt to open the supplied file
    // must be opened in binary mode as otherwise trailing whitespace is discarded
    ifstream file(argv[1], ifstream::binary);
    // report any problems opening the file and then exit
    if (!file.is_open()) {
        cout << "Unable to open file '" << argv[1] << "'." << endl;
        exit(2);
    }

    
    // read in the first section of the file: the prefix codes
    while (true) {
        string character, prefix;
        // read in the first token on the line
        file >> character;

        // did we hit the separator?
        if (character[0] == '-' && character.length() > 1) {
            break;
        }

        // check for space
        if (character == "space") {
            character = " ";
        }

        // read in the prefix code
        file >> prefix;

        //codes_map[character[0]] = prefix;
        create_path (root, character[0], prefix);

    }

    // read in the second section of the file: the encoded message
    stringstream sstm;
    while (true) {
        string bits;
        // read in the next set of 1's and 0's
        file >> bits;
        // check for the separator
        if (bits[0] == '-') {
            break;
        }
        // add it to the stringstream
        sstm << bits;
    }

    string allbits = sstm.str();

    huffNode* reference = root;

    while (allbits.size() != 0) {
        if (allbits[0] == '0') {
            reference = reference -> left;
            if (reference -> left == NULL) {
                cout << reference -> c;
                reference = root;
            }
        }
        else {
            reference = reference -> right;
            if (reference -> left == NULL) {
                cout << reference -> c;
                reference = root;
            }
        }
        allbits.erase(0, 1);
    }
    cout << endl;

    file.close();
    
    makeEmpty(root);
    return 0;
}

void create_path (huffNode* node, char leaf, string prefix_code) {
    if (prefix_code == "") {
        node -> c = leaf;
        return;
    }

    if ( prefix_code[0] == '0' ) {
        if (node -> left == NULL) {
            huffNode* left = new huffNode();
            node -> left = left;
        }
        prefix_code.erase(0,1);
        create_path (node->left, leaf, prefix_code);
    } 
    else { 
        if (node -> right == NULL) {
            huffNode* right = new huffNode();
            node -> right = right;
        }
        prefix_code.erase(0,1);
        create_path (node->right, leaf, prefix_code);
    }
}

void makeEmpty(huffNode* n) {
    if (n -> left != NULL) {
        makeEmpty(n -> left);
    }
    if (n -> right != NULL) {
        makeEmpty (n -> right);
    }

    delete n;
}






