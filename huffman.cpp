#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "heap.h"
#include "huffNode.h"
#include <vector>
#include <cstdlib>
#include <unordered_map>

// for encoding
using namespace std;
heap my_binary_heap;
unordered_map<char, string> codes_map;
int distinct_symbols = 0;
int total_symbols = 0;
int compressed_size = 0;
float cost = 0;
int freq[256];

int determine_prefix_nodes (huffNode* n, string path_taken);

// for decoding
void create_path (huffNode* node, char leaf, string prefix_code);
huffNode* root = new huffNode();
void makeEmpty(huffNode* n);

int main(int argc, char** argv) {
	if (argc != 3) {
        cout << "Must supply the appropriate operation (en/decode) and the input file name" << endl;
        exit(1);
    }

	std::string operation = argv[1];
	if (operation.compare("encode") == 0) {
		ifstream file(argv[2]);
		char g;
		for (int i = 0; i < 256; i++) {
			freq[i] = 0;
		}

		while (file.get(g)) {
			if ((g < 0x20) || (g > 0x7e))
				continue;
			freq[g]++;
		}

		for (int i = 0; i < 256; i++) {
			if (freq[i] != 0) {
				huffNode* node = new huffNode();
				node -> frequency = freq[i];
				node -> c = i;
				my_binary_heap.insert(node);

				codes_map[i] = "";
				total_symbols += freq[i];

			}
		}

		while (my_binary_heap.size() != 1) {
			huffNode* lowest1 = my_binary_heap.deleteMin();
			huffNode* lowest2 = my_binary_heap.deleteMin();

			huffNode* big_node = new huffNode();
			big_node -> left = lowest1;
			big_node -> right = lowest2;
			big_node -> frequency = (lowest1 -> frequency) + (lowest2 -> frequency);

			my_binary_heap.insert(big_node);
		}
		
		huffNode* top_node = my_binary_heap.findMin();

		int distinct = determine_prefix_nodes (top_node, "");

		cout << "----------------------------------------" << endl;
		file.clear(); // Clears the _state_ of the file, not its contents
		file.seekg(0);


		while (file.get(g)) {
			cout << codes_map[g] << " ";
			compressed_size += codes_map[g].length();
		}
		cout << endl;
		file.close();

		cout << "----------------------------------------" << endl;
		cout << "There are a total of " << total_symbols << " symbols that are encoded." << endl;
		cout << "There are " << distinct << " distinct symbols used." << endl;
		cout << "There were " << total_symbols * 8 << " bits in the original file." << endl;
		cout << "There were " << compressed_size << " bits in the compressed file." << endl;
		float ratio = (total_symbols * 8) / (float)compressed_size;
		printf("This gives a compression ratio of %.5f.\n", ratio);
		cout << "The cost of the Huffman tree is " << cost << " bits per character." << endl;

		return 0;
	}

	else if (operation.compare("decode") == 0) {
		ifstream file(argv[2], ifstream::binary);
    	// report any problems opening the file and then exit
    	if (!file.is_open()) {
        	cout << "Unable to open file '" << argv[2] << "'." << endl;
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

	else {
		cout << "enter either 'encode' or 'decode' as your first argument" << endl;
		exit(1);
	}
}

// for encoding
int determine_prefix_nodes (huffNode* n, string path_taken) {
	if (n -> left == NULL) {
		codes_map[n -> c] = path_taken;	
		distinct_symbols++;

		cost += freq[n -> c] / (float)total_symbols * codes_map[n -> c].length();
		if ((n -> c) != ' ') {
			cout << n -> c << " " << path_taken << endl;
		}
		else {
			cout << "space " << path_taken << endl;
		}
	}

	else {
		determine_prefix_nodes(n -> right, path_taken + "1");
		determine_prefix_nodes(n -> left, path_taken + "0");
	}

	return distinct_symbols;
}

// for decoding
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



